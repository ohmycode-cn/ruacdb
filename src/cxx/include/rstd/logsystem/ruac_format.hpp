/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format.hpp
 * src/rstd/logsystem/ruac_format.cpp
 * Description of header file function declaration
 * Abstract interface for log message formatting strategies.
 *
 */

#pragma once
#ifndef RUAC_FORMAT_HPP
#define RUAC_FORMAT_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Abstract interface for log message formatting.
     *
     * Implementations define how raw log components (level, time, message,
     * source location, etc.) are assembled into a single output string.
     * Concrete formatters (e.g. plain-text, JSON, CSV) should derive from
     * this class and override format().
     */
    class Format {
      public:
        /**
         * @brief Format a log entry into a string.
         *
         * @param strmap_   Key-value pairs for user-defined fields.
         * @param time_     Formatted timestamp of the log entry.
         * @param level_    Log severity level as a string (e.g. "INFO", "ERROR").
         * @param sequence_ Monotonically increasing sequence number.
         * @param message_  The log message body.
         * @param file_     Source file name where the log was emitted.
         * @param line_     Source line number where the log was emitted.
         * @return The fully formatted log string.
         */
        virtual auto format(const logtype::StringMap &strmap_,
                            const logtype::String &time_,
                            const logtype::String &level_,
                            const logtype::Seqnum &sequence_,
                            const logtype::String &message_,
                            const logtype::String &file_,
                            const logtype::Int line_) -> logtype::String = 0;

        virtual ~Format() = default;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_HPP
