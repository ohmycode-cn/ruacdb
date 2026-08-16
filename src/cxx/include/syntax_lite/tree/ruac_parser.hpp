/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_parser.hpp
 * src/syntax_lite/tree/ruac_parser.cpp
 *
 * @brief Defines the Parser class for tokenizing and parsing RUAC SQL-like queries with thread-safe access.
 */

#pragma once
#ifndef RUAC_PARSER_HPP
#define RUAC_PARSER_HPP

#include "syntax_lite/tree/ruac_kwenums.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include "syntax_lite/tree/ruac_prexec.hpp"
#include "syntax_lite/tree/ruac_synxlist.hpp"
#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace ruac::syntax_lite::tree {

    class Parser {
      private:
        std::unique_ptr<SynxList> M_SYNX_LIST;
        std::unique_ptr<PrExec> M_PREEXEC;
        std::unique_ptr<Lexer> M_LEXER;
        std::mutex M_PARSER_MTX;

      private:
        std::string M_SPACE_SEVEN{"       "};
        bool m_parser_success{false};

      private:
        std::vector<Token> M_TOKENS;
        size_t m_pos{0};
        void reset();
        auto has_more() -> bool;
        auto peek() const -> const Token &;
        auto consume() -> const Token &;
        auto expect(kwenums::TokenType type_, const std::string &value_ = "") -> bool;

      private:
        auto parse_create_database() -> bool;
        auto parse_create_table() -> bool;
        auto parse_use_database() -> bool;
        auto parse_show_databases() -> bool;
        auto parse_show_database_specific() -> bool;
        auto parse_show_tables() -> bool;

      public:
        Parser();
        ~Parser() = default;

      private:
        void print_tokens();
        void dispatcher();
        void parser();

      public:
        void get_query(const std::string &line_);
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_PARSER_HPP
