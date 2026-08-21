/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/fmt/ruac_format_row.hpp
 * src/syntax_lite/tree/node/fmt/ruac_format_row.cpp
 */

#include "syntax_lite/tree/node/fmt/ruac_format_row.hpp"

#include <sstream>

namespace ruac::syntax_lite::tree::node::fmt {

    auto FormatRow::frow(const FormatRowArgs &args_, bool &ret_) -> std::string {

        const bool newline{args_.m_newline};
        const int colsize{args_.m_col_szie};
        const char corner{args_.m_corners};
        const char coline{args_.m_colline};

        if (0 == colsize) {
            ret_ = false;
            return "";
        };

        std::stringstream ss;
        ss << corner << std::string(colsize, coline) << corner;
        if (newline) {
            ss << '\n';
        }

        ret_ = true;
        return ss.str();
    }

} // namespace ruac::syntax_lite::tree::node::fmt
