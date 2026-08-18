/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/convert/ruac_lowercase.hpp
 * src/rstd/convert/ruac_lowercase.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LOWERCASE_HPP
#define RUAC_LOWERCASE_HPP

#include <string>

namespace ruac::rstd::convert {

    namespace lowercase {

        void to_lower_string(std::string &str);

    }

} // namespace ruac::rstd::convert

#endif // RUAC_LOWERCASE_HPP
