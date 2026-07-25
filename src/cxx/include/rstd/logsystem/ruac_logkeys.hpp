/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logkeys.hpp
 * src/rstd/logsystem/ruac_logkeys.cpp
 * Description of header file function declaration
 *
 * Defines constant string keys and token values for the log system configuration and formatting
 *
 */

#pragma once
#ifndef RUAC_LOGKEYS_HPP
#define RUAC_LOGKEYS_HPP

namespace ruac::rstd::logsystem {

    namespace logkeys {

        namespace kword {

            constexpr const char *const G_ENABLE_TERM_COMPATIBLE_MODE{"ENABLE_TERM_COMPATIBLE_MODE"};
            constexpr const char *const G_ENABLE_TERM_HIGHLIGHT_MODE{"ENABLE_TERM_HIGHLIGHT_MODE"};
            constexpr const char *const G_ENABLE_TERM_BOLD_FONT_MODE{"ENABLE_TERM_BOLD_FONT_MODE"};

            constexpr const char *const G_LOG_TERM_FORMAT_MODE{"LOG_TERM_FORMAT_MODE"};
            constexpr const char *const G_LOG_FILE_FORMAT_MODE{"LOG_FILE_FORMAT_MODE"};

            constexpr const char *const G_LOG_TERM_OUTPUT_MODE{"LOG_TERM_OUTPUT_MODE"};
            constexpr const char *const G_LOG_FILE_OUTPUT_MODE{"LOG_FILE_OUTPUT_MODE"};

            constexpr const char *const G_LOG_WRITE_FILE_PATH{"LOG_WRITE_FILE_PATH"};
            constexpr const char *const G_LOG_WRITE_FILE_NAME{"LOG_WRITE_FILE_NAME"};

            constexpr const char *const G_LOG_FILE_SIZE_LIMIT{"LOG_FILE_SIZE_LIMIT"};

            constexpr const char *const G_LOG_TERM_LEVEL_FILTER{"LOG_TERM_LEVEL_FILTER"};
            constexpr const char *const G_LOG_FILE_LEVEL_FILTER{"LOG_FILE_LEVEL_FILTER"};

            constexpr const char *const G_LOG_MINI_LEVEL_FILTER{"LOG_MINI_LEVEL_FILTER"};

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
            constexpr const char *const G_TEXT{"text"};
            constexpr const char *const G_JSON{"json"};
            constexpr const char *const G_XML{"xml"};
            constexpr const char *const G_FALSE{"false"};
            constexpr const char *const G_TRUE{"true"};

        }; // namespace kword

        namespace token_v {

            constexpr const char *const G_SPACE_08{"        "};      // space 8
            constexpr const char *const G_SPACE_04{"    "};          // space 4
            constexpr const char *const G_SPACE_03{"   "};           // space 3
            constexpr const char *const G_SPACE_02{"  "};            // space 2
            constexpr const char *const G_SPACE_01{" "};             // space 1
            constexpr const char *const G_NEXT_LINE{"\n"};           // \n
            constexpr const char *const G_LEFT_BRACE{"{"};           // {
            constexpr const char *const G_RIGHT_BRACE{"}"};          // }
            constexpr const char *const G_LEFT_SQUARE_BRACKET{"["};  // [
            constexpr const char *const G_RIGHT_SQUARE_BRACKET{"]"}; // ]
            constexpr const char *const G_LEFT_PARENTHESIS{"("};     // (
            constexpr const char *const G_RIGHT_PARENTHESIS{")"};    // )
            constexpr const char *const G_SEQUENCE{"SEQUENCE"};      // SEQUENCE
            constexpr const char *const G_TIME{"TIME"};              // TIME
            constexpr const char *const G_LEVEL{"LEVEL"};            // LEVEL
            constexpr const char *const G_MESSAGE{"MESSAGE"};        // MESSAGE
            constexpr const char *const G_FILE{"FILE"};              // FILE
            constexpr const char *const G_LINE{"LINE"};              // LINE
            constexpr const char *const G_COLON{":"};                // :
            constexpr const char *const G_COMMA{","};                // ,
            constexpr const char *const G_EQUAL{"="};                // =
            constexpr const char *const G_QUOTE{"\""};               // "
            constexpr const char *const G_GT{">"};                   // >
            constexpr const char *const G_LT{"<"};                   // <
            constexpr const char *const G_SLASH{"/"};                // /
            constexpr const char *const G_QUESTION{"?"};             // ?
            constexpr const char *const G_DEBUG{"DEBUG"};            // DEBUG
            constexpr const char *const G_INFO{"INFO"};              // INFO
            constexpr const char *const G_WARNING{"WARNING"};        // WARNING
            constexpr const char *const G_ERROR{"ERROR"};            // ERROR
            constexpr const char *const G_FATAL{"FATAL"};            // FATAL
            constexpr const char *const G_XML_RECORD{"record"};      // record
            constexpr const char *const G_XML_TIME{"time"};          // time
            constexpr const char *const G_XML_LEVEL{"level"};        // level
            constexpr const char *const G_XML_MESSAGE{"message"};    // message
            constexpr const char *const G_XML_SEQUENCE{"sequence"};  // sequence
            constexpr const char *const G_XML_FILE{"file"};          // file
            constexpr const char *const G_XML_LINE{"line"};          // line

        } // namespace token_v

        namespace token_k {

            constexpr const char *const G_LEFT_BRACE{"left_brace"};                     // {
            constexpr const char *const G_RIGHT_BRACE{"right_brace"};                   // }
            constexpr const char *const G_LEFT_SQUARE_BRACKET{"left_square_bracket"};   // [
            constexpr const char *const G_RIGHT_SQUARE_BRACKET{"right_square_bracket"}; // ]
            constexpr const char *const G_LEFT_PARENTHESIS{"left_parenthesis"};         // (
            constexpr const char *const G_RIGHT_PARENTHESIS{"right_parenthesis"};       // )
            constexpr const char *const G_SEQUENCE{"sequence"};                         // SEQUENCE
            constexpr const char *const G_TIME{"time"};                                 // TIME
            constexpr const char *const G_LEVEL{"level"};                               // LEVEL
            constexpr const char *const G_MESSAGE{"message"};                           // MESSAGE
            constexpr const char *const G_FILE{"file"};                                 // FILE
            constexpr const char *const G_LINE{"line"};                                 // LINE
            constexpr const char *const G_COLON{"colon"};                               // :
            constexpr const char *const G_COMMA{"comma"};                               // ,
            constexpr const char *const G_EQUAL{"equal"};                               // =
            constexpr const char *const G_QUOTE{"quote"};                               // "
            constexpr const char *const G_GT{"gt"};                                     // >
            constexpr const char *const G_LT{"lt"};                                     // <
            constexpr const char *const G_SLASH{"slash"};                               // /
            constexpr const char *const G_QUESTION{"question"};                         // ?
            constexpr const char *const G_DEBUG{"debug"};                               // DEBUG
            constexpr const char *const G_INFO{"info"};                                 // INFO
            constexpr const char *const G_WARNING{"warning"};                           // WARNING
            constexpr const char *const G_ERROR{"error"};                               // ERROR
            constexpr const char *const G_FATAL{"fatal"};                               // FATAL
            constexpr const char *const G_XML_RECORD{"xml_record"};                     // record
            constexpr const char *const G_XML_TIME{"xml_time"};                         // time
            constexpr const char *const G_XML_LEVEL{"xml_level"};                       // level
            constexpr const char *const G_XML_MESSAGE{"xml_message"};                   // message
            constexpr const char *const G_XML_SEQUENCE{"xml_sequence"};                 // sequence
            constexpr const char *const G_XML_FILE{"xml_file"};                         // file
            constexpr const char *const G_XML_LINE{"xml_line"};                         // line
        }; // namespace token_k

    } // namespace logkeys

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGKEYS_HPP
