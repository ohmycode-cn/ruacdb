/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_keyword_map.hpp
 *
 * @brief Defines keyword-to-TokenType mapping for lexer classification.
 */

#pragma once
#ifndef RUAC_KEYWORD_MAP_HPP
#define RUAC_KEYWORD_MAP_HPP

#include "syntax_lite/tree/ruac_keyword.hpp"
#include "syntax_lite/tree/ruac_token_type.hpp"
#include <string>
#include <unordered_map>

namespace ruac::syntax_lite::tree {

    namespace keyword_map {

        namespace k_datatype = keyword::datatype;
        namespace k_object = keyword::object;
        namespace k_attribute = keyword::attribute;
        namespace k_symbol = keyword::symbol;
        namespace tt = token_type;
        using tt::TokenType;

        /**
         * @brief Mapping from keyword strings to their TokenType classifications.
         *
         * An unordered hash map that associates each defined keyword constant
         * (datatype, object, attribute, symbol) with its corresponding TokenType
         * enumeration value for fast lookup during lexical analysis.
         */
        const std::unordered_map<std::string, tt::TokenType> maps{
            // datatype
            {k_datatype::G_DATETIME, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_DATE, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_TIME, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_INT, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_FLOAT, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_STRING, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_BOOL, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_NULL, TokenType::KEYWORD_DATATYPE},
            {k_datatype::G_CHAR, TokenType::KEYWORD_DATATYPE},
            // object
            {k_object::G_DATABASES, TokenType::KEYWORD_OBJECT},
            {k_object::G_DATABASE, TokenType::KEYWORD_OBJECT},
            {k_object::G_TABLES, TokenType::KEYWORD_OBJECT},
            {k_object::G_TABLE, TokenType::KEYWORD_OBJECT},
            {k_object::G_COLUMNS, TokenType::KEYWORD_OBJECT},
            {k_object::G_COLUMN, TokenType::KEYWORD_OBJECT},
            {k_object::G_ROWS, TokenType::KEYWORD_OBJECT},
            {k_object::G_ROW, TokenType::KEYWORD_OBJECT},
            // attribute
            {k_attribute::G_CREATE, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_REMOVE, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_SYNC, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_INSERT, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_MODIFY, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_VALUE, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_SHOW, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_GET, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_SET, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_AND, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_OR, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_USE, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_SELECT, TokenType::KEYWORD_ATTRIBUTE},
            {k_attribute::G_FROM, TokenType::KEYWORD_ATTRIBUTE},
            // symbol
            {k_symbol::G_SEMICOLON, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_L_PARENTHESIS, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_R_PARENTHESIS, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_STAR, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_COMMA, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_EQUAL, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_COLON, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_L_BRACKET, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_R_BRACKET, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_L_BRACE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_R_BRACE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_QUOTE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_DOUBLE_QUOTE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_COMMENT, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_WHITESPACE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_GT, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_LT, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_GTE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_LTE, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_NOT_EQUAL, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_IS, TokenType::KEYWORD_SYMBOL},
            {k_symbol::G_NOT, TokenType::KEYWORD_SYMBOL},
        };

    } // namespace keyword_map

} // namespace ruac::syntax_lite::tree

#endif // RUAC_KEYWORD_MAP_HPP
