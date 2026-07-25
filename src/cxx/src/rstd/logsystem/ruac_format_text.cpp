/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_text.hpp
 * src/rstd/logsystem/ruac_format_text.cpp
 */

#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {
        namespace k = logkeys::token_k;
        namespace v = logkeys::token_v;
    } // namespace

    /**
     * @brief Formats a single log entry as a plain-text line pair.
     *
     * @param strmap_    Key-value map containing formatting token (colons, braces, etc.).
     * @param time_    Timestamp string for the log entry header.
     * @param level_   Log level string (e.g. "INFO", "ERROR", ....).
     * @param sequence_  Monotonically increasing sequence number for the log entry.
     * @param message_ The log message content.
     * @param file_    Source file name where the log was emitted.
     * @param line_    Source line number where the log was emitted.
     *
     * @return A formatted plain-text log segment as a string.
     *
     * @details e.g.
     * time level sequence line:file<next_line>
     * <space:8>{MESSAGE}:<space:1>message
     */
    auto FormatText::format(const logtype::strmap &strmap_,
                            const logtype::string &time_,
                            const logtype::string &level_,
                            const logtype::seqnum &sequence_,
                            const logtype::string &message_,
                            const logtype::string &file_,
                            const logtype::sd_int line_) -> logtype::string {
        std::stringstream ss;
        logtype::strmap map{strmap_};

        ss << time_;
        ss << v::G_SPACE_01;
        ss << level_;
        ss << v::G_SPACE_01;
        ss << sequence_;
        ss << v::G_SPACE_01;
        ss << line_;
        ss << map.at(k::G_COLON);
        ss << file_;
        ss << v::G_NEXT_LINE;
        ss << v::G_SPACE_08;
        ss << map.at(k::G_LEFT_BRACE);
        ss << map.at(k::G_MESSAGE);
        ss << map.at(k::G_RIGHT_BRACE);
        ss << map.at(k::G_COLON);
        ss << v::G_SPACE_01;
        ss << message_;
        return ss.str();
    }

} // namespace ruac::rstd::logsystem
