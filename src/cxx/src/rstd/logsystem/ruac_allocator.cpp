/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_allocator.hpp
 * src/rstd/logsystem/ruac_allocator.cpp
 * Allocator implementation with config path validation, one-time map loading,
 * and manual settings overlay. Anonymous namespace contains settings-to-map
 * conversion, default map factory, and map merge utility.
 */

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_logpath.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include <filesystem>
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace {

        namespace k = logkeys::word;

        /**
         * @brief Convert an AllocatorMapSettings struct to a key-value StringMap
         *
         * @param s Settings struct to convert
         *
         * @return StringMap with config keys mapped to string values
         *
         */
        auto settings_to_map(const AllocatorMapSettings &s) -> logtype::StringMap {
            return {
                {k::G_ENABLE_TERM_COMPATIBLE_MODE, s.m_enable_term_compatible_mode ? k::G_TRUE : k::G_FALSE},
                {k::G_ENABLE_TERM_HIGHLIGHT_MODE, s.m_enable_term_highlight_mode ? k::G_TRUE : k::G_FALSE},
                {k::G_ENABLE_TERM_BOLD_FONT_MODE, s.m_enable_term_bold_font_mode ? k::G_TRUE : k::G_FALSE},
                {k::G_ENABLE_TERM_LOG_PRINT_MODE, s.m_enable_term_log_print_mode ? k::G_TRUE : k::G_FALSE},
                {k::G_LOG_TERM_FORMAT_STYLE, s.m_log_term_format_style},
                {k::G_LOG_FILE_FORMAT_STYLE, s.m_log_file_format_style},
                {k::G_LOG_OUTPUT_MODE, s.m_log_output_mode},
                {k::G_LOG_WRITE_PATH, s.m_log_write_path},
                {k::G_LOG_WRITE_FILE, s.m_log_write_file},
                {k::G_LOG_FILE_SIZE_LIMIT, s.m_log_file_size_limit},
                {k::G_TERM_LOG_LEVEL_FILTER, s.m_term_log_level_filter},
                {k::G_FILE_LOG_LEVEL_FILTER, s.m_file_log_level_filter},
                {k::G_MINIMUM_LOG_LEVEL, s.m_minimum_log_level}};
        }

        /**
         * @brief Create a StringMap from default AllocatorMapSettings
         *
         * @return StringMap with all default configuration values
         *
         */
        auto get_default_map() -> logtype::StringMap {
            return settings_to_map(AllocatorMapSettings{});
        }

        /**
         * @brief Merge overlay entries into base map, overwriting existing keys
         *
         * @param base  Target map to merge into
         * @param overlay Source map whose entries take priority
         *
         */
        void merge_map(logtype::StringMap &base, const logtype::StringMap &overlay) {
            for (const auto &[key, val] : overlay) {
                base[key] = val;
            }
        }

    } // namespace

    /**
     * @brief Construct an Allocator, validate config file path, and load the map
     *
     * @param params_ File path and name configuration
     *
     */
    Allocator::Allocator(const AllocatorParamList &params_) : m_params(params_) {
        checkpath(params_);
        getmap();
    }

    /**
     * @brief Validate config file path and name, falling back to defaults on failure.
     *        Sets m_check_done to true only if a valid regular file is found.
     *
     * @param params_ File path and name to validate
     *
     */
    void Allocator::checkpath(const AllocatorParamList &params_) {

        auto fpath = params_.m_read_config_file_path;
        auto fname = params_.m_read_config_file_name;

        if (!std::filesystem::exists(fpath)) {
            std::stringstream ss;
            ss << "Load ruacdb log config file path not exist: " << fpath << nullproc::nextline();
            ss << DebugT::instance().print_string("", __FILE__, __LINE__);
            Message::instance().stdout_war(ss.str(), M_LOAD_KEYWORD);

            fpath = logpath::G_READ_LOG_CONFIG_FILE_PATH;
            if (!std::filesystem::exists(fpath)) {
                std::stringstream ss2;
                ss2 << "Load ruacdb log config default file path not exist: " << fpath << nullproc::nextline();
                ss2 << DebugT::instance().print_string("", __FILE__, __LINE__);
                Message::instance().stdout_err(ss2.str(), M_LOAD_KEYWORD);
                return;
            }
        }

        auto fullpath = std::filesystem::path(fpath) / fname;
        if (!std::filesystem::exists(fullpath)) {
            std::stringstream ss;
            ss << "Load ruacdb log config file not exist: " << fname << nullproc::nextline();
            ss << DebugT::instance().print_string("", __FILE__, __LINE__);
            Message::instance().stdout_war(ss.str(), M_LOAD_KEYWORD);

            fname = logpath::G_READ_LOG_CONFIG_FILE_NAME;
            fullpath = std::filesystem::path(fpath) / fname;
            if (!std::filesystem::exists(fullpath)) {
                std::stringstream ss2;
                ss2 << "Load ruacdb log config default file not exist: " << fname << nullproc::nextline();
                ss2 << DebugT::instance().print_string("", __FILE__, __LINE__);
                Message::instance().stdout_err(ss2.str(), M_LOAD_KEYWORD);
                return;
            }
        }

        if (!std::filesystem::is_regular_file(fullpath)) {
            std::stringstream ss;
            ss << "Load ruacdb log config file not regular file: " << nullproc::nextline();
            ss << DebugT::instance().print_string("", __FILE__, __LINE__);
            Message::instance().stdout_err(ss.str(), M_LOAD_KEYWORD);
            return;
        }

        m_params.m_read_config_file_path = fpath;
        m_params.m_read_config_file_name = fname;
        m_check_done = true;
    }

    /**
     * @brief Load configuration map once. Uses config file if available, otherwise defaults.
     *        Applies manual settings overlay if setmap was called.
     *
     */
    void Allocator::getmap() {
        if (!m_once_lock) {
            if (!m_check_done) {
                m_confmap = get_default_map();
            } else {
                Loader loader;
                LoaderParamList p;
                p.m_fpath = m_params.m_read_config_file_path;
                p.m_fname = m_params.m_read_config_file_name;
                m_confmap = loader.getmap(p);
            }
            m_once_lock = true;
        }
        if (m_has_manual_settings) {
            merge_map(m_confmap, settings_to_map(m_manual_settings));
        }
    }

    /**
     * @brief Store manual settings and merge them onto the current config map.
     *        Manual settings take priority over file-loaded and default values.
     *
     * @param params_ Manual settings to apply
     *
     */
    void Allocator::setmap(const AllocatorMapSettings &params_) {
        m_manual_settings = params_;
        m_has_manual_settings = true;
        merge_map(m_confmap, settings_to_map(params_));
    }

    /**
     * @brief Return the current configuration map
     *
     * @return The merged key-value configuration map
     *
     */
    auto Allocator::getconfmap() -> logtype::StringMap {
        return m_confmap;
    }

} // namespace ruac::rstd::logsystem
