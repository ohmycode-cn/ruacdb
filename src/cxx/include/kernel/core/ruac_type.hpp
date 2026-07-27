/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-09
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/core/ruac_type.hpp
 * Source File : src/kernel/core/ruac_type.cpp
 * 
 * File Function Description:
 * Defines the rtype enumeration for runtime type identification, supporting
 * all data types used in the RUAC variant value system.
 * 
 */

#pragma once
#ifndef RUAC_TYPE_HPP
#define RUAC_TYPE_HPP

namespace ruac::kernel::core {

    namespace type {
        /**
         * @brief Runtime type enumeration for variant type identification.
         *
         * Defines all supported data types in the RUAC database system.
         * Used to identify the active type in ruac::core::vals::rval variant.
         */
        enum class rtype {
            NONE,   // null/empty state
            INT64U, // unsigned 64-bit integer
            INT32U, // unsigned 32-bit integer
            INT16U, // unsigned 16-bit integer
            INT8U,  // unsigned 8-bit integer
            INT64,  // signed 64-bit integer
            INT32,  // signed 32-bit integer
            INT16,  // signed 16-bit integer
            INT8,   // signed 8-bit integer
            DOUBLE, // 64-bit floating-point
            FLOAT,  // 32-bit floating-point
            CHAR32, // UTF-32 character
            CHAR16, // UTF-16 character
            CHAR8,  // UTF-8 character
            CHAR,   // ASCII character
            STRING, // std::string
            ERROR_TYPE
        };
    } // namespace type

} // namespace ruac::kernel::core

#endif // RUAC_TYPE_HPP