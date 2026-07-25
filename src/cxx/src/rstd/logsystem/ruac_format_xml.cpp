/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_xml.hpp
 * src/rstd/logsystem/ruac_format_xml.cpp
 */

#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {
        namespace k = logkeys::token_k;
        namespace v = logkeys::token_v;
    } // namespace

    /**
     * @brief Formats a single XML element line with open/close tags and indentation.
     *
     * @tparam V   Type of the value to format (e.g. String, udll, sdit).
     * @param strmap_  Key-value map containing formatting token (angle brackets, slash, etc.).
     * @param key_   The XML element name token (e.g. k::G_XML_TIME).
     * @param val_   The value to be placed between the open and close tags.
     *
     * @return A formatted XML element line as a string.
     *
     * @details e.g.
     * <space:8><key>val</key>
     */
    template <typename V>
    auto FormatXML::fmt(const logtype::strmap &strmap_, const logtype::string &key_, const V &val_) -> logtype::string {
        std::stringstream ss;
        logtype::strmap map{strmap_};
        ss << v::G_SPACE_08;
        ss << map.at(k::G_LT);
        ss << map.at(key_);
        ss << map.at(k::G_GT);
        ss << val_;
        ss << map.at(k::G_LT);
        ss << map.at(k::G_SLASH);
        ss << map.at(key_);
        ss << map.at(k::G_GT);
        return ss.str();
    }

    /**
     * @brief Formats a single log entry as an XML <record> element string.
     *
     * @param strmap_    Key-value map containing formatting token (angle brackets, slash, etc.).
     * @param time_    Timestamp string for the TIME child element.
     * @param level_   Log level string (e.g. "INFO", "ERROR") for the LEVEL child element.
     * @param sequence_  Monotonically increasing sequence number for the SEQUENCE child element.
     * @param message_ The log message content for the MESSAGE child element.
     * @param file_    Source file name for the FILE child element.
     * @param line_    Source line number for the LINE child element.
     *
     * @return A formatted XML <record> segment as a string, ready to be embedded
     *         in the parent log structure.
     *
     * @details e.g.
     * <space:4><record><next_line>
     * <space:4><space:4><time>time</time><next_line>
     * <space:4><space:4><level>level</level><next_line>
     * <space:4><space:4><sequence>sequence</sequence><next_line>
     * <space:4><space:4><message>message</message><next_line>
     * <space:4><space:4><file>file</file><next_line>
     * <space:4><space:4><line>line</line><next_line>
     * <space:4></record>
     */
    auto FormatXML::format(const logtype::strmap &strmap_,
                           const logtype::string &time_,
                           const logtype::string &level_,
                           const logtype::seqnum &sequence_,
                           const logtype::string &message_,
                           const logtype::string &file_,
                           const logtype::sd_int line_) -> logtype::string {
        std::stringstream ss;
        logtype::strmap map{strmap_};

        ss << v::G_SPACE_04;
        ss << map.at(k::G_LT);
        ss << map.at(k::G_XML_RECORD);
        ss << map.at(k::G_GT);
        ss << v::G_NEXT_LINE;
        // time.
        ss << fmt(map, k::G_XML_TIME, time_);
        ss << v::G_NEXT_LINE;
        // level.
        ss << fmt(map, k::G_XML_LEVEL, level_);
        ss << v::G_NEXT_LINE;
        // sequence.
        ss << fmt(map, k::G_XML_SEQUENCE, sequence_);
        ss << v::G_NEXT_LINE;
        // message.
        ss << fmt(map, k::G_XML_MESSAGE, message_);
        ss << v::G_NEXT_LINE;
        // file.
        ss << fmt(map, k::G_XML_FILE, file_);
        ss << v::G_NEXT_LINE;
        // line.
        ss << fmt(map, k::G_XML_LINE, line_);
        ss << v::G_NEXT_LINE;
        ss << v::G_SPACE_04;
        ss << map.at(k::G_LT);
        ss << map.at(k::G_SLASH);
        ss << map.at(k::G_XML_RECORD);
        ss << map.at(k::G_GT);
        return ss.str();
    }

} // namespace ruac::rstd::logsystem
