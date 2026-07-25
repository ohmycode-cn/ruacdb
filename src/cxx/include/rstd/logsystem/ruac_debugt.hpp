/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_debugt.hpp
 * src/rstd/logsystem/ruac_debugt.cpp
 * Description of header file function declaration
 * Temporary debug logger with configurable output and source location tracking
 *
 */

#pragma once
#ifndef RUAC_DEBUGT_HPP
#define RUAC_DEBUGT_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Parameter list for configuring DebugT output behavior
     *
     */
    struct DebugTParamList {
        bool m_enable_color{false};
        bool m_output_std{true}; // true is stdout ,false: is stderr
        bool m_enable_out{true};
        bool m_next_line{true};
    };

    /**
     * @brief Singleton temporary debug logger that outputs formatted messages
     *        with source file and line number information
     *
     */
    class DebugT {
      private:
        const char *const M_NEXT_TABS{"\n\t\t "};
        const char *const M_NEXT_LINE{"\n"};
        logtype::string m_header{"[ TEMP DEBUG:( ] "};
        DebugTParamList m_param_mode{};

      public:
        DebugT() = default;
        ~DebugT() = default;
        DebugT(const DebugT &) = delete;
        DebugT &operator=(const DebugT &) = delete;

      public:
        void set_param_mode(const DebugTParamList &params_ = {});
        auto ostrs(const logtype::string &msg_, const logtype::string &file_, logtype::sd_int line_) -> logtype::string;
        void print(const logtype::string &msg_, const logtype::string &file_, logtype::sd_int line_);
        static auto instance() -> DebugT &;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_DEBUGT_HPP
