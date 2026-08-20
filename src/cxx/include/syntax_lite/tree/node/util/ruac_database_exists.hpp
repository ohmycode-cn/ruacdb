/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/util/ruac_database_exists.hpp
 * src/syntax_lite/tree/node/util/ruac_database_exists.cpp
 *
 * @brief Declares the exist_database() utility function for checking database existence.
 */

#pragma once
#ifndef RUAC_DATABASE_EXISTS_HPP
#define RUAC_DATABASE_EXISTS_HPP

#include <string>

namespace ruac::syntax_lite::tree::node::util {

    auto exist_database(const std::string &name_, const int uid_) -> bool;

} // namespace ruac::syntax_lite::tree::node::util

#endif // RUAC_DATABASE_EXISTS_HPP
