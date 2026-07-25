/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_loader.hpp
 * src/rstd/logsystem/ruac_loader.cpp
 * Configuration file loader implementation with buffer-based reading and key-value parsing.
 */

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_logkeys.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include "rstd/logsystem/ruac_table.hpp"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>

namespace ruac::rstd::logsystem {

    /**
     * @brief Construct a Loader and immediately load the config file into buffer
     *
     * @param params_ File path and name configuration
     *
     */
    Loader::Loader(const LoaderParamList &params_) {
        m_params = params_;
        load_file_content_to_buffer();
    }

    /**
     * @brief Read the entire config file into a heap-allocated buffer
     * @details Skips if already loaded (once-lock). Reports errors via Message on failure.
     *
     */
    void Loader::load_file_content_to_buffer() {
        if (m_once_lock) {
            return;
        }
        m_once_lock = true;

        auto fullpath = std::filesystem::path(m_params.m_fpath) / m_params.m_fname;
        auto fpath = m_params.m_fpath;
        auto fname = m_params.m_fname;

        if (!std::filesystem::exists(fullpath)) {
            std::stringstream ss;
            ss << "Not found file: " << fullpath.string();
            ss << DebugT::instance().ostrs("", __FILE__, __LINE__);
            Message::instance().stdout_err(ss.str(), "LOAD ");
            return;
        }

        auto f_size = std::filesystem::file_size(fullpath);
        auto b_size = static_cast<std::size_t>(f_size);

        m_buffer.resize(b_size);
        std::ifstream ifs(fullpath);
        ifs.read(reinterpret_cast<char *>(m_buffer.data()), b_size);
        ifs.close();
        m_load_done = true;
    }

    /**
     * @brief Parse the raw buffer content into a key-value StringMap
     *
     * @return Parsed map, or empty map if buffer is null
     *
     */
    auto Loader::parser_buffer_content() -> logtype::strmap {
        logtype::strmap map{};
        if (m_buffer.empty()) {
            return map;
        }

        std::string content(reinterpret_cast<const char *>(m_buffer.data()), m_buffer.size());
        std::istringstream stream(content);
        std::string line;

        while (std::getline(stream, line)) {

            if (line.empty() || line.find(logkeys::kword::G_COMMENT) == 0) {
                continue;
            }

            auto eq_pos = line.find(logkeys::kword::G_EQUAL);
            if (eq_pos == std::string::npos) {
                continue;
            }

            std::string key = line.substr(0, eq_pos);
            std::string value = line.substr(eq_pos + 1);

            key.erase(key.find_last_not_of(" \t") + 1);

            auto quote_start = value.find(logkeys::kword::G_QUOTE);
            auto quote_end = value.rfind(logkeys::kword::G_QUOTE);

            if (quote_start != std::string::npos && quote_end != std::string::npos && quote_start != quote_end) {
                value = value.substr(quote_start + 1, quote_end - quote_start - 1);
            }

            auto semicolon_pos = value.find(logkeys::kword::G_SEMICOLON);
            if (semicolon_pos != std::string::npos) {
                value = value.substr(0, semicolon_pos);
            }

            value.erase(value.find_last_not_of(" \t") + 1);
            map[key] = value;
        }
        return map;
    }

    /**
     * @brief Return the parsed config as a StringMap, loading the file if needed
     *
     * @param params_ Optional override for file path and name
     *
     * @return Parsed key-value map, or empty map on failure
     *
     */
    auto Loader::getmap(const LoaderParamList &params_) -> logtype::strmap {
        if (!params_.m_fpath.empty()) {
            m_params.m_fpath = params_.m_fpath;
        }
        if (!params_.m_fname.empty()) {
            m_params.m_fname = params_.m_fname;
        }
        if (!m_once_lock) {
            load_file_content_to_buffer();
        }
        if (!m_load_done) {
            return {};
        }
        return parser_buffer_content();
    }

    /**
     * @brief Print the parsed config map as an ASCII table to stdout
     *
     * @param strmap_  The key-value map to display
     */
    void Loader::outmap(const logtype::strmap &strmap_) {

        if (strmap_.empty()) {
            std::stringstream ss;
            ss << "Loader outmap failed ! Because the map is empty.";
            ss << DebugT::instance().ostrs("", __FILE__, __LINE__);
            Message::instance().stdout_err(ss.str(), "LOAD ");
            return;
        }

        auto table = Table();
        std::vector<logtype::string> h{"CONFIG@KEY", "CONFIG@VAL"};
        auto t = strmap_;
        table.set_param_list({h, t});
        table.print(TableType::STRMAP);
    }

} // namespace ruac::rstd::logsystem
