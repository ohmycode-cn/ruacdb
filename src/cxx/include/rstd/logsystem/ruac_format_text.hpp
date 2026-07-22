/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_text.hpp
 * src/rstd/logsystem/ruac_format_text.cpp
 * Description of header file function declaration
 * Declares the FormatText class, a concrete implementation of the Format
 * interface for the RUAC log system. FormatText serializes log entries into
 * plain-text line pairs, where the first line contains the timestamp, level,
 * sequence number, and source location, and the second line indents the
 * message content under a labeled brace tag.
 */

#pragma once
#ifndef RUAC_FORMAT_TEXT_HPP
#define RUAC_FORMAT_TEXT_HPP

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
        auto format(const logtype::StringMap &strmap_,
                    const logtype::String &time_,
                    const logtype::String &level_,
                    const logtype::Seqnum &sequence_,
                    const logtype::String &message_,
                    const logtype::String &file_,
                    const logtype::Int line_) -> logtype::String;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_TEXT_HPP
