/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_strmap.hpp
 * src/rstd/logsystem/ruac_strmap.cpp
 */

#include "rstd/logsystem/ruac_colored.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_strmap.hpp"

namespace {

    constexpr const char *const G_TOKEN_L_BRACE{"{"};
    constexpr const char *const G_TOKEN_R_BRACE{"}"};
    constexpr const char *const G_TOKEN_L_SQUARE_BRACKET{"["};
    constexpr const char *const G_TOKEN_R_SQUARE_BRACKET{"]"};
    constexpr const char *const G_TOKEN_L_PARENTHESIS{"("};
    constexpr const char *const G_TOKEN_R_PARENTHESIS{")"};
    constexpr const char *const G_TOKEN_SEQUENCE{"SEQUENCE"};
    constexpr const char *const G_TOKEN_TIME{"TIME"};
    constexpr const char *const G_TOKEN_LEVEL{"LEVEL"};
    constexpr const char *const G_TOKEN_MESSAGE{"MESSAGE"};
    constexpr const char *const G_TOKEN_FILE{"FILE"};
    constexpr const char *const G_TOKEN_LINE{"LINE"};
    constexpr const char *const G_TOKEN_COLON{":"};
    constexpr const char *const G_TOKEN_COMMA{","};
    constexpr const char *const G_TOKEN_EQUAL{"="};
    constexpr const char *const G_TOKEN_QUOTE{"\""};
    constexpr const char *const G_TOKEN_GT{">"};
    constexpr const char *const G_TOKEN_SLASH{"/"};
    constexpr const char *const G_TOKEN_LT{"<"};
    constexpr const char *const G_TOKEN_QUESTION{"?"};
    constexpr const char *const G_TOKEN_DEBUG{"DEBUG"};
    constexpr const char *const G_TOKEN_INFO{"INFO"};
    constexpr const char *const G_TOKEN_WARNING{"WARNING"};
    constexpr const char *const G_TOKEN_ERROR{"ERROR"};
    constexpr const char *const G_TOKEN_FATAL{"FATAL"};
    constexpr const char *const G_TOKEN_XML_RECORD{"record"};
    constexpr const char *const G_TOKEN_XML_TIME{"time"};
    constexpr const char *const G_TOKEN_XML_LEVEL{"level"};
    constexpr const char *const G_TOKEN_XML_MESSAGE{"message"};
    constexpr const char *const G_TOKEN_XML_SEQUENCE{"sequence"};
    constexpr const char *const G_TOKEN_XML_FILE{"file"};
    constexpr const char *const G_TOKEN_XML_LINE{"line"};

} // namespace

namespace ruac::rstd::logsystem {

    namespace strmap {

        /**
         * @brief Build a token-to-string map with ANSI color codes applied.
         *
         * @param enable_ce_  Use classic ESC escape sequence (\\033) instead of \\x1b.
         * @param enable_ht_  Enable ANSI color output; false disables all colors.
         * @param enable_bf_  Enable bold font weight instead of normal.
         * @return A StringMap mapping token keys to ANSI-colored string values.
         */
        auto get_ansi_map(const logtype::Bool enable_ce_, const logtype::Bool enable_ht_,
                          const logtype::Bool enable_bf_) -> logtype::StringMap {
            Colored cr(enable_ce_, enable_ht_, enable_bf_);
            logtype::StringMap map{
                {logkeys::token::G_LEFT_BRACE, cr.y(G_TOKEN_L_BRACE)},
                {logkeys::token::G_RIGHT_BRACE, cr.y(G_TOKEN_R_BRACE)},
                {logkeys::token::G_LEFT_SQUARE_BRACKET, cr.m(G_TOKEN_L_SQUARE_BRACKET)},
                {logkeys::token::G_RIGHT_SQUARE_BRACKET, cr.m(G_TOKEN_R_SQUARE_BRACKET)},
                {logkeys::token::G_LEFT_PARENTHESIS, cr.m(G_TOKEN_L_PARENTHESIS)},
                {logkeys::token::G_RIGHT_PARENTHESIS, cr.m(G_TOKEN_R_PARENTHESIS)},
                {logkeys::token::G_SEQUENCE, cr.y(G_TOKEN_SEQUENCE)},
                {logkeys::token::G_TIME, cr.r(G_TOKEN_TIME)},
                {logkeys::token::G_LEVEL, cr.m(G_TOKEN_LEVEL)},
                {logkeys::token::G_MESSAGE, cr.g(G_TOKEN_MESSAGE)},
                {logkeys::token::G_FILE, cr.b(G_TOKEN_FILE)},
                {logkeys::token::G_LINE, cr.c(G_TOKEN_LINE)},
                {logkeys::token::G_COLON, cr.w(G_TOKEN_COLON)},
                {logkeys::token::G_COMMA, cr.r(G_TOKEN_COMMA)},
                {logkeys::token::G_EQUAL, cr.w(G_TOKEN_EQUAL)},
                {logkeys::token::G_QUOTE, cr.y(G_TOKEN_QUOTE)},
                {logkeys::token::G_GT, cr.c(G_TOKEN_GT)},
                {logkeys::token::G_LT, cr.c(G_TOKEN_LT)},
                {logkeys::token::G_SLASH, cr.r(G_TOKEN_SLASH)},
                {logkeys::token::G_QUESTION, cr.d(G_TOKEN_QUESTION)},
                {logkeys::token::G_DEBUG, cr.d(G_TOKEN_DEBUG)},
                {logkeys::token::G_INFO, cr.c(G_TOKEN_INFO)},
                {logkeys::token::G_WARNING, cr.y(G_TOKEN_WARNING)},
                {logkeys::token::G_ERROR, cr.m(G_TOKEN_ERROR)},
                {logkeys::token::G_FATAL, cr.r(G_TOKEN_FATAL)},
                {logkeys::token::G_XML_RECORD, cr.b(G_TOKEN_XML_RECORD)},
                {logkeys::token::G_XML_TIME, cr.r(G_TOKEN_XML_TIME)},
                {logkeys::token::G_XML_LEVEL, cr.y(G_TOKEN_XML_LEVEL)},
                {logkeys::token::G_XML_MESSAGE, cr.g(G_TOKEN_XML_MESSAGE)},
                {logkeys::token::G_XML_SEQUENCE, cr.y(G_TOKEN_XML_SEQUENCE)},
                {logkeys::token::G_XML_FILE, cr.b(G_TOKEN_XML_FILE)},
                {logkeys::token::G_XML_LINE, cr.c(G_TOKEN_XML_LINE)}};
            return map;
        }

        /**
         * @brief Build a token-to-string map with plain (uncolored) text.
         *
         * @return A StringMap mapping token keys to plain string values.
         */
        auto get_text_map() -> logtype::StringMap {
            logtype::StringMap map{
                {logkeys::token::G_LEFT_BRACE, G_TOKEN_L_BRACE},
                {logkeys::token::G_RIGHT_BRACE, G_TOKEN_R_BRACE},
                {logkeys::token::G_LEFT_SQUARE_BRACKET, G_TOKEN_L_SQUARE_BRACKET},
                {logkeys::token::G_RIGHT_SQUARE_BRACKET, G_TOKEN_R_SQUARE_BRACKET},
                {logkeys::token::G_LEFT_PARENTHESIS, G_TOKEN_L_PARENTHESIS},
                {logkeys::token::G_RIGHT_PARENTHESIS, G_TOKEN_R_PARENTHESIS},
                {logkeys::token::G_SEQUENCE, G_TOKEN_SEQUENCE},
                {logkeys::token::G_TIME, G_TOKEN_TIME},
                {logkeys::token::G_LEVEL, G_TOKEN_LEVEL},
                {logkeys::token::G_MESSAGE, G_TOKEN_MESSAGE},
                {logkeys::token::G_FILE, G_TOKEN_FILE},
                {logkeys::token::G_LINE, G_TOKEN_LINE},
                {logkeys::token::G_COLON, G_TOKEN_COLON},
                {logkeys::token::G_COMMA, G_TOKEN_COMMA},
                {logkeys::token::G_EQUAL, G_TOKEN_EQUAL},
                {logkeys::token::G_QUOTE, G_TOKEN_QUOTE},
                {logkeys::token::G_GT, G_TOKEN_GT},
                {logkeys::token::G_LT, G_TOKEN_LT},
                {logkeys::token::G_SLASH, G_TOKEN_SLASH},
                {logkeys::token::G_QUESTION, G_TOKEN_QUESTION},
                {logkeys::token::G_DEBUG, G_TOKEN_DEBUG},
                {logkeys::token::G_INFO, G_TOKEN_INFO},
                {logkeys::token::G_WARNING, G_TOKEN_WARNING},
                {logkeys::token::G_ERROR, G_TOKEN_ERROR},
                {logkeys::token::G_FATAL, G_TOKEN_FATAL},
                {logkeys::token::G_XML_RECORD, G_TOKEN_XML_RECORD},
                {logkeys::token::G_XML_TIME, G_TOKEN_XML_TIME},
                {logkeys::token::G_XML_LEVEL, G_TOKEN_XML_LEVEL},
                {logkeys::token::G_XML_MESSAGE, G_TOKEN_XML_MESSAGE},
                {logkeys::token::G_XML_SEQUENCE, G_TOKEN_XML_SEQUENCE},
                {logkeys::token::G_XML_FILE, G_TOKEN_XML_FILE},
                {logkeys::token::G_XML_LINE, G_TOKEN_XML_LINE}};
            return map;
        }

    } // namespace strmap

} // namespace ruac::rstd::logsystem
