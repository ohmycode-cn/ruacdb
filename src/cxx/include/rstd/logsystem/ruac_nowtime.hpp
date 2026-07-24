/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_nowtime.hpp
 * src/rstd/logsystem/ruac_nowtime.cpp
 * Description of header file function declaration
 * Utility for retrieving the current formatted timestamp.
 *
 */

#pragma once
#ifndef RUAC_NOWTIME_HPP
#define RUAC_NOWTIME_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace nowtime {

        auto get_time() -> logtype::String;

    } // namespace nowtime

} // namespace ruac::rstd::logsystem

#endif // RUAC_NOWTIME_HPP
