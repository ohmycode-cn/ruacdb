/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/shext/ruac_upermission.hpp
 * src/shext/ruac_upermission.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_UPERMISSION_HPP
#define RUAC_UPERMISSION_HPP

#include <string>

namespace ruac::shext::upermission {

    void print_view(std::string user_name_, bool color_ = false);

} // namespace ruac::shext::upermission

#endif // RUAC_UPERMISSION_HPP
