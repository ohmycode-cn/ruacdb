/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_json.hpp
 * src/rstd/logsystem/ruac_format_json.cpp
 */

#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {
        namespace k = logkeys::token_k;
        namespace v = logkeys::token_v;
    } // namespace

    /**
     * @brief Formats a single JSON key-value pair line with indentation.
     *
     * @tparam V       Type of the value to format (e.g. String, udll, sdit).
     * @param strmap_  Key-value map containing formatting token (quotes, colons, etc.).
     * @param key_     The JSON property name token (e.g. logkeys::token::G_TIME).
     * @param val_     The value to be serialized into the JSON property.
     *
     * @return A formatted JSON property line as a string.
     *
     * @details e.g.
     * <space:8>"key":<space:1>"value",<next_line>
     */
    template <typename V>
    auto FormatJson::fmt(const logtype::strmap &strmap_,
                         const logtype::string &key_, const V &val_) -> logtype::string {
        std::stringstream ss;
        logtype::strmap map{strmap_};
        ss << v::G_SPACE_08;
        ss << map.at(k::G_QUOTE);
        ss << map.at(key_);
        ss << map.at(k::G_QUOTE);
        ss << map.at(k::G_COLON);
        ss << v::G_SPACE_01;
        ss << map.at(k::G_QUOTE);
        ss << val_;
        ss << map.at(k::G_QUOTE);
        ss << map.at(k::G_COMMA);
        ss << v::G_NEXT_LINE;
        return ss.str();
    }

    /**
     * @brief Formats a single log entry as a JSON object string.
     *
     * @param strmap_    Key-value map containing formatting token (quotes, colons, braces, etc.).
     * @param time_      Timestamp string used as the JSON object key and the TIME field value.
     * @param level_     Log level string (e.g. "INFO", "ERROR", ...).
     * @param sequence_  Monotonically increasing sequence number for the log entry.
     * @param message_   The log message content.
     * @param file_      Source file name where the log was emitted.
     * @param line_      Source line number where the log was emitted.
     *
     * @return A formatted JSON object segment as a string, ready to be embedded
     *         in the parent log structure.
     *
     * @details e.g.
     * <space:4>"time":<space:1>{<next_line>
     * <space:4><space:4>"TIME":<space:1>"time_",<next_line>
     * <space:4><space:4>"LEVEL":<space:1>"level_",<next_line>
     * <space:4><space:4>"SEQUENCE":<space:1>sequence_,<next_line>
     * <space:4><space:4>"MESSAGE":<space:1>"message_",<next_line>
     * <space:4><space:4>"FILE":<space:1>"file_",<next_line>
     * <space:4><space:4>"LINE":<space:1>line_,<next_line>
     * <space:4>},
     */
    auto FormatJson::format(const logtype::strmap &strmap_,
                            const logtype::string &time_,
                            const logtype::string &level_,
                            const logtype::seqnum &sequence_,
                            const logtype::string &message_,
                            const logtype::string &file_,
                            const logtype::sd_int line_) -> logtype::string {
        std::stringstream ss;
        logtype::strmap map{strmap_};

        // start.
        ss << v::G_SPACE_04;
        ss << map.at(k::G_QUOTE);
        ss << time_;
        ss << map.at(k::G_QUOTE);
        ss << map.at(k::G_COLON);
        ss << v::G_SPACE_01;
        ss << map.at(k::G_LEFT_BRACE);
        ss << v::G_NEXT_LINE;

        // time.
        ss << fmt(map, k::G_TIME, time_);
        // levels.
        ss << fmt(map, k::G_LEVEL, level_);
        // sequence.
        ss << fmt(map, k::G_SEQUENCE, sequence_);
        // message.
        ss << fmt(map, k::G_MESSAGE, message_);
        // file.
        ss << fmt(map, k::G_FILE, file_);
        // line.
        ss << fmt(map, k::G_LINE, line_);

        // endof.
        ss << v::G_SPACE_04;
        ss << map.at(k::G_RIGHT_BRACE);
        ss << map.at(k::G_COMMA);
        return ss.str();
    }

} // namespace ruac::rstd::logsystem
