/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logpath.hpp
 * src/rstd/logsystem/ruac_logpath.cpp
 * @brief Defines platform-specific file paths and names for log system configuration and output.
 */

#pragma once
#ifndef RUAC_LOGPATH_HPP
#define RUAC_LOGPATH_HPP

namespace ruac::rstd::logsystem {

    namespace logpath {

        const char *const G_READ_LOG_CONFIG_FILE_NAME{"ruacdb.log.conf"};
        const char *const G_LOG_WRITE_FILE_NAME{"ruacdb.default.log"};

#if defined(__linux__) || defined(__gnu_linux__)
        const char *const G_READ_LOG_CONFIG_FILE_PATH{"/etc/ruacdb"};
        const char *const G_LOG_WRITE_FILE_PATH{"/var/log/ruacdb"};
#elif defined(_WIN32) || defined(_WIN64)
        const char *const G_LOG_WRITE_FILE_PATH{"C:\\Users\\RuacDB\\Log"};
        const char *const G_READ_LOG_CONFIG_FILE_PATH{"C:\\Users\\RuacDB\\Etc"};
#else
#error "Unsupported platform: only Windows and Linux are supported"
#endif

    } // namespace logpath

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGPATH_HPP
