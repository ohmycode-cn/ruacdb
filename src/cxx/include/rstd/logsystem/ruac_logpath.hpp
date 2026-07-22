/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_logpath.hpp
 * src/rstd/logsystem/ruac_logpath.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LOGPATH_HPP
#define RUAC_LOGPATH_HPP
namespace ruac::rstd::logsystem {

    namespace logpath {

        const char *const G_READ_LOG_CONFING_FILE{"ruacdb.log.config"};
        const char *const G_WRITE_LOG_FILE{"ruacdb.default.log"};

#if defined(__linux__)
        const char *const G_WRITE_LOG_PATH{"/var/log/ruacdb"};
        const char *const G_READ_LOG_PATH{"/etc/ruacdb"};
#endif

#if defined(__Win32__) || defined(__Win64__) || defined(__WIN32__) || \
    defined(__WIN64__)
        const char *const G_WRITE_LOG_PATH{"C:\\Users\\RuacDB\\Log"};
        const char *const G_READ_LOG_PATH{"C:\\Users\\RuacDB\\Etc"};
#endif

    } // namespace logpath

} // namespace ruac::rstd::logsystem

#endif // RUAC_LOGPATH_HPP
