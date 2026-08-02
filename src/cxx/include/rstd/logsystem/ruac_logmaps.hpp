/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logmaps.hpp
 * src/rstd/logsystem/ruac_logmaps.cpp
 * Description of header file function declaration
 *
 * Declares functions for retrieving text format maps and ANSI color maps used in log message formatting
 *
 */

#pragma once
#ifndef RUAC_LOGMAPS_HPP
#define RUAC_LOGMAPS_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logmaps {

        auto get_text_map() -> logtype::strmap;
        auto get_ansi_map(bool enable_ce_,  bool enable_ht_, bool enable_bf_) -> logtype::strmap;
        auto get_text_level_map() -> logtype::strmap;
        auto get_ansi_level_map() -> logtype::strmap;

    } // namespace logmaps

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGMAPS_HPP
