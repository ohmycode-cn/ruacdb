/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_confmap.hpp
 * src/rstd/logsystem/ruac_confmap.cpp
 */

#include "rstd/logsystem/ruac_confmap.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_logpath.hpp"

namespace ruac::rstd::logsystem {

    namespace confmap {

        namespace {

            namespace w = logkeys::kword;
            namespace p = logpath;

        } // namespace

        /**
         * @brief Get the default log configuration map
         *
         * @return logtype::strmap - A string map containing default log
         *         configuration key-value pairs
         *
         * @details Constructs and returns a map with default configuration values
         *          for the logging system. Includes settings for terminal output
         *          modes (compatible, highlight, bold), log format styles (text),
         *          output modes (console), log file path and name, file size limit,
         *          and level filters for terminal, file, and mini logging.
         *
         */
        auto get_default_config_map() -> logtype::strmap {

            logtype::strmap map{
                {w::G_LOG_TERM_OUTPUT_MODE, w::G_CONSOLE},
                {w::G_LOG_FILE_OUTPUT_MODE, w::G_CONSOLE},
                {w::G_LOG_TERM_FORMAT_STYLE, w::G_TEXT},
                {w::G_LOG_FILE_FORMAT_STYLE, w::G_TEXT},
                {w::G_LOG_TERM_LEVEL_FILTER, w::G_DEBUG},
                {w::G_LOG_FILE_LEVEL_FILTER, w::G_DEBUG},
                {w::G_LOG_MINI_LEVEL_FILTER, w::G_DEBUG},
                {w::G_ENABLE_TERM_COMPATIBLE_MODE, w::G_TRUE},
                {w::G_ENABLE_TERM_HIGHLIGHT_MODE, w::G_FALSE},
                {w::G_ENABLE_TERM_BOLD_FONT_MODE, w::G_FALSE},
                {w::G_LOG_WRITE_FILE_PATH, p::G_LOG_WRITE_FILE_PATH},
                {w::G_LOG_WRITE_FILE_NAME, p::G_LOG_WRITE_FILE_NAME},
                {w::G_LOG_FILE_SIZE_LIMIT, w::G_LOG_FILE_SIZE_LIMIT_VALUE}};
            return map;
        }

    } // namespace confmap

} // namespace ruac::rstd::logsystem
