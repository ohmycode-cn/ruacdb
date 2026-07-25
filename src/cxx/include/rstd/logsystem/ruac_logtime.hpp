/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logtime.hpp
 * src/rstd/logsystem/ruac_logtime.cpp
 * Description of header file function declaration
 *
 * Declares functions for retrieving formatted timestamps used in log output
 *
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
