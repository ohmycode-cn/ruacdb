/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_lexer.hpp
 * src/syntax_lite/tree/ruac_lexer.cpp
 *
 * @brief Implements Lexer class for tokenizing RUAC syntax input.
 */

#pragma once
#ifndef RUAC_LEXER_HPP
#define RUAC_LEXER_HPP

#include "syntax_lite/tree/ruac_kwenums.hpp"
#include <vector>
#include <string>

namespace ruac::syntax_lite::tree {

    /**
     * @brief Represents a single lexical token.
     *
     * A simple data structure holding the token's type classification (TokenType)
     * and its string value, produced by the Lexer during tokenization of input lines.
     */
    struct Token {
        kwenums::TokenType type;
        std::string value;
    };

    /**
     * @brief Lexical analyzer that converts input lines into tokens.
     *
     * Provides methods to parse a line into a vector of Token objects, with support
     * for skipping whitespace, extracting string literals, and classifying keywords
     * via the keyword mapping.
     */
    class Lexer {
      private:
        std::string m_line;
        size_t m_pos{0};
        std::vector<Token> m_tokens;

      public:
        Lexer() = default;
        ~Lexer() = default;

      private:
        void skip_whitespace();
        void get_string(std::string &str_);
        void read_token();

      public:
        void parse_line(const std::string &line_);
        auto get_tokens() -> std::vector<Token>;
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_LEXER_HPP
