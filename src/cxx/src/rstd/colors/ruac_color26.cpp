/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/colors/ruac_color26.hpp
 * src/rstd/colors/ruac_color26.cpp
 */

#include "rstd/colors/ruac_color26.hpp"

namespace ruac::rstd::colors {

    /**
     * @brief Construct a Color26 instance with color configuration
     *
     * @param enable_ce_ - Use classic ESC escape sequence (\033) instead of \x1b
     * @param enable_ht_ - Enable ANSI color output; false disables all colors
     * @param enable_bf_ - Enable bold font weight instead of normal
     *
     * @details Delegates initialization to init() method to set up color sequences
     *          based on the provided configuration flags.
     *
     */
    Color26::Color26(const bool enable_ce_, const bool enable_ht_, const bool enable_bf_) {
        init(enable_ce_, enable_ht_, enable_bf_);
    }

    /**
     * @brief Initialize color sequences based on configuration flags
     *
     * @param enable_ce_ - Use classic ESC escape sequence (\033) instead of \x1b
     * @param enable_ht_ - Enable ANSI color output; false disables all colors
     * @param enable_bf_ - Enable bold font weight instead of normal
     *
     * @details Sets m_enable_ht flag, constructs font and ANSI prefix strings,
     *          then builds color sequence members (m_reset, m_dark, m_red, etc.)
     *          by combining ANSI prefix, font style, and color sequence. Returns
     *          early without setting color sequences if enable_ht_ is false.
     *
     */
    void Color26::init(const bool enable_ce_, const bool enable_ht_, const bool enable_bf_) {
        m_enable_ht = enable_ht_;
        std::string font = (enable_bf_) ? M_FONT_BOLD : M_FONT_NORMAL;
        std::string ansi = (enable_ce_) ? M_ANSI_OLD : M_ANSI_NEW;
        if (!enable_ht_) {
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
     * @brief Wrap a message with color escape sequences
     *
     * @param color_ - ANSI color escape sequence to apply
     * @param message_ - Text message to wrap with color
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with color sequences, or plain message
     *
     * @details Dual-gate color wrapping: returns plain message if either instance-
     *          level m_enable_ht or per-call enable_ht_ is false. Otherwise returns
     *          color_ + message_ + m_reset to apply color and reset formatting.
     *
     */
    auto Color26::wrap(const std::string &color_, const std::string &message_,
                       const bool enable_ht_) -> std::string {
        if (!m_enable_ht || !enable_ht_) {
            return message_;
        }
        return color_ + message_ + m_reset;
    }

    /**
     * @brief Get the ANSI color sequence for a Color26List enum value
     *
     * @param color_ - Color26List enum value specifying the color
     *
     * @return std::string - ANSI color sequence string, or empty string if disabled
     *
     * @details Returns empty string if m_enable_ht is false. Otherwise uses a
     *          switch statement to return the corresponding color member variable
     *          (m_reset, m_dark, m_red, etc.) based on the Color26List enum value.
     *          Falls back to m_reset for unknown enum values.
     *
     */
    auto Color26::get_var(Color26List color_) -> std::string {
        if (!m_enable_ht) {
            return "";
        }
        switch (color_) {
        case Color26List::RESET:
            return m_reset;
        case Color26List::DARK:
            return m_dark;
        case Color26List::RED:
            return m_red;
        case Color26List::GREEN:
            return m_green;
        case Color26List::YELLOW:
            return m_yellow;
        case Color26List::BLUE:
            return m_blue;
        case Color26List::MAGENTA:
            return m_magenta;
        case Color26List::CYAN:
            return m_cyan;
        case Color26List::WHITE:
            return m_white;
        }
        return m_reset;
    }

    /**
     * @brief Wrap message with dark/black color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with dark color sequences
     *
     * @details Delegates to wrap() with the dark color member variable.
     *
     */
    auto Color26::d(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_dark, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with red color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with red color sequences
     *
     * @details Delegates to wrap() with the red color member variable.
     *
     */
    auto Color26::r(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_red, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with green color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with green color sequences
     *
     * @details Delegates to wrap() with the green color member variable.
     *
     */
    auto Color26::g(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_green, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with yellow color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with yellow color sequences
     *
     * @details Delegates to wrap() with the yellow color member variable.
     *
     */
    auto Color26::y(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_yellow, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with blue color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with blue color sequences
     *
     * @details Delegates to wrap() with the blue color member variable.
     *
     */
    auto Color26::b(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_blue, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with magenta color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with magenta color sequences
     *
     * @details Delegates to wrap() with the magenta color member variable.
     *
     */
    auto Color26::m(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_magenta, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with cyan color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with cyan color sequences
     *
     * @details Delegates to wrap() with the cyan color member variable.
     *
     */
    auto Color26::c(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_cyan, message_, enable_ht_);
    }

    /**
     * @brief Wrap message with white color
     *
     * @param message_ - Text message to colorize
     * @param enable_ht_ - Per-call flag to enable/disable color output
     *
     * @return std::string - Message wrapped with white color sequences
     *
     * @details Delegates to wrap() with the white color member variable.
     *
     */
    auto Color26::w(const std::string &message_, const bool enable_ht_) -> std::string {
        return wrap(m_white, message_, enable_ht_);
    }

} // namespace ruac::rstd::colors
