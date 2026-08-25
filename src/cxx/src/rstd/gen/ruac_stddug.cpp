/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/gen/ruac_stddug.hpp
 * src/rstd/gen/ruac_stddug.cpp
 */

#include "rstd/gen/ruac_stddug.hpp"
#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::rstd::gen {

    StdDug::StdDug(bool prompt_header_next_line_) {
        if (prompt_header_next_line_) {
            m_header = "[ TEMP DEBUG:( ] \n";
        } else {
            m_header = "[ TEMP DEBUG:( ] ";
        }
    }

    /**
     * @brief Update output parameters; enables ANSI color header when m_enable_color is set
     *
     * @param params_ Configuration values to apply
     *
     */
    void StdDug::set_param_mode(const StdDebugParamList &params_) {
        std::lock_guard<std::mutex> lock(M_STDDUG_MTX);
        m_param_mode.m_enable_out = params_.m_enable_out;
        m_param_mode.m_output_std = params_.m_output_std;
        m_param_mode.m_enable_header = params_.m_enable_header;
        m_param_mode.m_next_line = params_.m_next_line;
        if (params_.m_enable_color) {
            m_header = "[ \033[40m\033[1;31mTEMP DEBUG:(\033[0m ] ";
        }
    }

    auto StdDug::ostrs_view(std::string_view msg_, std::string_view file_, int line_) -> std::string {

        std::lock_guard<std::mutex> lock(M_STDDUG_MTX);

        if (!m_param_mode.m_enable_out) {
            return "";
        }

        std::stringstream ss;

        if (m_param_mode.m_next_line) {
            ss << M_NEXT_LINE;
        }

        if (m_param_mode.m_enable_header) {
            ss << m_header;
        }
        ss << msg_;

        if (!msg_.empty()) {
            ss << M_NEXT_TABS;
        }

        ss << "FILE: " << file_ << M_NEXT_TABS;
        ss << "LINE: " << line_;

        return ss.str();
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
    auto StdDug::ostrs(const std::string &msg_, const std::string &file_, int line_) -> std::string {

        std::lock_guard<std::mutex> lock(M_STDDUG_MTX);

        if (!m_param_mode.m_enable_out) {
            return "";
        }

        std::stringstream ss;

        if (m_param_mode.m_next_line) {
            ss << M_NEXT_LINE;
        }

        if (m_param_mode.m_enable_header) {
            ss << m_header;
        }
        ss << msg_;

        if (!msg_.empty()) {
            ss << M_NEXT_TABS;
        }

        ss << "FILE: " << file_ << M_NEXT_TABS;
        ss << "LINE: " << line_;

        return ss.str();
    }

    /**
     * @brief Format and output a debug message to stdout or stderr via osyncstream
     * @details Delegates formatting to ostrs(), then writes the result
     *          to the configured stream. Thread-safe via std::osyncstream.
     *
     * @param msg_  The debug message content
     * @param file_ Source file path
     * @param line_ Source line number
     *
     */
    void StdDug::print(const std::string &msg_, const std::string &file_, int line_) {

        if (msg_.empty()) {
            return;
        }

        std::lock_guard<std::mutex> lock(M_STDDUG_MTX);

        if (!m_param_mode.m_enable_out) {
            return;
        }

        std::stringstream ss;
        if (m_param_mode.m_next_line) {
            ss << M_NEXT_LINE;
        }
        if (m_param_mode.m_enable_header) {
            ss << m_header;
        }
        ss << msg_;
        if (!msg_.empty()) {
            ss << M_NEXT_TABS;
        }
        ss << "FILE: " << file_ << M_NEXT_TABS;
        ss << "LINE: " << line_;

        if (m_param_mode.m_output_std) {
            std::osyncstream(std::cout) << ss.str() << std::endl;
        } else {
            std::osyncstream(std::cerr) << ss.str() << std::endl;
        }
    }

} // namespace ruac::rstd::gen
