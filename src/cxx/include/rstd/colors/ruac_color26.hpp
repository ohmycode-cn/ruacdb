/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/colors/ruac_color26.hpp
 * src/rstd/colors/ruac_color26.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_COLOR26_HPP
#define RUAC_COLOR26_HPP

#include <string>

namespace ruac::rstd::colors {

    enum class Color26List {
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

    class Color26 {
      private:
        const char *const M_ANSI_SEQS[9]{"0m", "30m", "31m", "32m", "33m", "34m", "35m",
                                         "36m", "37m"};
        const char *const M_FONT_NORMAL{"[0;"};
        const char *const M_FONT_BOLD{"[1;"};
        const char *const M_ANSI_OLD{"\033"};
        const char *const M_ANSI_NEW{"\x1b"};
        bool m_enable_ht{false};

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
        void init(const bool enable_ce_, const bool enable_ht_, const bool enable_bf_);
        auto wrap(const std::string &color_, const std::string &message_, const bool enable_ht_) -> std::string;

      public:
        Color26(const bool enable_ce_ = true, const bool enable_ht_ = false, const bool enable_bf_ = false);
        ~Color26() = default;

      public:
        auto d(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto r(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto g(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto y(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto b(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto m(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto c(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto w(const std::string &message_, const bool enable_ht_ = true) -> std::string;
        auto get_var(Color26List color_) -> std::string;
    };

} // namespace ruac::rstd::colors

#endif // RUAC_COLOR26_HPP
