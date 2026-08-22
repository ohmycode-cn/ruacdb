/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/fmt/ruac_format_col.hpp
 * src/syntax_lite/tree/node/fmt/ruac_format_col.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_FORMAT_COL_HPP
#define RUAC_FORMAT_COL_HPP

#include <string>
#include <mutex>

namespace ruac::syntax_lite::tree::node::fmt {

    struct FormatColArgs {
        char m_right_char{'|'};
        char m_left_char{'|'};
        bool m_newline{true};
        int m_col_max_size{0};
    };

    class FormatCol {
      private:
        FormatColArgs m_format_args;

      public:
        FormatCol() = default;
        ~FormatCol() = default;

      public:
        auto fcol(const FormatColArgs &args_, bool &ret_, const std::string &str_) -> std::string;

      public:
        void fset_member_args(const FormatColArgs &args_);
        auto fcol(const std::string &str_) -> std::string;
    };

} // namespace ruac::syntax_lite::tree::node::fmt

#endif // RUAC_FORMAT_COL_HPP
