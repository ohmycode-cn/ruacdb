/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_debugt.hpp
 * src/rstd/logsystem/ruac_debugt.cpp
 * Description of source file function implementation
 *
 */

#include "rstd/logsystem/ruac_debugt.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Update output parameters; enables ANSI color header when m_enable_color is set
     *
     * @param params_ Configuration values to apply
     *
     */
    void DebugT::set_param_mode(const DebugTParamList &params_) {
        m_param_mode.m_enable_out = params_.m_enable_out;
        m_param_mode.m_output_std = params_.m_output_std;
        m_param_mode.m_next_line = params_.m_next_line;
        if (params_.m_enable_color) {
            m_header = "[ \033[40m\033[1;31mTEMP DEBUG:(\033[0m ] ";
        }
    }

    /**
     * @brief Format a debug message with file and line info, return as string without output
     *
     * @param msg_  The debug message content
     * @param file_ Source file path
     * @param line_ Source line number
     *
     * @return Formatted string, or empty string when output is disabled
     *
     */
    auto DebugT::print_string(const logtype::String &msg_, const logtype::String &file_, logtype::Int line_)
        -> logtype::String {

        if (!m_param_mode.m_enable_out) {
            return "";
        }

        std::stringstream ss;

        if (m_param_mode.m_next_line) {
            ss << M_NEXT_LINE;
        }

        ss << m_header << msg_;

        if (!msg_.empty()) {
            ss << M_NEXT_TABS;
        }

        ss << "FILE: " << file_ << M_NEXT_TABS;
        ss << "LINE: " << line_;

        return ss.str();
    }

    /**
     * @brief Format and output a debug message to stdout or stderr via osyncstream
     * @details Delegates formatting to print_string(), then writes the result
     *          to the configured stream. Thread-safe via std::osyncstream.
     *
     * @param msg_  The debug message content
     * @param file_ Source file path
     * @param line_ Source line number
     *
     */
    void DebugT::print(const logtype::String &msg_, const logtype::String &file_, logtype::Int line_) {

        if (msg_.empty() || !m_param_mode.m_enable_out) {
            return;
        }

        const auto formatted = print_string(msg_, file_, line_);

        if (m_param_mode.m_output_std) {
            std::osyncstream(std::cout) << formatted << std::endl;
        } else {
            std::osyncstream(std::cerr) << formatted << std::endl;
        }
    }

    /**
     * @brief Return the global singleton DebugT instance
     *
     * @return Reference to the static DebugT object
     *
     */
    auto DebugT::instance() -> DebugT & {
        static DebugT instance_object;
        return instance_object;
    };

} // namespace ruac::rstd::logsystem
