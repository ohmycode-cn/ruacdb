/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/gen/ruac_stddug.hpp
 * src/rstd/gen/ruac_stddug.cpp
 *
 * @brief Provides debug output utilities with configurable output behavior.
 */

#pragma once
#ifndef RUAC_STDDUG_HPP
#define RUAC_STDDUG_HPP

#include <mutex>
#include <string>
#include <string_view>

namespace ruac::rstd::gen {

    /**
     * @brief Parameter list for configuring DebugT output behavior
     *
     */
    struct StdDebugParamList {
        bool m_enable_color{false};
        bool m_output_std{true}; // true is stdout ,false: is stderr
        bool m_enable_out{true};
        bool m_enable_header{true};
        bool m_next_line{true};
    };

    class StdDug {
      private:
        const char *const M_NEXT_TABS{"\n\t\t "};
        const char *const M_NEXT_LINE{"\n"};
        std::mutex M_STDDUG_MTX;
        std::string m_header;
        StdDebugParamList m_param_mode{};

      public:
        StdDug(bool prompt_header_next_line_ = false);
        ~StdDug() = default;

      public:
        void set_param_mode(const StdDebugParamList &params_ = {});
        auto ostrs_view(std::string_view msg_, std::string_view file_, int line_) -> std::string;
        auto ostrs(const std::string &msg_, const std::string &file_, int line_) -> std::string;
        void print(const std::string &msg_, const std::string &file_, int line_);
    };

} // namespace ruac::rstd::gen

#endif // RUAC_STDDUG_HPP
