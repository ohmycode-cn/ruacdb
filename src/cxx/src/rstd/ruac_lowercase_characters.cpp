/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/ruac_lowercase_characters.hpp
 * src/rstd/ruac_lowercase_characters.cpp
 */

#include "rstd/ruac_lowercase_characters.hpp"

namespace ruac::rstd {

    namespace lowercase_characters {

        void tolower(std::string &str_) {
            for (auto &c : str_) {
                c = std::tolower(c);
            }
        }

    } // namespace lowercase_characters

} // namespace ruac::rstd
