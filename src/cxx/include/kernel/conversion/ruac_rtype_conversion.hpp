/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/conversion/ruac_rtype_conversion.hpp
 * src/kernel/conversion/ruac_rtype_conversion.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RTYPE_CONVERSION_HPP
#define RUAC_RTYPE_CONVERSION_HPP

#include "kernel/core/ruac_type.hpp"

#include <string>

namespace ruac::kernel::conversion {

    auto rtype_to_string(const ruac::kernel::core::type::rtype &rtype_) -> std::string;
    auto string_to_rtype(const std::string &string_type_) -> ruac::kernel::core::type::rtype;

} // namespace ruac::kernel::conversion

#endif // RUAC_RTYPE_CONVERSION_HPP
