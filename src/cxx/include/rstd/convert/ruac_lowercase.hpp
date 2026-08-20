/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/convert/ruac_lowercase.hpp
 * src/rstd/convert/ruac_lowercase.cpp
 *
 * @brief Declares the to_lower_string() utility function for in-place lowercasing of strings.
 */

#pragma once
#ifndef RUAC_LOWERCASE_HPP
#define RUAC_LOWERCASE_HPP

#include <string>

namespace ruac::rstd::convert {

    namespace lowercase {

        void to_lower_string(std::string &str_);

    }

} // namespace ruac::rstd::convert

#endif // RUAC_LOWERCASE_HPP
