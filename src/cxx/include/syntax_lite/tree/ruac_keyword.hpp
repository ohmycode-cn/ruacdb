/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_keyword.hpp
 * src/syntax_lite/tree/ruac_keyword.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_KEYWORD_HPP
#define RUAC_KEYWORD_HPP

namespace ruac::syntax_lite::tree {

    namespace keyword {

        namespace datatype {

            constexpr auto G_DATETIME{"datetime"};
            constexpr auto G_DATE{"date"};
            constexpr auto G_TIME{"time"};
            constexpr auto G_INT{"int"};
            constexpr auto G_FLOAT{"float"};
            constexpr auto G_STRING{"string"};
            constexpr auto G_BOOL{"bool"};
            constexpr auto G_NULL{"null"};
            constexpr auto G_CHAR{"char"};

        } // namespace datatype

        namespace object {

            constexpr auto G_DATABASES{"databases"};
            constexpr auto G_DATABASE{"database"};
            constexpr auto G_TABLES{"tables"};
            constexpr auto G_TABLE{"table"};
            constexpr auto G_COLUMNS{"columns"};
            constexpr auto G_COLUMN{"column"};
            constexpr auto G_ROWS{"rows"};
            constexpr auto G_ROW{"row"};

        } // namespace object

        namespace attribute {

            constexpr auto G_CREATE{"create"};
            constexpr auto G_REMOVE{"remove"};
            constexpr auto G_SYNC{"sync"};
            constexpr auto G_INSERT{"insert"};
            constexpr auto G_MODIFY{"modify"};
            constexpr auto G_VALUE{"value"};
            constexpr auto G_SHOW{"show"};
            constexpr auto G_GET{"get"};
            constexpr auto G_SET{"set"};
            constexpr auto G_AND{"and"};
            constexpr auto G_OR{"or"};
            constexpr auto G_USE{"use"};
            constexpr auto G_SELECT{"select"};
            constexpr auto G_FROM{"from"};

        } // namespace attribute

        namespace symbol {

            constexpr auto G_SEMICOLON{";"};
            constexpr auto G_L_PARENTHESIS{"("};
            constexpr auto G_R_PARENTHESIS{")"};
            constexpr auto G_STAR{"*"};
            constexpr auto G_COMMA{","};
            constexpr auto G_EQUAL{"="};
            constexpr auto G_COLON{":"};
            constexpr auto G_L_BRACKET{"["};
            constexpr auto G_R_BRACKET{"]"};
            constexpr auto G_L_BRACE{"{"};
            constexpr auto G_R_BRACE{"}"};
            constexpr auto G_QUOTE{"'"};
            constexpr auto G_DOUBLE_QUOTE{"\""};
            constexpr auto G_COMMENT{"--"};
            constexpr auto G_WHITESPACE{" "};
            constexpr auto G_WHITESPACE_CHAR{' '};
            constexpr auto G_GT{">"};
            constexpr auto G_LT{"<"};
            constexpr auto G_GTE{">="};
            constexpr auto G_LTE{"<="};
            constexpr auto G_NOT_EQUAL{"!="};
            constexpr auto G_IS{"is"};
            constexpr auto G_NOT{"not"};

        } // namespace symbol

    } // namespace keyword

} // namespace ruac::syntax_lite::tree

#endif // RUAC_KEYWORD_HPP
