/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_json.hpp
 * src/rstd/logsystem/ruac_format_json.cpp
 *
 * @brief Defines the JSON log formatter that serializes log entries into structured JSON strings.
 *
 */

#pragma once
#ifndef RUAC_FORMAT_JSON_HPP
#define RUAC_FORMAT_JSON_HPP

#include "rstd/logsystem/ruac_format.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <mutex>

namespace ruac::rstd::logsystem {

    /**
     * @brief JSON log formatter that serializes log entries into structured
     *        JSON object strings with configurable key-value formatting.
     */
    class FormatJson : public Format {
      private:
        std::mutex M_FORMAT_JSON_MTX;
        template <typename V>
        auto fmt(const logtype::strmap &strmap_, const logtype::string &key_, const V &val_) -> logtype::string;

      public:
        FormatJson() = default;
        ~FormatJson() override = default;

      public:
        auto format(const logtype::strmap &strmap_,
                    const logtype::string &time_,
                    const logtype::string &level_,
                    const logtype::seqnum &sequence_,
                    const logtype::string &message_,
                    const logtype::string &file_,
                    logtype::sd_int line_) -> logtype::string override;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_FORMAT_JSON_HPP
