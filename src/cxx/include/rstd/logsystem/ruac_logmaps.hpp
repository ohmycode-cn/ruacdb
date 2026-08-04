/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logmaps.hpp
 * src/rstd/logsystem/ruac_logmaps.cpp
 * @brief Provides functions to retrieve text and ANSI color maps for log formatting.
 */

#pragma once
#ifndef RUAC_LOGMAPS_HPP
#define RUAC_LOGMAPS_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace logmaps {

        /**
         * @brief Retrieves the text format map for log token formatting.
         *
         * Returns a string map mapping token keys to their text representations.
         */
        auto get_text_map() -> logtype::strmap;

        /**
         * @brief Retrieves the ANSI color map for log token formatting.
         *
         * Returns a string map mapping token keys to ANSI color escape sequences,
         * with options to enable color, highlight, and bold font modes.
         */
        auto get_ansi_map(bool enable_ce_,  bool enable_ht_, bool enable_bf_) -> logtype::strmap;

        /**
         * @brief Retrieves the text-level map for log level formatting.
         *
         * Returns a string map mapping log level keys to their text representations.
         */
        auto get_text_level_map() -> logtype::strmap;

        /**
         * @brief Retrieves the ANSI color-level map for log level formatting.
         *
         * Returns a string map mapping log level keys to ANSI color escape sequences.
         */
        auto get_ansi_level_map() -> logtype::strmap;

    } // namespace logmaps

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGMAPS_HPP
