/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/conversion/ruac_rval_conversion.hpp
 * src/kernel/conversion/ruac_rval_conversion.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RVAL_CONVERSION_HPP
#define RUAC_RVAL_CONVERSION_HPP

#include "kernel/core/ruac_type.hpp"
#include "kernel/core/ruac_vals.hpp"
#include <string>

namespace ruac::kernel::conversion {

    auto rval_to_string(const ruac::kernel::core::vals::rval &rval_) -> std::string;
    auto string_to_rval(const std::string &string_rval_, ruac::kernel::core::type::rtype rtype_) -> ruac::kernel::core::vals::rval;

} // namespace ruac::kernel::conversion

#endif // RUAC_RVAL_CONVERSION_HPP
