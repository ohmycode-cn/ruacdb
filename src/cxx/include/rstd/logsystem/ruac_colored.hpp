/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_colored.hpp
 * src/rstd/logsystem/ruac_colored.cpp
 *
 * @brief Defines ANSI color utilities for colorizing terminal log output with configurable escape sequences and font weight.
 *
 */

#pragma once
#ifndef RUAC_COLORED_HPP
#define RUAC_COLORED_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Enumeration of supported ANSI color names for log colorization
     */
    enum class ColoredName {
        RESET = 0,
        DARK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    /**
     * @brief Utility for applying ANSI color codes to log messages.
     *
     * Provides shorthand methods (d, r, g, y, b, m, c, w) to wrap text
     * in the corresponding ANSI terminal color sequences.
     * Supports configurable escape prefix and font weight.
     */
    class Colored {
      private:
        const char *const M_ANSI_SEQS[9]{"0m", "30m", "31m", "32m", "33m", "34m", "35m",
                                         "36m", "37m"};
        const char *const M_FONT_NORMAL{"[0;"};
        const char *const M_FONT_BOLD{"[1;"};
        const char *const M_ANSI_OLD{"\033"};
        const char *const M_ANSI_NEW{"\x1b"};

      private:
        logtype::string m_reset;
        logtype::string m_dark;
        logtype::string m_red;
        logtype::string m_green;
        logtype::string m_yellow;
        logtype::string m_blue;
        logtype::string m_magenta;
        logtype::string m_cyan;
        logtype::string m_white;

      private:
        void init(const bool enable_ce_, const bool enable_ht_, const bool enable_bf_);
        auto wrap(const logtype::string &color_, const logtype::string &message_) -> logtype::string;

      public:
        Colored(const bool enable_ce_ = true, const bool enable_ht_ = false, const bool enable_bf_ = false);
        ~Colored() = default;

      public:
        auto d(const logtype::string &message_) -> logtype::string;
        auto r(const logtype::string &message_) -> logtype::string;
        auto g(const logtype::string &message_) -> logtype::string;
        auto y(const logtype::string &message_) -> logtype::string;
        auto b(const logtype::string &message_) -> logtype::string;
        auto m(const logtype::string &message_) -> logtype::string;
        auto c(const logtype::string &message_) -> logtype::string;
        auto w(const logtype::string &message_) -> logtype::string;
        auto get_var(ColoredName color_) -> logtype::string;
    };
} // namespace ruac::rstd::logsystem

#endif // RUAC_COLORED_HPP
