/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-09
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/core/ruac_vals.hpp
 * Source File : src/kernel/core/ruac_vals.cpp
 * 
 * File Function Description:
 * Defines the rval variant type alias for polymorphic value storage,
 * supporting integers, floating-point, characters, and string types.
 * 
 */

#pragma once
#ifndef RUAC_VALS_HPP
#define RUAC_VALS_HPP

#include <cstdint>
#include <string>
#include <variant>

namespace ruac::kernel::core {

    namespace vals {
        /**
         * @brief Runtime value type alias for variant storage.
         *
         * Represents a polymorphic value that can hold one of the following types:
         * - std::monostate: null/empty state
         * - Integer types: uint64, uint32, uint16, uint8, int64, int32, int16, int8
         * - Floating-point types: float64 (double), float32 (float)
         * - Character types: char32, char16, char8, char
         * - String type: std::string
         */
        using rval = std::variant<std::monostate, // null
                                  std::uint64_t,  // uint64
                                  std::uint32_t,  // uint32
                                  std::uint16_t,  // uint16
                                  std::uint8_t,   // uint8
                                  std::int64_t,   // int64
                                  std::int32_t,   // int32
                                  std::int16_t,   // int16
                                  std::int8_t,    // int8
                                  double,         // float64
                                  float,          // float32
                                  char32_t,       // char32
                                  char16_t,       // char16
                                  char8_t,        // char8
                                  char,           // char
                                  std::string>;   // string
    } // namespace vals

} // namespace ruac::kernel::core

#endif // RUAC_VALS_HPP