/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/colors/ruac_background.hpp
 * src/rstd/colors/ruac_background.cpp
 */

#include "rstd/colors/ruac_background.hpp"

namespace ruac::rstd::colors {

    /**
     * @brief Construct a Background instance with background color configuration
     *
     * @param enable_ce_ - Use classic ESC escape sequence (\033) instead of \x1b
     * @param enable_ht_ - Enable ANSI color output; false disables all colors
     * @param enable_dp_ - Enable dark mode (40-47); false uses bright mode (100-107)
     *
     * @details Delegates initialization to init() method to set up background color
     *          sequences based on the provided configuration flags.
     *
     */
    Background::Background(const bool enable_ce_, const bool enable_ht_, const bool enable_dp_) {
        init(enable_ce_, enable_ht_, enable_dp_);
    }

    /**
     * @brief Initialize background color sequences based on configuration flags
     *
     * @param enable_ce_ - Use classic ESC escape sequence (\033) instead of \x1b
     * @param enable_ht_ - Enable ANSI color output; false disables all colors
     * @param enable_dp_ - Enable dark mode (40-47); false uses bright mode (100-107)
     *
     * @details Sets m_enable_ht and m_enable_dp flags, constructs font and ANSI prefix
     *          strings, then builds color sequence members (m_reset, m_dark, m_red, etc.)
     *          by combining ANSI prefix, font style, and color sequence. Returns early
     *          without setting color sequences if enable_ht_ is false.
     *
     */
    void Background::init(const bool enable_ce_, const bool enable_ht_, const bool enable_dp_) {
        m_enable_ht = enable_ht_;
        m_enable_dp = enable_dp_;
        std::string font = M_FONT_NORMAL;
        std::string ansi = (enable_ce_) ? M_ANSI_OLD : M_ANSI_NEW;
        if (!enable_ht_) {
            return;
        }
        const char *const *seqs = (enable_dp_) ? M_ANSI_DARK_SEQS : M_ANSI_BRIGHT_SEQS;
        m_reset = ansi + font + seqs[0];
        m_dark = ansi + font + seqs[1];
        m_red = ansi + font + seqs[2];
        m_green = ansi + font + seqs[3];
        m_yellow = ansi + font + seqs[4];
        m_blue = ansi + font + seqs[5];
        m_magenta = ansi + font + seqs[6];
        m_cyan = ansi + font + seqs[7];
        m_white = ansi + font + seqs[8];
    }

    /**
     * @brief Wrap a message with background color escape sequences
     *
     * @param color_ - ANSI background color escape sequence to apply
     * @param message_ - Text message to wrap with background color
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with background color sequences, or plain message
     *
     * @details Dual-gate color wrapping: returns plain message if either instance-
     *          level m_enable_ht or per-call enable_ht_ is false. Otherwise returns
     *          color_ + message_ + m_reset to apply background color and reset formatting.
     *
     */
    auto Background::wrap(const std::string &color_, const std::string &message_,
                          const bool enable_ht_) -> std::string {
        if (!m_enable_ht || !enable_ht_) {
            return message_;
        }
        return color_ + message_ + m_reset;
    }

    /**
     * @brief Get the ANSI background color sequence for a BackgroundColorList enum value
     *
     * @param color_ - BackgroundColorList enum value specifying the color
     *
     * @return std::string - ANSI background color sequence string, or empty string if disabled
     *
     * @details Returns empty string if m_enable_ht is false. Otherwise uses a switch
     *          statement to return the corresponding color member variable (m_reset,
     *          m_dark, m_red, etc.) based on the BackgroundColorList enum value.
     *          Falls back to m_reset for unknown enum values.
     *
     */
    auto Background::get_var(BackgroundColorList color_) -> std::string {
        if (!m_enable_ht) {
            return "";
        }
        switch (color_) {
        case BackgroundColorList::RESET:
            return m_reset;
        case BackgroundColorList::DARK:
            return m_dark;
        case BackgroundColorList::RED:
            return m_red;
        case BackgroundColorList::GREEN:
            return m_green;
        case BackgroundColorList::YELLOW:
            return m_yellow;
        case BackgroundColorList::BLUE:
            return m_blue;
        case BackgroundColorList::MAGENTA:
            return m_magenta;
        case BackgroundColorList::CYAN:
            return m_cyan;
        case BackgroundColorList::WHITE:
            return m_white;
        }
        return m_reset;
    }

    /**
     * @brief Wrap message with dark/black background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with dark background color sequences
     *
     * @details Delegates to wrap() with the dark background color member variable.
     *
     */
    auto Background::d(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_dark, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with red background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with red background color sequences
     *
     * @details Delegates to wrap() with the red background color member variable.
     *
     */
    auto Background::r(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_red, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with green background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with green background color sequences
     *
     * @details Delegates to wrap() with the green background color member variable.
     *
     */
    auto Background::g(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_green, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with yellow background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with yellow background color sequences
     *
     * @details Delegates to wrap() with the yellow background color member variable.
     *
     */
    auto Background::y(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_yellow, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with blue background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with blue background color sequences
     *
     * @details Delegates to wrap() with the blue background color member variable.
     *
     */
    auto Background::b(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_blue, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with magenta background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with magenta background color sequences
     *
     * @details Delegates to wrap() with the magenta background color member variable.
     *
     */
    auto Background::m(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_magenta, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with cyan background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with cyan background color sequences
     *
     * @details Delegates to wrap() with the cyan background color member variable.
     *
     */
    auto Background::c(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_cyan, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with white background color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with white background color sequences
     *
     * @details Delegates to wrap() with the white background color member variable.
     *
     */
    auto Background::w(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_white, message_, enable_ht_);
    }

} // namespace ruac::rstd::colors
