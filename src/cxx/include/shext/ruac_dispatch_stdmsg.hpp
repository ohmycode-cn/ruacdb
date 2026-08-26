/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/shext/ruac_dispatch_stdmsg.hpp
 * src/shext/ruac_dispatch_stdmsg.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_DISPATCH_STDMSG_HPP
#define RUAC_DISPATCH_STDMSG_HPP

#include <string>

namespace ruac::shext {

    auto dispatch_stdmsg(const std::string &line_) -> bool;

} // namespace ruac::shext

#endif // RUAC_DISPATCH_STDMSG_HPP
