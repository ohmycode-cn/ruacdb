/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_parser.hpp
 * src/syntax_lite/tree/ruac_parser.cpp
 */

// #include "syntax_lite/tree/node/ruac_nodeproc.hpp"
#include "syntax_lite/tree/node/ruac_nodelist.hpp"
#include "syntax_lite/tree/ruac_keyword.hpp"
#include "syntax_lite/tree/ruac_kwenums.hpp"
#include "syntax_lite/tree/ruac_parser.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "rstd/messages/ruac_stddug.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <variant>

namespace ruac::syntax_lite::tree {

    /**
     * @brief Reset the parser cursor to the start of the token stream
     *
     * @details Sets m_pos back to 0 so the next peek/consume begins from
     *          the first token in M_TOKENS. The token vector itself is left
     *          untouched; it is repopulated by get_query() before a new
     *          parse cycle starts.
     *
     */
    void Parser::reset() {
        m_pos = 0;
    }

    /**
     * @brief Check whether more tokens remain to be consumed
     *
     * @return bool - true if m_pos has not reached the end of M_TOKENS,
     *         false otherwise
     *
     * @details Compares the current cursor position against the size of
     *          M_TOKENS. Callers should invoke this before peek()/consume()
     *          to avoid out-of-range access.
     *
     */
    bool Parser::has_more() {
        return m_pos < M_TOKENS.size();
    }

    /**
     * @brief Inspect the token at the current cursor position
     *
     * @return const Token & - reference to the current token
     *
     * @details Returns a const reference to M_TOKENS[m_pos] without
     *          advancing the cursor. Behaviour is undefined if has_more()
     *          is false; callers must guard with has_more() first.
     *
     */
    auto Parser::peek() const -> const Token & {
        return M_TOKENS[m_pos];
    }

    /**
     * @brief Return the current token and advance the cursor past it
     *
     * @return const Token & - reference to the token that was current
     *         before the advance
     *
     * @details Returns a const reference to M_TOKENS[m_pos] and then
     *          increments m_pos. The reference stays valid because M_TOKENS
     *          is not modified during parsing. Behaviour is undefined if
     *          has_more() is false.
     *
     */
    auto Parser::consume() -> const Token & {
        return M_TOKENS[m_pos++];
    }

    /**
     * @brief Check that the current token matches the expected type/value
     *
     * @param type_  - Required TokenType classification
     * @param value_ - Optional exact value to match; empty string means
     *                 only the type is checked
     * @return bool  - true if the current token matches both constraints
     *                 and has been consumed, false otherwise (cursor stays)
     *
     * @details When value_ is empty only a type-check is performed; when
     *          non-empty the token value must also compare equal. On
     *          success the cursor advances past the matched token; on
     *          failure m_pos is left unchanged so the caller can backtrack.
     *
     */
    bool Parser::expect(kwenums::TokenType type_, const std::string &value_) {
        if (!has_more())
            return false;
        const auto &t = peek();
        if (t.type != type_)
            return false;
        if (!value_.empty() && t.value != value_)
            return false;
        consume();
        return true;
    }

    /**
     * @brief Parse a CREATE DATABASE statement into its AST node
     *
     * @return bool - true on success, false if a required token is missing
     *
     * @details Cursor is positioned just past "database" on entry.
     *          Optionally consumes the triplet "if not exists" and then
     *          a single IDENTIFIER for the database name. On success the
     *          resulting node is stored into SynxList via set_node_tree,
     *          relying on std::variant's implicit converting constructor
     *          to wrap the struct into the variant type.
     *
     */
    bool Parser::parse_create_database() {

        rstd::messages::StdMsg::instance()
            .print(rstd::messages::StdDug::instance()
                       .ostrs(
                           "Parser: CreateDatabase",
                           __FILE__,
                           __LINE__));

        // namespace ka = keyword::attribute;
        namespace ks = keyword::symbol;
        using kw = kwenums::TokenType;
        node::nodelist::CreateDatabase node;

        // Optional: "if not exists" — each word may be a KEYWORD_ATTRIBUTE
        // or fall back to plain IDENTIFIER if not yet in the keyword map.
        auto match_word = [&](const std::string &w) -> bool {
            if (!has_more())
                return false;
            const auto &t = peek();
            if (t.value != w)
                return false;
            if (t.type != kw::KEYWORD_ATTRIBUTE &&
                t.type != kw::KEYWORD_SYMBOL &&
                t.type != kw::IDENTIFIER)
                return false;
            consume();
            return true;
        };
        if (match_word("if")) {
            if (!match_word(ks::G_NOT))
                return false;
            if (!match_word("exists"))
                return false;
            node.if_not_exists = true;
        }
        if (!has_more() || peek().type != kw::IDENTIFIER)
            return false;
        node.name = consume().value;
        M_SYNX_LIST->set_node_tree(node);
        return true;
    }

    /**
     * @brief Parse a CREATE TABLE statement into its AST node
     *
     * @return bool - true on success, false if a required token is missing
     *
     * @details Cursor is positioned just past "table"/"tables" on entry.
     *          Optionally consumes the triplet "if not exists" and then
     *          a single IDENTIFIER for the table name. On success the
     *          resulting node is stored into SynxList via set_node_tree.
     *          Parenthesised column definitions are not handled yet and
     *          are left for a later pass once the lexer can split
     *          punctuation tokens separately from identifiers.
     *
     */
    bool Parser::parse_create_table() {

        rstd::messages::StdMsg::instance()
            .print(rstd::messages::StdDug::instance()
                       .ostrs(
                           "Parser: CreateDatabase",
                           __FILE__,
                           __LINE__));

        using kw = kwenums::TokenType;
        namespace ks = keyword::symbol;
        node::nodelist::CreateTable node;

        auto match_word = [&](const std::string &w) -> bool {
            if (!has_more())
                return false;
            const auto &t = peek();
            if (t.value != w)
                return false;
            if (t.type != kw::KEYWORD_ATTRIBUTE &&
                t.type != kw::KEYWORD_SYMBOL &&
                t.type != kw::IDENTIFIER)
                return false;
            consume();
            return true;
        };
        if (match_word("if")) {
            if (!match_word(ks::G_NOT))
                return false;
            if (!match_word("exists"))
                return false;
            node.if_not_exists = true;
        }
        if (!has_more() || peek().type != kw::IDENTIFIER)
            return false;
        node.name = consume().value;
        M_SYNX_LIST->set_node_tree(node);
        return true;
    }

    /**
     * @brief Parse a USE DATABASE statement into its AST node
     *
     * @return bool - true on success, false if the name identifier is
     *         missing or of the wrong token type
     *
     * @details Cursor is positioned just past "database"/"databases"
     *          on entry. Expects a single IDENTIFIER token for the target
     *          database name; on success wraps the resulting UseDatabase
     *          node and stores it via SynxList.
     *
     */
    bool Parser::parse_use_database() {
        using kw = kwenums::TokenType;
        if (!has_more() || peek().type != kw::IDENTIFIER)
            return false;
        node::nodelist::UseDatabase node;
        node.name = consume().value;
        M_SYNX_LIST->set_node_tree(node);
        return true;
    }

    /**
     * @brief Parse a SHOW DATABASES statement into its AST node
     *
     * @return bool - Always returns true on the current grammar because
     *         no further tokens are required after the object keyword.
     *
     * @details Cursor is positioned just past "databases"/"database" on
     *          entry. An optional trailing IDENTIFIER is accepted as a
     *          filter name and stored in the node; if absent the name
     *          field stays empty. On success stores the ShowDatabases
     *          node via SynxList.
     *
     */
    bool Parser::parse_show_databases() {
        using kw = kwenums::TokenType;
        node::nodelist::ShowDatabases node;
        if (has_more() && peek().type == kw::IDENTIFIER) {
            node.name = consume().value;
        }
        M_SYNX_LIST->set_node_tree(node);
        return true;
    }

    /**
     * @brief Parse a SHOW TABLES statement into its AST node
     *
     * @return bool - Always returns true on the current grammar because
     *         no further tokens are required after the object keyword.
     *
     * @details Cursor is positioned just past "tables"/"table" on entry.
     *          An optional trailing IDENTIFIER is accepted as a scope
     *          (database) name and stored in the node; if absent the
     *          name field stays empty. On success stores the ShowTables
     *          node via SynxList.
     *
     */
    bool Parser::parse_show_tables() {
        using kw = kwenums::TokenType;
        node::nodelist::ShowTables node;
        if (has_more() && peek().type == kw::IDENTIFIER) {
            node.name = consume().value;
        }
        M_SYNX_LIST->set_node_tree(node);
        return true;
    }

    Parser::Parser() : M_SYNX_LIST(std::make_unique<SynxList>()), M_LEXER(std::make_unique<Lexer>()) {}

    /**
     * @brief Test helper: dump all parsed tokens to stdout
     *
     * @details Iterates through M_TOKENS once, printing each token's
     *          numeric type id and string value wrapped in a bracketed
     *          block. Used as a temporary diagnostic while the parser
     *          logic is being developed.
     *
     */
    void Parser::print_tokens() {
        std::stringstream ss;
        ss << "Tmp Test !\n[\n";
        for (const auto &token : M_TOKENS) {
            ss << "    Token Type ID: " << static_cast<int>(token.type) << "\n"
               << "    Token Value  : " << token.value << "\n";
        }
        ss << "]\n";
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

    /**
     * @brief Dispatch the token stream to the appropriate parse_* method
     *
     * @details Resets the cursor to the start, then uses expect() to
     *          consume the opening KEYWORD_ATTRIBUTE token (e.g. create,
     *          show, use). The attribute string is recorded so the second
     *          token (KEYWORD_OBJECT, e.g. database, table) can select
     *          the correct concrete parse_xxx routine.
     *
     */
    void Parser::dispatcher() {
        M_SYNX_LIST->clr_node_tree();
        reset();
        if (!has_more())
            return;
        // Peek-and-hold: capture the attribute keyword string BEFORE we
        // consume it, so the reference stays valid for the rest of the
        // function (the underlying Token inside M_TOKENS is not moved).
        const std::string attr_val = peek().value;
        if (!expect(kwenums::TokenType::KEYWORD_ATTRIBUTE) || !has_more()) {
            return;
        }
        const auto obj_v = peek().value;
        const auto obj_t = peek().type;
        if (obj_t != kwenums::TokenType::KEYWORD_OBJECT) {
            return;
        }
        consume();
        if (attr_val == keyword::attribute::G_CREATE) {
            if (obj_v == keyword::object::G_DATABASE) {
                parse_create_database();
            } else if (obj_v == keyword::object::G_TABLE) {
                parse_create_table();
            }
        } else if (attr_val == keyword::attribute::G_SHOW) {
            if (obj_v == keyword::object::G_DATABASES) {
                parse_show_databases();
            } else if (obj_v == keyword::object::G_TABLES) {
                parse_show_tables();
            }
        } else if (attr_val == keyword::attribute::G_USE) {
            if (obj_v == keyword::object::G_DATABASE) {
                parse_use_database();
            }
        }
    }

    void Parser::parser() {
        dispatcher();
        auto &node = M_SYNX_LIST->get_node_tree();
        std::visit([](auto &arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, node::nodelist::CreateDatabase>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::CreateTable>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::UseDatabase>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::ShowDatabases>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::ShowTables>) {
            }
        },
                   node);
    }

    void Parser::get_query(const std::string &line_) {
        std::lock_guard<std::mutex> lock(M_PARSER_MTX);
        M_LEXER->parse_line(line_);
        M_TOKENS = M_LEXER->get_tokens();
        parser();
    }

} // namespace ruac::syntax_lite::tree
