/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/ruac_lowercase_characters.hpp
 * src/rstd/ruac_lowercase_characters.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LOWERCASE_CHARACTERS_HPP
#define RUAC_LOWERCASE_CHARACTERS_HPP

#include <string>

namespace ruac::rstd {

    namespace lowercase_characters {

        void tolower(std::string &str_);

    } // namespace lowercase_characters

} // namespace ruac::rstd

#endif // RUAC_LOWERCASE_CHARACTERS_HPP
