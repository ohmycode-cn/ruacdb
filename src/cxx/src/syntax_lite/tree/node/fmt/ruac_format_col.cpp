/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/fmt/ruac_format_col.hpp
 * src/syntax_lite/tree/node/fmt/ruac_format_col.cpp
 */

#include "syntax_lite/tree/node/fmt/ruac_format_col.hpp"

#include <sstream>
#include <iomanip>

namespace ruac::syntax_lite::tree::node::fmt {

    auto FormatCol::fcol(const FormatColArgs &args_, bool &ret_, const std::string &str_) -> std::string {
        int col_max_size = args_.m_col_max_size;
        char right_char = args_.m_right_char;
        char left_char = args_.m_left_char;
        bool newline = args_.m_newline;

        if (col_max_size <= 0) {
            ret_ = false;
            return "";
        }

        std::stringstream ss;
        ss << left_char << " ";
        ss << std::left << std::setw(col_max_size);
        ss << str_;
        ss << " " << right_char;
        if (newline) {
            ss << "\n";
        }

        ret_ = true;
        return ss.str();
    }

    void FormatCol::fset_member_args(const FormatColArgs &args_) {
        m_format_args = args_;
    }

    auto FormatCol::fcol(const std::string &str_) -> std::string {
        std::stringstream ss;
        ss << m_format_args.m_left_char << " ";
        ss << std::left << std::setw(m_format_args.m_col_max_size);
        ss << str_;
        ss << " " << m_format_args.m_right_char;
        if (m_format_args.m_newline) {
            ss << "\n";
        }
        return ss.str();
    }

} // namespace ruac::syntax_lite::tree::node::fmt
