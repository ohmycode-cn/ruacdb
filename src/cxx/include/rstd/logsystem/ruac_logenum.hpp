/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logenum.hpp
 * src/rstd/logsystem/ruac_logenum.cpp
 * @brief Defines enumerations for log levels, output modes, and format types.
 */

#pragma once
#ifndef RUAC_LOGENUM_HPP
#define RUAC_LOGENUM_HPP

namespace ruac::rstd::logsystem {

    namespace logenum {

        /**
         * @brief Log severity levels.
         *
         * Defines the severity hierarchy from DEBUG (lowest) to FATAL (highest).
         */
        enum class Level {
            DEBUG = 0,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

        /**
         * @brief Log output destination modes.
         *
         * Specifies whether log output is directed to the console or to a file.
         */
        enum class Output {
            CONSOLE = 0,
            FILE
        };

        /**
         * @brief Log output format types.
         *
         * Defines the serialization format for log messages: plain text, JSON, or XML.
         */
        enum class Format {
            TEXT = 0,
            JSON,
            XML
        };

    } // namespace logenum

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGENUM_HPP
