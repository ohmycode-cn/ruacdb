/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logtime.hpp
 * src/rstd/logsystem/ruac_logtime.cpp
 * @brief Provides a get_time() function for log output timestamp generation.
 */

#pragma once
#ifndef RUAC_LOGTIME_HPP
#define RUAC_LOGTIME_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logtime {

        auto get_time() -> logtype::string;

    }; // namespace logtime

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGTIME_HPP
