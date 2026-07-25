/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_loader.hpp
 * src/rstd/logsystem/ruac_loader.cpp
 * Description of header file function declaration
 * Configuration file loader that reads and parses log config files into key-value maps.
 *
 */

#pragma once
#ifndef RUAC_LOADER_HPP
#define RUAC_LOADER_HPP

#include "rstd/logsystem/ruac_logpath.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <vector>

namespace ruac::rstd::logsystem {

    /**
     * @brief Parameter list for configuring the Loader file path and name
     *
     */
    struct LoaderParamList {
        logtype::string m_fpath{logpath::G_READ_LOG_CONFIG_FILE_PATH};
        logtype::string m_fname{logpath::G_READ_LOG_CONFIG_FILE_NAME};
    };

    /**
     * @brief Reads a log configuration file into memory and parses it into a StringMap.
     *        Supports one-time loading with a lock mechanism to prevent repeated reads.
     *
     */
    class Loader {
      private:
        std::vector<std::byte> m_buffer;
        LoaderParamList m_params;
        bool m_once_lock{false};
        bool m_load_done{false};

      private:
        void load_file_content_to_buffer();
        auto parser_buffer_content() -> logtype::strmap;

      public:
        Loader() = default;
        Loader(const LoaderParamList &params_);
        ~Loader() = default;

      public:
        auto getmap(const LoaderParamList &params_ = {}) -> logtype::strmap;
        void outmap(const logtype::strmap &strmap_);
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOADER_HPP
