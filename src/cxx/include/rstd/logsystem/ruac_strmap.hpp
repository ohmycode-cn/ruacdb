/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_strmap.hpp
 * src/rstd/logsystem/ruac_strmap.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_STRMAP_HPP
#define RUAC_STRMAP_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace strmap {

        auto get_ansi_map(const logtype::Bool enable_ce_ = true, const logtype::Bool enable_ht_ = false,
                          const logtype::Bool enable_bf_ = false) -> logtype::StringMap;
        auto get_text_map() -> logtype::StringMap;

    } // namespace strmap

} // namespace ruac::rstd::logsystem

#endif // RUAC_STRMAP_HPP
