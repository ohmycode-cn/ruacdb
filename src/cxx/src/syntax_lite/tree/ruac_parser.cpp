/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_parser.hpp
 * src/syntax_lite/tree/ruac_parser.cpp
 */

#include "syntax_lite/tree/node/ruac_nodeproc.hpp"
#include "syntax_lite/tree/ruac_parser.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::syntax_lite::tree {

    Parser::Parser() : M_SYNX_LIST(std::make_unique<SynxList>()), M_LEXER(std::make_unique<Lexer>()) {}

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

    void Parser::print_tokens() {
        std::stringstream ss;
        ss << "Tmp Test !\n";
        for (std::size_t line_id{0}; line_id < M_TOKENS.size(); ++line_id) {
            ss << "Line ID: " << line_id << " -> [\n";
            for (const auto &token : M_TOKENS) {
                ss << "    Token Type ID: " << static_cast<int>(token.type) << "\n"
                   << "    Token Value  : " << token.value << "\n";
            }
            ss << "]\n";
            std::cout << ss.str() << std::endl;
        }
    }

    void Parser::dispatcher() {
    }

    void Parser::parser_tokens() {
        print_tokens();
    }

    void Parser::get_query(const std::string &line_) {
        std::lock_guard<std::mutex> lock(M_PARSER_MTX);
        M_LEXER->parse_line(line_);
        M_TOKENS = M_LEXER->get_tokens();
        parser_tokens();
    }

} // namespace ruac::syntax_lite::tree
