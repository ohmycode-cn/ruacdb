/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logkeys.hpp
 * src/rstd/logsystem/ruac_logkeys.cpp
 * Constant key definitions for log system configuration and formatting tokens.
 *
 */

#pragma once
#ifndef RUAC_LOGKEYS_HPP
#define RUAC_LOGKEYS_HPP

namespace ruac::rstd::logsystem {

    namespace logkeys {

        namespace word {

            constexpr const char *const G_ENABLE_TERM_COMPATIBLE_MODE{"ENABLE_TERM_COMPATIBLE_MODE"};
            constexpr const char *const G_ENABLE_TERM_HIGHLIGHT_MODE{"ENABLE_TERM_HIGHLIGHT_MODE"};
            constexpr const char *const G_ENABLE_TERM_BOLD_FONT_MODE{"ENABLE_TERM_BOLD_FONT_MODE"};
            constexpr const char *const G_ENABLE_TERM_LOG_PRINT_MODE{"ENABLE_TERM_LOG_PRINT_MODE"};
            constexpr const char *const G_LOG_TERM_FORMAT_STYLE{"LOG_TERM_FORMAT_STYLE"};
            constexpr const char *const G_LOG_FILE_FORMAT_STYLE{"LOG_FILE_FORMAT_STYLE"};
            constexpr const char *const G_LOG_OUTPUT_MODE{"LOG_OUTPUT_MODE"};
            constexpr const char *const G_LOG_WRITE_PATH{"LOG_WRITE_PATH"};
            constexpr const char *const G_LOG_WRITE_FILE{"LOG_WRITE_FILE"};
            constexpr const char *const G_LOG_FILE_SIZE_LIMIT{"LOG_FILE_SIZE_LIMIT"};
            constexpr const char *const G_TERM_LOG_LEVEL_FILTER{"TERM_LOG_LEVEL_FILTER"};
            constexpr const char *const G_FILE_LOG_LEVEL_FILTER{"FILE_LOG_LEVEL_FILTER"};
            constexpr const char *const G_MINIMUM_LOG_LEVEL{"MINIMUM_LOG_LEVEL"};
            constexpr const char *const G_LOG_LEVEL_DEBUG{"debug"};
            constexpr const char *const G_LOG_LEVEL_INFO{"info"};
            constexpr const char *const G_LOG_LEVEL_WARNING{"warning"};
            constexpr const char *const G_LOG_LEVEL_ERROR{"error"};
            constexpr const char *const G_LOG_LEVEL_FATAL{"fatal"};
            constexpr const char *const G_COMMENT{"#"};
            constexpr const char *const G_SEMICOLON{";"};
            constexpr const char *const G_EQUAL{"="};
            constexpr const char *const G_QUOTE{"\""};
            constexpr const char *const G_CONSOLE{"console"};
            constexpr const char *const G_FILE{"file"};
            constexpr const char *const G_BOTH{"both"};
            constexpr const char *const G_TEXT{"text"};
            constexpr const char *const G_JSON{"json"};
            constexpr const char *const G_XML{"xml"};
            constexpr const char *const G_FALSE{"false"};
            constexpr const char *const G_TRUE{"true"};

        } // namespace word

        namespace token {

            constexpr const char *const G_NEXT_LINE{"\n"};                              // \n
            constexpr const char *const G_SPACE_08{"        "};                         // space 8
            constexpr const char *const G_SPACE_04{"    "};                             // space 4
            constexpr const char *const G_SPACE_03{"   "};                              // space 3
            constexpr const char *const G_SPACE_02{"  "};                               // space 2
            constexpr const char *const G_SPACE_01{" "};                                // space 1
            constexpr const char *const G_LEFT_BRACE{"left_brace"};                     // {
            constexpr const char *const G_RIGHT_BRACE{"right_brace"};                   // }
            constexpr const char *const G_LEFT_SQUARE_BRACKET{"left_square_bracket"};   // [
            constexpr const char *const G_RIGHT_SQUARE_BRACKET{"right_square_bracket"}; // ]
            constexpr const char *const G_LEFT_PARENTHESIS{"left_parenthesis"};         // (
            constexpr const char *const G_RIGHT_PARENTHESIS{"right_parenthesis"};       // )
            constexpr const char *const G_SEQUENCE{"sequence"};                         // sequence
            constexpr const char *const G_TIME{"time"};                                 // time
            constexpr const char *const G_LEVEL{"level"};                               // level
            constexpr const char *const G_MESSAGE{"message"};                           // message
            constexpr const char *const G_FILE{"file"};                                 // file
            constexpr const char *const G_LINE{"line"};                                 // line
            constexpr const char *const G_XML_SEQUENCE{"xml_sequence"};                 // xml_sequence
            constexpr const char *const G_XML_TIME{"xml_time"};                         // xml_time
            constexpr const char *const G_XML_LEVEL{"xml_level"};                       // xml_level
            constexpr const char *const G_XML_MESSAGE{"xml_message"};                   // xml_message
            constexpr const char *const G_XML_FILE{"xml_file"};                         // xml_file
            constexpr const char *const G_XML_LINE{"xml_line"};                         // xml_line
            constexpr const char *const G_XML_RECORD{"xml_record"};                     // xml_record
            constexpr const char *const G_COLON{"colon"};                               // :
            constexpr const char *const G_COMMA{"comma"};                               // ,
            constexpr const char *const G_EQUAL{"equal"};                               // =
            constexpr const char *const G_QUOTE{"quote"};                               // "
            constexpr const char *const G_GT{"gt"};                                     // >
            constexpr const char *const G_LT{"lt"};                                     // <
            constexpr const char *const G_SLASH{"slash"};                               // /
            constexpr const char *const G_QUESTION{"question"};                         // ?
            constexpr const char *const G_DEBUG{"DEBUG"};                               // DEBUG
            constexpr const char *const G_INFO{"INFO"};                                 // INFO
            constexpr const char *const G_WARNING{"WARNING"};                           // WARNING
            constexpr const char *const G_ERROR{"ERROR"};                               // ERROR
            constexpr const char *const G_FATAL{"FATAL"};                               // FATAL

        } // namespace token

    } // namespace logkeys

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGKEYS_HPP
