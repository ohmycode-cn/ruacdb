/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logtype.hpp
 * src/rstd/logsystem/ruac_logtype.cpp
 * Description of header file function declaration
 *
 * Defines type aliases used in the log system including string maps, integer types, and template map utilities
 *
 */

#pragma once
#ifndef RUAC_LOGTYPE_HPP
#define RUAC_LOGTYPE_HPP

#include <unordered_map>
#include <string>

namespace ruac::rstd::logsystem {

    namespace logtype {

        using strmap = std::unordered_map<std::string, std::string>;
        using string = std::string;
        using seqnum = unsigned long long;
        using ud_int = unsigned int;
        using sd_int = int;
        using ud_lng = unsigned long long;
        using sd_lng = long long;
        using ud_llg = unsigned long long;
        using sd_llg = long long;
        template <typename K, typename V>
        using tepmap = std::unordered_map<K, V>;

    }; // namespace logtype

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTYPE_HPP
