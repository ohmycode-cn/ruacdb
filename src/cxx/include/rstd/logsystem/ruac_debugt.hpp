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
        logtype::Bool m_enable_color{false};
        logtype::Bool m_output_std{true}; // true is stdout ,false: is stderr
        logtype::Bool m_enable_out{true};
        logtype::Bool m_next_line{true};
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
        logtype::String m_header{"[ TEMP DEBUG:( ] "};
        DebugTParamList m_param_mode{};

      public:
        DebugT() = default;
        ~DebugT() = default;
        DebugT(const DebugT &) = delete;
        DebugT &operator=(const DebugT &) = delete;

      public:
        void set_param_mode(const DebugTParamList &params_ = {});
        auto print_string(const logtype::String &msg_, const logtype::String &file_, logtype::Int line_)
            -> logtype::String;
        void print(const logtype::String &msg_, const logtype::String &file_, logtype::Int line_);
        static auto instance() -> DebugT &;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_DEBUGT_HPP
