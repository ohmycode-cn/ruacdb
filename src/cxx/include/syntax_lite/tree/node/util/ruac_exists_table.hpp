/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/util/ruac_exists_table.hpp
 * src/syntax_lite/tree/node/util/ruac_exists_table.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_EXISTS_TABLE_HPP
#define RUAC_EXISTS_TABLE_HPP

#include <string>

namespace ruac::syntax_lite::tree::node::util {

    auto exist_table(const std::string &dbname_, const std::string &tbname_, const int uid_) -> bool;

} // namespace ruac::syntax_lite::tree::node::util

#endif // RUAC_EXISTS_TABLE_HPP
