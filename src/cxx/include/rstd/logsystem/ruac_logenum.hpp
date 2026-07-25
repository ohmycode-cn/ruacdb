/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logenum.hpp
 * src/rstd/logsystem/ruac_logenum.cpp
 * Description of header file function declaration
 *
 * Defines enumerations for log levels, output modes, and format types used throughout the log system
 *
 */

#pragma once
#ifndef RUAC_LOGENUM_HPP
#define RUAC_LOGENUM_HPP

namespace ruac::rstd::logsystem {

    namespace logenum {

        enum class Level {
            DEBUG = 0,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

        enum class Output {
            CONSOLE = 0,
            FILE
        };

        enum class Format {
            TEXT = 0,
            JSON,
            XML
        };

    } // namespace logenum

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGENUM_HPP
