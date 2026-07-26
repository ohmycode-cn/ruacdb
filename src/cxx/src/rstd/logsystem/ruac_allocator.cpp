/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_allocator.hpp
 * src/rstd/logsystem/ruac_allocator.cpp
 */

#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_confmap.hpp"
#include "rstd/logsystem/ruac_logenum.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
// #include "rstd/logsystem/ruac_message.hpp"
// #include "rstd/logsystem//ruac_debugt.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::rstd::logsystem {

    namespace {

        namespace w = logkeys::kword;

    };

    /**
     * @brief Construct an Allocator and initialize from loader parameters
     *
     * @param loader_param_list - List of loader parameters for configuration
     *
     * @details Creates a Loader instance within a scoped block to populate
     *          m_loader_map and m_loader_msg, then calls init_default_map()
     *          to initialize default configuration, parser_verify_configure_map()
     *          to validate and parse configuration values. The scoped block ensures
     *          the Loader is destroyed after initialization completes.
     *
     */
    Allocator::Allocator(const LoaderParamList &loader_param_list) {
        {
            Loader loader(loader_param_list);
            m_loader_map = loader.getmap();
            m_loader_msg = loader.outmap_string(m_loader_map);
            init_default_map();
        }
        parser_verify_configure_map();
    }

    /**
     * @brief Parse a boolean configuration value
     *
     * @param map_ - Configuration map to read from
     * @param key_ - Key to look up in the map
     * @param val_ - Reference to store the parsed boolean value
     *
     * @details Looks up the value associated with key_ in map_ and sets val_
     *          to true if the string equals "true", otherwise false.
     *
     */
    void Allocator::parser_config_bool_value(logtype::strmap &map_, const logtype::string key_, bool &val_) {
        if ("true" == map_.at(key_)) {
            val_ = true;
        } else {
            val_ = false;
        }
    }

    /**
     * @brief Parse an output mode configuration value
     *
     * @param map_ - Configuration map to read from
     * @param key_ - Key to look up in the map
     * @param val_ - Reference to store the parsed Output enum value
     * @param isf_ - Flag to check if the configuration is for a file output
     *
     * @details Looks up the value associated with key_ in map_ and sets val_
     *          to logenum::Output::FILE if the string equals "file", otherwise
     *          logenum::Output::CONSOLE.
     *
     */
    void Allocator::parser_config_output(logtype::strmap &map_, const logtype::string key_, logenum::Output &val_,
                                         bool isf_) {
        if (isf_ && m_once_lock_guard) {
            return;
        }

        if ("file" == map_.at(key_)) {
            val_ = logenum::Output::FILE;
        } else {
            val_ = logenum::Output::CONSOLE;
        }
        m_once_lock_guard = true;
    }

    /**
     * @brief Parse a format style configuration value
     *
     * @param map_ - Configuration map to read from
     * @param key_ - Key to look up in the map
     * @param val_ - Reference to store the parsed Format enum value
     * @param isf_ - Flag to check if the configuration is for a file output
     *
     * @details Looks up the value associated with key_ in map_ and sets val_
     *          to logenum::Format::JSON if "json", logenum::Format::XML if "xml",
     *          otherwise logenum::Format::TEXT as the default.
     *
     */
    void Allocator::parser_config_format(logtype::strmap &map_, const logtype::string key_, logenum::Format &val_,
                                         bool isf_) {

        if (isf_ && m_once_lock_guard) {
            return;
        }

        if ("json" == map_.at(key_)) {
            val_ = logenum::Format::JSON;
        } else if ("xml" == map_.at(key_)) {
            val_ = logenum::Format::XML;
        } else {
            val_ = logenum::Format::TEXT;
        }

        m_once_lock_guard = true;
    }

    /**
     * @brief Parse a log level configuration value
     *
     * @param map_ - Configuration map to read from
     * @param key_ - Key to look up in the map
     * @param val_ - Reference to store the parsed Level enum value
     *
     * @details Looks up the value associated with key_ in map_ and sets val_
     *          to the corresponding logenum::Level: INFO for "info", WARNING
     *          for "warning", ERROR for "error", FATAL for "fatal", otherwise
     *          DEBUG as the default.
     *
     */
    void Allocator::parser_config_log_level(logtype::strmap &map_, const logtype::string key_, logenum::Level &val_) {
        if ("info" == map_.at(key_)) {
            val_ = logenum::Level::INFO;
        } else if ("warning" == map_.at(key_)) {
            val_ = logenum::Level::WARNING;
        } else if ("error" == map_.at(key_)) {
            val_ = logenum::Level::ERROR;
        } else if ("fatal" == map_.at(key_)) {
            val_ = logenum::Level::FATAL;
        } else {
            val_ = logenum::Level::DEBUG;
        }
    }

    /**
     * @brief Initialize the default configuration map
     *
     * @details Populates m_default_map with default configuration values
     *          retrieved from confmap::get_default_config_map().
     *
     */
    void Allocator::init_default_map() {
        m_default_map = confmap::get_default_config_map();
    }

    /**
     * @brief Verify and parse the configuration map
     *
     * @details Validates and parses configuration values by merging loader
     *          map entries into the default map. First copies m_default_map
     *          into m_std_map, then iterates through m_loader_map to overwrite
     *          matching entries. Extracts file path, file name, and size limit
     *          values from the merged map. Finally delegates to helper parser
     *          functions to populate m_param_list with boolean flags, output
     *          modes, format styles, and log level filters for terminal, file,
     *          and mini logging.
     *
     */
    void Allocator::parser_verify_configure_map() {

        m_std_map = m_default_map;

        for (const auto &pair : m_loader_map) {
            m_std_map[pair.first] = pair.second;
        }

        auto tmp_path = m_std_map.at(w::G_LOG_WRITE_FILE_PATH);
        if (!tmp_path.empty()) {
            m_param_list.m_wf_path = tmp_path;
        }
        auto tmp_file = m_std_map.at(w::G_LOG_WRITE_FILE_NAME);
        if (!tmp_file.empty()) {
            m_param_list.m_wf_name = tmp_file;
        }
        auto tmp_size = m_std_map.at(w::G_LOG_FILE_SIZE_LIMIT);
        if (!tmp_size.empty()) {
            m_param_list.m_limit_f = tmp_size;
        }

        parser_config_bool_value(m_std_map, w::G_ENABLE_TERM_COMPATIBLE_MODE,
                                 m_param_list.m_enable_ce);
        parser_config_bool_value(m_std_map, w::G_ENABLE_TERM_HIGHLIGHT_MODE,
                                 m_param_list.m_enable_ht);
        parser_config_bool_value(m_std_map, w::G_ENABLE_TERM_BOLD_FONT_MODE,
                                 m_param_list.m_enable_bf);

        parser_config_output(m_std_map, w::G_LOG_TERM_OUTPUT_MODE,
                             m_param_list.m_term_output, false);
        parser_config_output(m_std_map, w::G_LOG_FILE_OUTPUT_MODE,
                             m_param_list.m_file_output, true);

        parser_config_format(m_std_map, w::G_LOG_TERM_FORMAT_STYLE,
                             m_param_list.m_term_format, false);
        parser_config_format(m_std_map, w::G_LOG_FILE_FORMAT_STYLE,
                             m_param_list.m_file_format, true);

        parser_config_log_level(m_std_map, w::G_LOG_TERM_LEVEL_FILTER,
                                m_param_list.m_term_level);
        parser_config_log_level(m_std_map, w::G_LOG_FILE_LEVEL_FILTER,
                                m_param_list.m_file_level);
        parser_config_log_level(m_std_map, w::G_LOG_MINI_LEVEL_FILTER,
                                m_param_list.m_mini_level);
    }

    /**
     * @brief Get the parameter list
     *
     * @return AllocatorParamList - Copy of the internal parameter list
     *
     * @details Returns a copy of m_param_list containing the allocator's
     *          configuration parameters.
     *
     */
    auto Allocator::get_param_list() -> AllocatorParamList {
        return m_param_list;
    }

    /**
     * @brief Output the loader message to standard output
     *
     * @details Writes m_loader_msg to stdout using std::osyncstream for
     *          thread-safe concurrent output. The message includes loader
     *          configuration information captured during initialization.
     *
     */
    void Allocator::out_loader_msg() {
        std::osyncstream(std::cout) << m_loader_msg << std::endl;
    }

} // namespace ruac::rstd::logsystem
