/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/lib/ruac_legal_characters.hpp
 * src/login/lib/ruac_legal_characters.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LEGAL_CHARACTERS_HPP
#define RUAC_LEGAL_CHARACTERS_HPP

#include <string>

namespace ruac::login::lib {

    auto legal_char(std::string &str_) -> bool;

} // namespace ruac::login::lib

#endif // RUAC_LEGAL_CHARACTERS_HPP
