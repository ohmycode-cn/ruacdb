/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_json.hpp
 * src/rstd/logsystem/ruac_format_json.cpp
 * JSON-formatted log entry serializer with configurable key-value formatting.
 *
 */

#pragma once
#include "rstd/logsystem/ruac_logtype.hpp"
#ifndef RUAC_FORMAT_JSON_HPP
#define RUAC_FORMAT_JSON_HPP

#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief JSON log formatter that serializes log entries into structured
     *        JSON object strings with configurable key-value formatting.
     */
    class FormatJson : public Format {
      private:
        template <typename V>
        auto fmt(const logtype::StringMap &strmap_, const logtype::String &key_, const V &val_) -> logtype::String;

      public:
        FormatJson() = default;
        ~FormatJson() = default;

      public:
        auto format(const logtype::StringMap &strmap_,
                    const logtype::String &time_,
                    const logtype::String &level_,
                    const logtype::Seqnum &sequence_,
                    const logtype::String &message_,
                    const logtype::String &file_,
                    const logtype::Int line_) -> logtype::String override;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_JSON_HPP
