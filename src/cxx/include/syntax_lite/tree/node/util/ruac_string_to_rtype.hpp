/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/util/ruac_string_to_rtype.hpp
 * src/syntax_lite/tree/node/util/ruac_string_to_rtype.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_STRING_TO_RTYPE_HPP
#define RUAC_STRING_TO_RTYPE_HPP

#include "kernel/core/ruac_type.hpp"

#include <string>
#include <vector>

namespace ruac::syntax_lite::tree::node::util {

    using rtype = ruac::kernel::core::type::rtype;
    auto string_to_rtype(const std::vector<std::string> &stypes_) -> std::vector<rtype>;
    auto rtype_to_string(const std::vector<rtype> &rtypes_) -> std::vector<std::string>;

} // namespace ruac::syntax_lite::tree::node::util

#endif // RUAC_STRING_TO_RTYPE_HPP
