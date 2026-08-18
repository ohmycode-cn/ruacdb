/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/convert/ruac_lowercase.hpp
 * src/rstd/convert/ruac_lowercase.cpp
 */

#include "rstd/convert/ruac_lowercase.hpp"

namespace ruac::rstd::convert {

    namespace lowercase {

        /**
         * @brief Convert a string to lowercase.
         *
         * @param str_ The string to convert.
         */
        void to_lower_string(std::string &str_) {
            str_.resize_and_overwrite(str_.size(), [](char *buf, std::size_t n) -> std::size_t {
                for (std::size_t i = 0; i < n; ++i) {
                    buf[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(buf[i])));
                }
                return n;
            });
        }

    } // namespace lowercase

} // namespace ruac::rstd::convert
