/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_parser.hpp
 * src/syntax_lite/tree/ruac_parser.cpp
 */

#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "syntax_lite/tree/node/ruac_node_types.hpp"
#include "syntax_lite/tree/ruac_keyword.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include "syntax_lite/tree/ruac_parser.hpp"
#include "syntax_lite/tree/ruac_token_type.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::syntax_lite::tree {

    void Parser::reset() {
        m_pos = 0;
    }

    auto Parser::has_more() -> bool {
        return m_pos < M_TOKENS.size();
    }

    auto Parser::peek() const -> const Token & {
        return M_TOKENS[m_pos];
    }

    auto Parser::consume() -> const Token & {
        return M_TOKENS[m_pos++];
    }

    auto Parser::expect(token_type::TokenType type_, const std::string &value_) -> bool {
        if (!has_more()) {
            return false;
        }
        const auto &t = peek();
        if (t.type != type_) {
            return false;
        }
        if (!value_.empty() && t.value != value_) {
            return false;
        }
        consume();
        return true;
    }

    auto Parser::parse_create_database() -> bool {

        // tmp debug line;
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();
        constexpr const char *const dugmsg{"Class: Parser, Func: parse_create_database"};
        stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));

        namespace ks = keyword::symbol;
        using tt = token_type::TokenType;
        node::types::CreateDatabase node;

        auto match_word = [&](const std::string &w) -> bool {
            if (!has_more())
                return false;
            const auto &t = peek();
            if (t.value != w)
                return false;
            if (t.type != tt::KEYWORD_ATTRIBUTE &&
                t.type != tt::KEYWORD_SYMBOL &&
                t.type != tt::IDENTIFIER)
                return false;
            consume();
            return true;
        };
        if (match_word("if")) {
            if (!match_word(ks::G_NOT)) {
                return false;
            }
            if (!match_word("exists")) {
                return false;
            }
            node.if_not_exists = true;
        }
        if (!has_more() || peek().type != tt::IDENTIFIER) {
            return false;
        }
        node.name = consume().value;
        m_node_store->set_node_tree(node);
        return true;
    }

    auto Parser::parse_create_table() -> bool {

        // Tmp debug.
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();
        constexpr const char *const dugmsg{"Class: Parser, Func: parse_create_table"};
        stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));

        using tt = token_type::TokenType;
        namespace ks = keyword::symbol;
        node::types::CreateTable node;

        auto match_word = [&](const std::string &w) -> bool {
            if (!has_more()) {
                return false;
            }
            const auto &t = peek();
            if (t.value != w) {
                return false;
            }
            if (t.type != tt::KEYWORD_ATTRIBUTE && t.type != tt::KEYWORD_SYMBOL && t.type != tt::IDENTIFIER) {
                return false;
            }
            consume();
            return true;
        };

        if (match_word("if")) {
            if (!match_word(ks::G_NOT)) {
                return false;
            }
            if (!match_word("exists")) {
                return false;
            }
            node.if_not_exists = true;
        }
        if (!has_more() || peek().type != tt::IDENTIFIER) {
            return false;
        }
        node.name = consume().value;
        m_node_store->set_node_tree(node);
        return true;
    }

    auto Parser::parse_use_database() -> bool {
        using tt = token_type::TokenType;
        if (!has_more() || peek().type != tt::IDENTIFIER) {
            return false;
        }
        node::types::UseDatabase node;
        node.name = consume().value;
        m_node_store->set_node_tree(node);
        return true;
    }

    auto Parser::parse_show_databases() -> bool {
        using tt = token_type::TokenType;
        node::types::ShowDatabases node;
        if (has_more() && peek().type == tt::IDENTIFIER) {
            node.name = consume().value;
            if (!node.name.empty()) {
                const auto tar{"\n" + M_SPACE_SEVEN + "Target is '" + node.name + "'"};
                const auto msg{"Error: Not supported parameter target -> show databases <target>"};
                std::osyncstream(std::cout) << msg << tar << std::endl;
                return false;
            }
        }
        node.name = "*";
        m_node_store->set_node_tree(node);
        return true;
    }

    auto Parser::parse_show_database_specific() -> bool {
        using tt = token_type::TokenType;
        namespace ks = keyword::symbol;
        node::types::ShowDatabases node;
        if (has_more() && peek().type == tt::KEYWORD_SYMBOL && peek().value == ks::G_STAR) {
            {
                std::stringstream ss;
                ss << "Error: Not supported parameter target syntax keyword star symbol '*', show database <target>. ";
                ss << "You should replace * with to all. Or you can use show databases replace to show database all.";
                ss << "\n" + M_SPACE_SEVEN + "Target is '*'";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
            return false;
        }
        if (has_more() && peek().type == tt::IDENTIFIER) {
            node.name = consume().value;
        } else {
            node.name = "*"; // default to show all databases. show database * = show databases
            {
                std::stringstream ss;
                ss << "Warn : You not specific parameter target -> show database <target>, default use * !";
                ss << "\n" + M_SPACE_SEVEN + "Target is '" + node.name + "'";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
        }

        m_node_store->set_node_tree(node);
        return true;
    }

    auto Parser::parse_show_tables() -> bool {
        using tt = token_type::TokenType;
        node::types::ShowTables node;
        if (has_more() && peek().type == tt::IDENTIFIER) {
            node.name = consume().value;
        }
        m_node_store->set_node_tree(node);
        return true;
    }

    Parser::Parser(int uid_)
        : m_node_store(std::make_unique<NodeStore>()),
          m_executor(std::make_unique<Executor>(uid_)),
          M_LEXER(std::make_unique<Lexer>()) {}

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

    void Parser::dispatch() {
        m_node_store->clr_node_tree();
        reset();
        if (!has_more())
            return;
        const std::string attr_val = peek().value;
        if (!expect(token_type::TokenType::KEYWORD_ATTRIBUTE) || !has_more()) {
            return;
        }
        const auto obj_v = peek().value;
        const auto obj_t = peek().type;
        if (obj_t != token_type::TokenType::KEYWORD_OBJECT) {
            return;
        }
        consume();
        if (attr_val == keyword::attribute::G_CREATE) {
            if (obj_v == keyword::object::G_DATABASE) {
                m_parser_success = parse_create_database();
            } else if (obj_v == keyword::object::G_TABLE) {
                m_parser_success = parse_create_table();
            }
        } else if (attr_val == keyword::attribute::G_SHOW) {
            if (obj_v == keyword::object::G_DATABASES) {
                m_parser_success = parse_show_databases();
            } else if (obj_v == keyword::object::G_DATABASE) {
                m_parser_success = parse_show_database_specific();
            } else if (obj_v == keyword::object::G_TABLES) {
                m_parser_success = parse_show_tables();
            }
        } else if (attr_val == keyword::attribute::G_USE) {
            if (obj_v == keyword::object::G_DATABASE) {
                m_parser_success = parse_use_database();
            }
        }
    }

    void Parser::parse() {
        dispatch();
        if (!m_parser_success) {
            return;
        }
        m_executor->dispatch(m_node_store.get());
    }

    void Parser::process(const std::string &line_) {
        std::lock_guard<std::mutex> lock(M_PARSER_MTX);
        M_LEXER->tokenize(line_);
        M_TOKENS = M_LEXER->tokens();
        M_LEXER->out_tokens(); // Tmp debug line.
        parse();
    }

} // namespace ruac::syntax_lite::tree
