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

#include "syntax_lite/tree/ruac_token_type.hpp"
#include <string>
#include <vector>

namespace ruac::syntax_lite::tree {

    /**
     * @brief Represents a single lexical token.
     *
     * A simple data structure holding the token's type classification (TokenType)
     * and its string value, produced by the Lexer during tokenization of input lines.
     */
    struct Token {
        token_type::TokenType type;
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
        int m_tmp_debug_count{0};

      private:
        std::vector<Token> m_tokens;
        std::string m_line;
        size_t m_pos{0};

      public:
        Lexer() = default;
        ~Lexer() = default;

      private:
        void skip_whitespace();
        void read_word(std::string &str_);
        void read_token();

      public:
        void tokenize(const std::string &line_);
        auto tokens() -> std::vector<Token>;
        void out_tokens();
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_LEXER_HPP
