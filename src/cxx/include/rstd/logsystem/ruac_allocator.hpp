/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_allocator.hpp
 * src/rstd/logsystem/ruac_allocator.cpp
 * Description of header file function declaration
 * Log configuration allocator that validates config file paths, loads settings
 * into a key-value map, and supports manual override with priority control.
 *
 */

#pragma once
#ifndef RUAC_ALLOCATOR_HPP
#define RUAC_ALLOCATOR_HPP

#include "rstd/logsystem/ruac_logpath.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Parameter list for configuring the config file path and name to read
     *
     */
    struct AllocatorParamList {
        logtype::String m_read_config_file_path{logpath::G_READ_LOG_CONFIG_FILE_PATH};
        logtype::String m_read_config_file_name{logpath::G_READ_LOG_CONFIG_FILE_NAME};
    };

    /**
     * @brief Typed settings structure for log system configuration.
     *        Provides default values that match the built-in default map.
     *
     */
    struct AllocatorMapSettings {
        logtype::Bool m_enable_term_compatible_mode{true};
        logtype::Bool m_enable_term_highlight_mode{false};
        logtype::Bool m_enable_term_bold_font_mode{false};
        logtype::Bool m_enable_term_log_print_mode{false};
        logtype::String m_log_term_format_style{"text"};
        logtype::String m_log_file_format_style{"text"};
        logtype::String m_log_output_mode{"console"};
        logtype::String m_log_write_path{logpath::G_WRITE_LOG_PATH};
        logtype::String m_log_write_file{logpath::G_WRITE_LOG_FILE};
        logtype::String m_log_file_size_limit{"128M"};
        logtype::String m_term_log_level_filter{"debug"};
        logtype::String m_file_log_level_filter{"debug"};
        logtype::String m_minimum_log_level{"debug"};
    };

    /**
     * @brief Manages log configuration loading with three-layer priority:
     *        manual settings > config file > defaults. Loads once and supports override.
     *
     */
    class Allocator {
      private:
        logtype::Bool m_check_done{false};
        logtype::Bool m_once_lock{false};
        logtype::Bool m_has_manual_settings{false};
        AllocatorParamList m_params{};
        AllocatorMapSettings m_manual_settings{};
        const char *const M_LOAD_KEYWORD{"LOAD "};
        logtype::StringMap m_confmap{};

      private:
        void checkpath(const AllocatorParamList &params_ = {});
        void getmap();

      public:
        Allocator() = default;
        Allocator(const AllocatorParamList &params_);
        ~Allocator() = default;

      public:
        void setmap(const AllocatorMapSettings &params_);
        auto getconfmap() -> logtype::StringMap;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_ALLOCATOR_HPP
