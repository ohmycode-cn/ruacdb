/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_colored.hpp
 * src/rstd/logsystem/ruac_colored.cpp
 */

#include "rstd/logsystem/ruac_colored.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Construct a Colored formatter and initialize color sequences.
     *
     * @param enable_ce_  Use classic ESC escape sequence (\\033) instead of \\x1b.
     * @param enable_ht_  Enable ANSI color output; false disables all colors.
     * @param enable_bf_  Enable bold font weight instead of normal.
     */
    Colored::Colored(const logtype::Bool enable_ce_, const logtype::Bool enable_ht_, const logtype::Bool enable_bf_) {
        init(enable_ce_, enable_ht_, enable_bf_);
    }

    /**
     * @brief Initialize ANSI color sequences based on configuration.
     *
     * @param enable_ce_  Use classic ESC escape sequence (\\033) instead of \\x1b.
     * @param enable_ht_  Enable ANSI color output; false sets all colors to empty.
     * @param enable_bf_  Enable bold font weight instead of normal.
     */
    void Colored::init(const logtype::Bool enable_ce_, const logtype::Bool enable_ht_, const logtype::Bool enable_bf_) {

        logtype::String font = (enable_bf_) ? M_FONT_BOLD : M_FONT_NORMAL;
        logtype::String ansi = (enable_ce_) ? M_ANSI_OLD : M_ANSI_NEW;
        if (!enable_ht_) {
            m_reset = "";
            m_dark = "";
            m_red = "";
            m_green = "";
            m_yellow = "";
            m_blue = "";
            m_magenta = "";
            m_cyan = "";
            m_white = "";
            return;
        }
        m_reset = ansi + font + M_ANSI_SEQS[0];
        m_dark = ansi + font + M_ANSI_SEQS[1];
        m_red = ansi + font + M_ANSI_SEQS[2];
        m_green = ansi + font + M_ANSI_SEQS[3];
        m_yellow = ansi + font + M_ANSI_SEQS[4];
        m_blue = ansi + font + M_ANSI_SEQS[5];
        m_magenta = ansi + font + M_ANSI_SEQS[6];
        m_cyan = ansi + font + M_ANSI_SEQS[7];
        m_white = ansi + font + M_ANSI_SEQS[8];
    }

    /**
     * @brief Wrap a message with an ANSI color prefix and reset suffix.
     *
     * @param color_    The ANSI color sequence to prepend.
     * @param message_  The message text to colorize.
     * @return The colorized string with reset appended.
     */
    auto Colored::wrap(const logtype::String &color_, const logtype::String &message_) -> logtype::String {
        return color_ + message_ + m_reset;
    }

    auto Colored::get_var(ColoredName color_) -> logtype::String {
        switch (color_) {
        case ColoredName::RESET:
            return m_reset;
        case ColoredName::DARK:
            return m_dark;
        case ColoredName::RED:
            return m_red;
        case ColoredName::GREEN:
            return m_green;
        case ColoredName::YELLOW:
            return m_yellow;
        case ColoredName::BLUE:
            return m_blue;
        case ColoredName::MAGENTA:
            return m_magenta;
        case ColoredName::CYAN:
            return m_cyan;
        case ColoredName::WHITE:
            break;
        }
        return m_reset;
    }

    /**
     * @brief Apply dark (black) color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::d(const logtype::String &message_) -> logtype::String {
        return wrap(m_dark, message_);
    }

    /**
     * @brief Apply red color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::r(const logtype::String &message_) -> logtype::String {
        return wrap(m_red, message_);
    }

    /**
     * @brief Apply green color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::g(const logtype::String &message_) -> logtype::String {
        return wrap(m_green, message_);
    }

    /**
     * @brief Apply yellow color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::y(const logtype::String &message_) -> logtype::String {
        return wrap(m_yellow, message_);
    }

    /**
     * @brief Apply blue color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::b(const logtype::String &message_) -> logtype::String {
        return wrap(m_blue, message_);
    }

    /**
     * @brief Apply magenta color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::m(const logtype::String &message_) -> logtype::String {
        return wrap(m_magenta, message_);
    }

    /**
     * @brief Apply cyan color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::c(const logtype::String &message_) -> logtype::String {
        return wrap(m_cyan, message_);
    }

    /**
     * @brief Apply white color to the message.
     *
     * @param message_  The message text to colorize.
     * @return The colorized string.
     */
    auto Colored::w(const logtype::String &message_) -> logtype::String {
        return wrap(m_white, message_);
    }

} // namespace ruac::rstd::logsystem
