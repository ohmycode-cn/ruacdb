/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/convert/ruac_rmspace.hpp
 * src/rstd/convert/ruac_rmspace.cpp
 */

#include "rstd/convert/ruac_rmspace.hpp"
#include <algorithm>
#include <cctype>
#include <string_view>

namespace ruac::rstd::convert {

    namespace {

        constexpr auto trim_view(std::string_view sv_) noexcept -> std::string_view {
            auto is_space = [](unsigned char c) { return std::isspace(c); };
            auto start = std::find_if_not(sv_.begin(), sv_.end(), is_space);
            if (start == sv_.end()) {
                return {};
            }
            auto end = std::find_if_not(
                sv_.rbegin(),
                sv_.rend(),
                is_space);
            return {start, end.base()};
        }

    } // namespace

    namespace rmspace {

        /**
         * @brief Remove string heading and trailing spaces.
         *
         * @param str_ The string to remove heading and trailing spaces from.
         */
        void remove_string_spaces(std::string &str_) {
            auto trimmed = trim_view(str_);
            str_.assign(trimmed.data(), trimmed.size());
        }

    } // namespace rmspace

} // namespace ruac::rstd::convert
