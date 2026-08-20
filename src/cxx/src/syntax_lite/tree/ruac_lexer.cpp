/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_lexer.hpp
 * src/syntax_lite/tree/ruac_lexer.cpp
 */

#include "syntax_lite/tree/ruac_keyword.hpp"
#include "syntax_lite/tree/ruac_keyword_map.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"

#include <cctype>
#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::syntax_lite::tree {

    void Lexer::skip_whitespace() {
        while (m_pos < m_line.size() && std::isspace(m_line[m_pos])) {
            m_pos++;
        }
    }

    void Lexer::read_word(std::string &str_) {
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
        read_word(word);
        if (word.empty()) {
            return;
        }
        if (const auto it = keyword_map::maps.find(word); it != keyword_map::maps.end()) {
            m_tokens.push_back({.type = it->second, .value = word});
        } else {
            m_tokens.push_back({.type = token_type::TokenType::IDENTIFIER, .value = word});
        }
    }

    void Lexer::tokenize(const std::string &line_) {
        m_line = line_;
        m_pos = 0;
        m_tokens.clear();
        while (m_pos < m_line.size()) {
            read_token();
        }
    }

    auto Lexer::tokens() -> std::vector<Token> {
        return m_tokens;
    }

    void Lexer::out_tokens() {
        std::stringstream ss;
        auto list{m_tokens};
        ss << "THIS IS TEMPORARY DEBUG OUTPUT THE X TIME : X->" << m_tmp_debug_count++ << "\n";
        ss << "TOKENS:[\n";
        for (size_t index{0}; index < list.size(); index++) {
            ss << "Token   item: " << index << "\n";
            ss << "Token int id: " << static_cast<int>(list[index].type) << "\n";
            ss << "Token  value: " << list[index].value << "\n";
            ss << "\n";
        }
        ss << "];\n";
        std::osyncstream(std::cout) << ss.str() << std::endl;
    };

} // namespace ruac::syntax_lite::tree
