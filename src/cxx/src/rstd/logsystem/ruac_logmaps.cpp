/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logmaps.hpp
 * src/rstd/logsystem/ruac_logmaps.cpp
 */

#include "rstd/logsystem/ruac_logmaps.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_colored.hpp"

namespace ruac::rstd::logsystem {

    namespace logmaps {

        namespace {

            namespace k = logkeys::token_k;
            namespace v = logkeys::token_v;

        } // namespace

        /**
         * @brief Get a plain-text token map for log formatting
         *
         * @return logtype::strmap - A string map containing token keys and their
         *         corresponding plain-text values
         *
         * @details Constructs and returns a map where each log token key
         *          (e.g., G_LEFT_BRACE, G_TIME, G_LEVEL) is mapped to its plain-
         *          text representation without any color formatting. This map is
         *          used for basic log output without ANSI color codes.
         *
         */
        auto get_text_map() -> logtype::strmap {
            logtype::strmap map{
                {k::G_LEFT_BRACE, v::G_LEFT_BRACE},
                {k::G_RIGHT_BRACE, v::G_RIGHT_BRACE},
                {k::G_LEFT_SQUARE_BRACKET, v::G_LEFT_SQUARE_BRACKET},
                {k::G_RIGHT_SQUARE_BRACKET, v::G_RIGHT_SQUARE_BRACKET},
                {k::G_LEFT_PARENTHESIS, v::G_LEFT_PARENTHESIS},
                {k::G_RIGHT_PARENTHESIS, v::G_RIGHT_PARENTHESIS},
                {k::G_SEQUENCE, v::G_SEQUENCE},
                {k::G_TIME, v::G_TIME},
                {k::G_LEVEL, v::G_LEVEL},
                {k::G_MESSAGE, v::G_MESSAGE},
                {k::G_FILE, v::G_FILE},
                {k::G_LINE, v::G_LINE},
                {k::G_COLON, v::G_COLON},
                {k::G_COMMA, v::G_COMMA},
                {k::G_EQUAL, v::G_EQUAL},
                {k::G_QUOTE, v::G_QUOTE},
                {k::G_GT, v::G_GT},
                {k::G_LT, v::G_LT},
                {k::G_SLASH, v::G_SLASH},
                {k::G_QUESTION, v::G_QUESTION},
                {k::G_DEBUG, v::G_DEBUG},
                {k::G_INFO, v::G_INFO},
                {k::G_WARNING, v::G_WARNING},
                {k::G_ERROR, v::G_ERROR},
                {k::G_FATAL, v::G_FATAL},
                {k::G_XML_RECORD, v::G_XML_RECORD},
                {k::G_XML_TIME, v::G_XML_TIME},
                {k::G_XML_LEVEL, v::G_XML_LEVEL},
                {k::G_XML_MESSAGE, v::G_XML_MESSAGE},
                {k::G_XML_SEQUENCE, v::G_XML_SEQUENCE},
                {k::G_XML_FILE, v::G_XML_FILE},
                {k::G_XML_LINE, v::G_XML_LINE}};
            return map;
        }

        /**
         * @brief Get an ANSI-colored token map for log formatting
         *
         * @param enable_ce_ - Use classic ESC escape sequence (\033) instead of \x1b
         * @param enable_ht_ - Enable ANSI color output; false disables all colors
         * @param enable_bf_ - Enable bold font weight instead of normal
         *
         * @return logtype::strmap - A string map containing token keys and their
         *         corresponding ANSI-colored values
         *
         * @details Constructs and returns a map where each log token key is
         *          mapped to its colored ANSI representation. Uses the Colored
         *          helper class to apply different colors and formatting styles
         *          to different token types (e.g., debug in green, error in red,
         *          time/level in yellow). The color application is controlled
         *          by the boolean parameters for enabling colored output, high
         *          intensity, and bold formatting.
         *
         */
        auto get_ansi_map(const bool enable_ce_, const bool enable_ht_, const bool enable_bf_) -> logtype::strmap {
            Colored t(enable_ce_, enable_ht_, enable_bf_);
            logtype::strmap map{
                {k::G_LEFT_BRACE, t.c(v::G_LEFT_BRACE)},
                {k::G_RIGHT_BRACE, t.c(v::G_RIGHT_BRACE)},
                {k::G_LEFT_SQUARE_BRACKET, t.b(v::G_LEFT_SQUARE_BRACKET)},
                {k::G_RIGHT_SQUARE_BRACKET, t.b(v::G_RIGHT_SQUARE_BRACKET)},
                {k::G_LEFT_PARENTHESIS, t.m(v::G_LEFT_PARENTHESIS)},
                {k::G_RIGHT_PARENTHESIS, t.m(v::G_RIGHT_PARENTHESIS)},
                {k::G_SEQUENCE, t.y(v::G_SEQUENCE)},
                {k::G_TIME, t.y(v::G_TIME)},
                {k::G_LEVEL, t.y(v::G_LEVEL)},
                {k::G_MESSAGE, t.y(v::G_MESSAGE)},
                {k::G_FILE, t.y(v::G_FILE)},
                {k::G_LINE, t.y(v::G_LINE)},
                {k::G_COLON, t.c(v::G_COLON)},
                {k::G_COMMA, t.w(v::G_COMMA)},
                {k::G_EQUAL, t.w(v::G_EQUAL)},
                {k::G_QUOTE, t.r(v::G_QUOTE)},
                {k::G_GT, t.w(v::G_GT)},
                {k::G_LT, t.w(v::G_LT)},
                {k::G_SLASH, t.w(v::G_SLASH)},
                {k::G_QUESTION, t.w(v::G_QUESTION)},
                {k::G_DEBUG, t.g(v::G_DEBUG)},
                {k::G_INFO, t.b(v::G_INFO)},
                {k::G_WARNING, t.y(v::G_WARNING)},
                {k::G_ERROR, t.r(v::G_ERROR)},
                {k::G_FATAL, t.m(v::G_FATAL)},
                {k::G_XML_RECORD, t.g(v::G_XML_RECORD)},
                {k::G_XML_TIME, t.g(v::G_XML_TIME)},
                {k::G_XML_LEVEL, t.g(v::G_XML_LEVEL)},
                {k::G_XML_MESSAGE, t.g(v::G_XML_MESSAGE)},
                {k::G_XML_SEQUENCE, t.g(v::G_XML_SEQUENCE)},
                {k::G_XML_FILE, t.g(v::G_XML_FILE)},
                {k::G_XML_LINE, t.g(v::G_XML_LINE)}};
            return map;
        }

        /**
         * @brief Get a plain-text log level map
         *
         * @return logtype::strmap - A string map of the five log level
         *         keys (DEBUG, INFO, WARNING, ERROR, FATAL) to their
         *         plain-text values
         *
         * @details Builds and returns a strmap mapping each log level token
         *          key to its uncoloured plain-text representation. Used for
         *          log output that does not require ANSI colour codes.
         *
         */
        auto get_text_level_map() -> logtype::strmap {
            logtype::strmap map{
                {k::G_DEBUG, v::G_DEBUG},
                {k::G_INFO, v::G_INFO},
                {k::G_WARNING, v::G_WARNING},
                {k::G_ERROR, v::G_ERROR},
                {k::G_FATAL, v::G_FATAL}};
            return map;
        }

        /**
         * @brief Get an ANSI-colored log level map
         *
         * @return logtype::strmap - A string map of the five log level
         *         keys (DEBUG, INFO, WARNING, ERROR, FATAL) to their
         *         ANSI-colored values
         *
         * @details Constructs a Colored helper with classic ESC, high
         *          intensity and bold enabled, then maps each log level
         *          token key to its colourised value: DEBUG in green, INFO
         *          in cyan, WARNING in yellow, ERROR in red and FATAL in
         *          magenta.
         *
         */
        auto get_ansi_level_map() -> logtype::strmap {
            Colored t(true, true, true);
            logtype::strmap map{
                {k::G_DEBUG, t.g(v::G_DEBUG)},
                {k::G_INFO, t.c(v::G_INFO)},
                {k::G_WARNING, t.y(v::G_WARNING)},
                {k::G_ERROR, t.r(v::G_ERROR)},
                {k::G_FATAL, t.m(v::G_FATAL)}};
            return map;
        }

    } // namespace logmaps

} // namespace ruac::rstd::logsystem
