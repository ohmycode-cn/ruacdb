/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_format_text.hpp
 * src/rstd/logsystem/ruac_format_text.cpp
 */

#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

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
    auto FormatText::format(const logtype::StringMap &strmap_,
                            const logtype::String &time_,
                            const logtype::String &level_,
                            const logtype::Seqnum &sequence_,
                            const logtype::String &message_,
                            const logtype::String &file_,
                            const logtype::Int line_) -> logtype::String {
        std::stringstream ss;
        logtype::StringMap map{strmap_};

        ss << time_;
        ss << logkeys::token::G_SPACE_01;
        ss << level_;
        ss << logkeys::token::G_SPACE_01;
        ss << sequence_;
        ss << logkeys::token::G_SPACE_01;
        ss << line_;
        ss << map.at(logkeys::token::G_COLON);
        ss << file_;
        ss << logkeys::token::G_NEXT_LINE;
        ss << logkeys::token::G_SPACE_08;
        ss << map.at(logkeys::token::G_LEFT_BRACE);
        ss << map.at(logkeys::token::G_MESSAGE);
        ss << map.at(logkeys::token::G_RIGHT_BRACE);
        ss << map.at(logkeys::token::G_COLON);
        ss << logkeys::token::G_SPACE_01;
        ss << message_;
        return ss.str();
    }

} // namespace ruac::rstd::logsystem
