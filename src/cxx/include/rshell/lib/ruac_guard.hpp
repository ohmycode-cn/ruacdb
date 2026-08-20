/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/lib/ruac_guard.hpp
 * src/rshell/lib/ruac_guard.cpp
 *
 * @brief Declares uid_permission_guard() for UID-based access control with optional group membership checks.
 */

#pragma once
#ifndef RUAC_GUARD_HPP
#define RUAC_GUARD_HPP

#include <string>

namespace ruac::rshell::lib::guard {

    auto uid_permission_guard(const int uid_, const std::string &msg_, const std::string &guard_group_, bool out_msg_ = true) -> bool;

} // namespace ruac::rshell::lib::guard

#endif // RUAC_GUARD_HPP
