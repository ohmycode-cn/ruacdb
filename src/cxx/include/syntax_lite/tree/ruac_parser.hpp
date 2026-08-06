/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_parser.hpp
 * src/syntax_lite/tree/ruac_parser.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_PARSER_HPP
#define RUAC_PARSER_HPP

#include "syntax_lite/tree/ruac_synxlist.hpp"
#include "syntax_lite/tree/ruac_kwenums.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <mutex>
#include <vector>

namespace ruac::syntax_lite::tree {

    class Parser {
      private:
        std::unique_ptr<SynxList> M_SYNX_LIST;
        std::unique_ptr<Lexer> M_LEXER;
        std::mutex M_PARSER_MTX;

      private:
        std::vector<Token> M_TOKENS;
        size_t m_pos{0};
        void reset();
        bool has_more();
        auto peek() const -> const Token &;
        auto consume() -> const Token &;
        bool expect(kwenums::TokenType type_, const std::string &value_ = "");

      private:
        bool parse_create_database();
        bool parse_create_table();
        bool parse_use_database();
        bool parse_show_databases();
        bool parse_show_tables();

      public:
        Parser();
        ~Parser() = default;

      private:
        void print_tokens();
        void dispatcher();
        void parser_tokens();

      public:
        void get_query(const std::string &line_);
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_PARSER_HPP
