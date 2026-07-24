/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_colored.hpp
 * src/rstd/logsystem/ruac_colored.cpp
 * Description of header file function declaration
 * Utility for applying ANSI color codes to log messages.
 *
 */

#pragma once
#ifndef RUAC_COLORED_HPP
#define RUAC_COLORED_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Enumeration of supported ANSI color names for log colorization
     *
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
        const char *const M_ANSI_OLD{"\033"};
        const char *const M_ANSI_NEW{"\x1b"};
        const char *const M_FONT_NORMAL{"[0;"};
        const char *const M_FONT_BOLD{"[1;"};
        const char *const M_ANSI_SEQS[9]{"0m", "30m", "31m", "32m", "33m",
                                         "34m", "35m", "36m", "37m"};

      private:
        logtype::String m_reset;
        logtype::String m_dark;
        logtype::String m_red;
        logtype::String m_green;
        logtype::String m_yellow;
        logtype::String m_blue;
        logtype::String m_magenta;
        logtype::String m_cyan;
        logtype::String m_white;

      private:
        void init(const logtype::Bool enable_ce_, const logtype::Bool enable_ht_, const logtype::Bool enable_bf_);
        auto wrap(const logtype::String &color_, const logtype::String &message_) -> logtype::String;

      public:
        Colored(const logtype::Bool enable_ce_ = true, const logtype::Bool enable_ht_ = false,
                const logtype::Bool enable_bf_ = false);
        ~Colored() = default;

      public:
        auto get_var(ColoredName color_) -> logtype::String;
        auto d(const logtype::String &message_) -> logtype::String;
        auto r(const logtype::String &message_) -> logtype::String;
        auto g(const logtype::String &message_) -> logtype::String;
        auto y(const logtype::String &message_) -> logtype::String;
        auto b(const logtype::String &message_) -> logtype::String;
        auto m(const logtype::String &message_) -> logtype::String;
        auto c(const logtype::String &message_) -> logtype::String;
        auto w(const logtype::String &message_) -> logtype::String;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_COLORED_HPP
