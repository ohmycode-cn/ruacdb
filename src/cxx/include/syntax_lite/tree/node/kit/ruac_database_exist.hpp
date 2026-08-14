/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/kit/ruac_database_exist.hpp
 * src/syntax_lite/tree/node/kit/ruac_database_exist.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_DATABASE_EXIST_HPP
#define RUAC_DATABASE_EXIST_HPP

#include <string>

namespace ruac::syntax_lite::tree::node::kit {

    auto database_exist(const std::string &name_, const int uid_) -> bool;

} // namespace ruac::syntax_lite::tree::node::kit

#endif // RUAC_DATABASE_EXIST_HPP
