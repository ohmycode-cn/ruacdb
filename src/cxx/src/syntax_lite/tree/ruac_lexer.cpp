/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_lexer.hpp
 * src/syntax_lite/tree/ruac_lexer.cpp
 */

#include "syntax_lite/tree/ruac_keyword.hpp"
#include "syntax_lite/tree/ruac_kwmapps.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include <cctype>

namespace ruac::syntax_lite::tree {

    void Lexer::skip_whitespace() {
        while (m_pos < m_line.size() && std::isspace(m_line[m_pos])) {
            m_pos++;
        }
    }

    void Lexer::get_string(std::string &str_) {
        std::string tmp_string;
        while (m_pos < m_line.size() && m_line[m_pos] != keyword::symbol::G_WHITESPACE_CHAR) {
            tmp_string += m_line[m_pos];
            m_pos++;
        }
        str_ = tmp_string;
        if (m_pos < m_line.size() && m_line[m_pos] == keyword::symbol::G_WHITESPACE_CHAR) {
            m_pos++;
        }
    }

    void Lexer::read_token() {
        std::string word;
        skip_whitespace();
        get_string(word);
        if (word.empty())
            return;
        auto it = kwmapps::maps.find(word);
        if (it != kwmapps::maps.end()) {
            m_tokens.push_back({it->second, word});
        } else {
            m_tokens.push_back({kwenums::TokenType::IDENTIFIER, word});
        }
    }

    void Lexer::parse_line(const std::string &line_) {
        m_line = line_;
        m_pos = 0;
        m_tokens.clear();
        while (m_pos < m_line.size()) {
            read_token();
        }
    }

    auto Lexer::get_tokens() -> std::vector<Token> {
        return m_tokens;
    }

} // namespace ruac::syntax_lite::tree
