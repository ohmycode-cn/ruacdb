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

    /**
     * @brief Skip whitespace characters at the current position
     *
     * @details Advances m_pos past consecutive space/tab characters
     *          in m_line until a non-whitespace character or end of
     *          string is reached.
     *
     */
    void Lexer::skip_whitespace() {
        while (m_pos < m_line.size() && std::isspace(m_line[m_pos])) {
            m_pos++;
        }
    }

    /**
     * @brief Read a word from the current position into the output string
     *
     * @param str_ - Output parameter receiving the extracted word
     *
     * @details Accumulates characters from m_pos until a whitespace
     *          character or end of m_line is found, then stores the
     *          result in str_. Advances m_pos past the trailing
     *          whitespace delimiter if present.
     *
     */
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

    /**
     * @brief Read and classify the next token from the input line
     *
     * @details Skips leading whitespace, extracts a word via
     *          read_word(), then looks it up in the keyword map.
     *          If found, the token is classified with the matched
     *          keyword type; otherwise it is classified as IDENTIFIER.
     *          Does nothing when the extracted word is empty.
     *
     */
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

    /**
     * @brief Tokenize an entire input line into a vector of Token objects
     *
     * @param line_ - The input string to tokenize
     *
     * @details Resets m_pos to 0, clears any previous tokens, and
     *          repeatedly calls read_token() until the entire line
     *          has been consumed.
     *
     */
    void Lexer::tokenize(const std::string &line_) {
        m_line = line_;
        m_pos = 0;
        m_tokens.clear();
        while (m_pos < m_line.size()) {
            read_token();
        }
    }

    /**
     * @brief Return the tokens produced by the most recent tokenize call
     *
     * @return std::vector<Token> - Copy of the internal token vector
     *
     */
    auto Lexer::tokens() -> std::vector<Token> {
        return m_tokens;
    }

    /**
     * @brief Print the current token list to stdout for debugging
     *
     * @details Outputs each token's index, integer type id, and
     *          string value to stdout via std::osyncstream.
     *
     */
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
