/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_api_log_runtime.hpp
 * src/rstd/logsystem/ruac_api_log_runtime.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_API_LOG_RUNTIME_HPP
#define RUAC_API_LOG_RUNTIME_HPP

#include "rstd/logsystem/ruac_manager.hpp"
#include <memory>

namespace ruac::rstd::logsystem {

    namespace api {

        class LogRuntime {
          private:
            LogRuntime() = default;
            ~LogRuntime() = default;
            LogRuntime(const LogRuntime &) = delete;
            LogRuntime &operator=(const LogRuntime &) = delete;

          private:
            std::unique_ptr<Manager> m_manager{nullptr};
            bool m_init_done{false};
            bool m_once_msgs{false};

          public:
            static auto instance() -> LogRuntime &;
            void init();
            void write(logenum::Level level_, const logtype::string &message_, const logtype::string &file_,
                       logtype::sd_int line_);
        };

    } // namespace api

} // namespace ruac::rstd::logsystem

#define RUAC_API_LOG_RUNTIME(level_, message_) ruac::rstd::logsystem::api::LogRuntime::instance().write(level_, message_, __FILE__, __LINE__);
#define RUAC_RUNTIME_DEBUG(message_) RUAC_API_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::DEBUG, message_)
#define RUAC_RUNTIME_INFO(message_) RUAC_API_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::INFO, message_)
#define RUAC_RUNTIME_WARNING(message_) RUAC_API_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::WARNING, message_)
#define RUAC_RUNTIME_ERROR(message_) RUAC_API_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::ERROR, message_)
#define RUAC_RUNTIME_FATAL(message_) RUAC_API_LOG_RUNTIME(ruac::rstd::logsystem::logenum::Level::FATAL, message_)

#endif // RUAC_API_LOG_RUNTIME_HPP
