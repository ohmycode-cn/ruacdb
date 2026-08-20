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

#include "syntax_lite/tree/ruac_executor.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include "syntax_lite/tree/ruac_node_store.hpp"
#include "syntax_lite/tree/ruac_token_type.hpp"

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace ruac::syntax_lite::tree {

    class Parser {
      private:
        std::unique_ptr<NodeStore> m_node_store;
        std::unique_ptr<Executor> m_executor;
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
        auto expect(token_type::TokenType type_, const std::string &value_ = "") -> bool;

      private:
        auto parse_create_database() -> bool;
        auto parse_create_table() -> bool;
        auto parse_use_database() -> bool;
        auto parse_show_databases() -> bool;
        auto parse_show_database_specific() -> bool;
        auto parse_show_tables() -> bool;

      public:
        explicit Parser(int uid_ = 1);
        ~Parser() = default;

      private:
        void print_tokens();
        void dispatch();
        void parse();

      public:
        void process(const std::string &line_);
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_PARSER_HPP
