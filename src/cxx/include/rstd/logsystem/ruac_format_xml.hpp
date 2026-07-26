/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_xml.hpp
 * src/rstd/logsystem/ruac_format_xml.cpp
 * Description of header file function declaration
 *
 * Defines the XML log formatter that serializes log entries into structured XML elements
 *
 */

#pragma once
#ifndef RUAC_FORMAT_XML_HPP
#define RUAC_FORMAT_XML_HPP

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_format.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief XML log formatter that serializes log entries into structured
     *        XML element strings with configurable tag formatting.
     */
    class FormatXML : public Format {
      private:
        template <typename V>
        auto fmt(const logtype::strmap &map, const logtype::string &key_, const V &val_) -> logtype::string;

      public:
        FormatXML() = default;
        ~FormatXML() = default;

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

#endif // RUAC_FORMAT_XML_HPP
