/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/colors/ruac_background.hpp
 * src/rstd/colors/ruac_background.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_BACKGROUND_HPP
#define RUAC_BACKGROUND_HPP

#include <string>

namespace ruac::rstd::colors {

    enum class BackgroundColorList {
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

    class Background {
      private:
        const char *const M_ANSI_DARK_SEQS[9]{"0m", "40m", "41m", "42m", "43m", "44m", "45m",
                                              "46m", "47m"};
        const char *const M_ANSI_BRIGHT_SEQS[9]{"0m", "100m", "101m", "102m", "103m", "104m",
                                                "105m", "106m", "107m"};
        const char *const M_FONT_NORMAL{"[0;"};
        const char *const M_ANSI_OLD{"\033"};
        const char *const M_ANSI_NEW{"\x1b"};
        bool m_enable_ht{false};
        bool m_enable_dp{false};

      private:
        std::string m_reset{""};
        std::string m_dark{""};
        std::string m_red{""};
        std::string m_green{""};
        std::string m_yellow{""};
        std::string m_blue{""};
        std::string m_magenta{""};
        std::string m_cyan{""};
        std::string m_white{""};

      private:
        void init(const bool enable_ce_, const bool enable_ht_, const bool enable_dp_);
        auto wrap(const std::string &color_, const std::string &message_, const bool enable_ht_) -> std::string;

      public:
        Background(const bool enable_ce_ = true, const bool enable_ht_ = false, const bool enable_dp_ = true);
        ~Background() = default;

      public:
        auto d(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto r(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto g(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto y(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto b(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto m(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto c(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto w(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto get_var(BackgroundColorList color_) -> std::string;
    };

} // namespace ruac::rstd::colors

#endif // RUAC_BACKGROUND_HPP
