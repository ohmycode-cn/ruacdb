/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_xml.hpp
 * src/rstd/logsystem/ruac_format_xml.cpp
 * Description of header file function declaration
 * Declares the FormatXML class, a concrete implementation of the Format
 * interface for the RUAC log system. FormatXML serializes log entries into
 * XML element strings, where each entry is wrapped in a <record> element
 * containing TIME, LEVEL, SEQUENCE, MESSAGE, FILE, and LINE child elements.
 * A private template helper fmt generates paired open/close
 * XML tags with consistent indentation.
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
        auto fmt(const logtype::StringMap &map, const logtype::String &key_, const V &val_) -> logtype::String;

      public:
        FormatXML() = default;
        ~FormatXML() = default;

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

#endif // RUAC_FORMAT_XML_HPP
