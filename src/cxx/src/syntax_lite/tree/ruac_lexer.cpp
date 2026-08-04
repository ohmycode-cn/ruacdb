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

    /**
     * @brief Skip whitespace characters in the input line
     *
     * @details Advances m_pos past all consecutive whitespace characters
     *          (detected via std::isspace) until a non-whitespace character
     *          or end-of-line is reached.
     *
     */
    void Lexer::skip_whitespace() {
        while (m_pos < m_line.size() && std::isspace(m_line[m_pos])) {
            m_pos++;
        }
    }

    /**
     * @brief Extract a token string from the current position
     *
     * @param str_ - Output string to store the extracted token
     *
     * @details Reads characters from m_line starting at m_pos until a
     *          whitespace character (keyword::symbol::G_WHITESPACE_CHAR) or
     *          end-of-line is reached. Stores the result in str_ and advances
     *          m_pos past the terminating whitespace character if present.
     *
     */
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

    /**
     * @brief Read and classify a single token from the input line
     *
     * @details Skips leading whitespace, extracts a string token via get_string(),
     *          then looks it up in the keyword map (kwmapps::maps). If found,
     *          creates a token with the matched keyword type; otherwise creates
     *          an IDENTIFIER token. Pushes the result into m_tokens.
     *
     */
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

    /**
     * @brief Parse an entire input line into tokens
     *
     * @param line_ - Input string line to parse
     *
     * @details Sets m_line to the provided string, resets m_pos to 0, clears
     *          m_tokens, then repeatedly calls read_token() until the end of
     *          the line is reached.
     *
     */
    void Lexer::parse_line(const std::string &line_) {
        m_line = line_;
        m_pos = 0;
        m_tokens.clear();
        while (m_pos < m_line.size()) {
            read_token();
        }
    }

    /**
     * @brief Get the parsed tokens
     *
     * @return std::vector<Token> - Copy of the internal token vector
     *
     * @details Returns a copy of m_tokens containing all tokens parsed from
     *          the most recent parse_line() call.
     *
     */
    auto Lexer::get_tokens() -> std::vector<Token> {
        return m_tokens;
    }

} // namespace ruac::syntax_lite::tree
