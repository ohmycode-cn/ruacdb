/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/fmt/ruac_format_row.hpp
 * src/syntax_lite/tree/node/fmt/ruac_format_row.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_FORMAT_ROW_HPP
#define RUAC_FORMAT_ROW_HPP

#include <string>
#include <mutex>

namespace ruac::syntax_lite::tree::node::fmt {

    struct FormatRowArgs {
        bool m_newline{true};
        char m_corners{'+'};
        char m_rowline{'-'};
        int m_row_szie{0};
    };

    class FormatRow {
      private:
        // FormatRowArgs m_format_args;
        std::mutex M_FORMAT_ROW_MTX;

      public:
        FormatRow() = default;
        ~FormatRow() = default;

      public:
        auto frow(const FormatRowArgs &args_, bool &ret_) -> std::string;
    };

} // namespace ruac::syntax_lite::tree::node::fmt

#endif // RUAC_FORMAT_ROW_HPP
