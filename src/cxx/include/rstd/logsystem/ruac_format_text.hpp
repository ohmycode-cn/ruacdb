/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_text.hpp
 * src/rstd/logsystem/ruac_format_text.cpp
 * Description of header file function declaration
 *
 * Defines the plain-text log formatter for human-readable log output
 *
 */

#pragma once
#ifndef RUAC_FORMAT_TEXT_HPP
#define RUAC_FORMAT_TEXT_HPP

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Plain-text log formatter that serializes log entries into
     *        human-readable two-line text segments with consistent indentation.
     */
    class FormatText : public Format {
      public:
        FormatText() = default;
        ~FormatText() = default;

      public:
        auto format(const logtype::strmap &strmap_,
                    const logtype::string &time_,
                    const logtype::string &level_,
                    const logtype::seqnum &sequence_,
                    const logtype::string &message_,
                    const logtype::string &file_,
                    const logtype::sd_int line_) -> logtype::string;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_TEXT_HPP
