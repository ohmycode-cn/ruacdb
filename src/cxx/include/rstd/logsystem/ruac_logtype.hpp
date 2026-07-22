/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logtype.hpp
 * src/rstd/logsystem/ruac_logtype.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LOGTYPE_HPP
#define RUAC_LOGTYPE_HPP

#include <unordered_map>
#include <string_view>
#include <string>

namespace ruac::rstd::logsystem {

    namespace logtype {

        using StringMap = std::unordered_map<std::string, std::string>;
        using String = std::string;
        using StringView = std::string_view;
        using UInt = unsigned int;
        using Int = signed int;
        using ULong = unsigned long;
        using Long = signed long;
        using Bool = bool;
        using ULongLong = unsigned long long;
        using LongLong = signed long long;
        using SizeT = size_t;
        using Seqnum = unsigned long long;

    } // namespace logtype

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTYPE_HPP
