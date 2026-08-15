/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_api_log_runtime.hpp
 * src/rstd/logsystem/ruac_api_log_runtime.cpp
 */

#include "rstd/logsystem/ruac_api_log_runtime.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace api {

        /**
         * @brief Set the runtime parameters
         *
         * @param params_ - LogRuntime parameter list containing configuration
         *
         * @details Stores the provided parameter list into m_params for later use
         *          in controlling log runtime behavior, such as enabling/disabling
         *          logging via m_enable_log_runtime.
         *
         */
        void LogRuntime::setting(const LogRuntimeParamList &params_) {
            m_params = params_;
        }

        /**
         * @brief Get the singleton instance of LogRuntime
         *
         * @return LogRuntime& - Reference to the singleton instance
         *
         * @details Implements the singleton pattern using a static local variable.
         *          Returns a reference to the single LogRuntime instance, ensuring
         *          only one instance exists throughout the application.
         *
         */
        auto LogRuntime::instance() -> LogRuntime & {
            static LogRuntime instance_object;
            return instance_object;
        }

        /**
         * @brief Initialize the LogRuntime with loader parameters
         *
         * @param params_ - Loader parameter list for initial configuration
         *
         * @details Creates a Manager instance via std::make_unique, delegates
         *          initialization to m_manager->init(), and sets m_init_done
         *          to true to indicate successful initialization. Must be called
         *          before write() can log messages.
         *
         */
        void LogRuntime::init(const LoaderParamList &params_) {
            m_manager = std::make_unique<Manager>();
            m_manager->init(params_);
            m_init_done = true;
        }

        /**
         * @brief Write a log message with specified level
         *
         * @param level_ - Log level enum (DEBUG, INFO, WARNING, ERROR, FATAL)
         * @param message_ - The log message content
         * @param file_ - Source file name where the log was generated
         * @param line_ - Source line number where the log was generated
         *
         * @details Three-phase guard logic before delegating to the Manager.
         *          First, if not initialized and m_once_msgs is false, outputs
         *          a one-time warning message via Message::instance().stdout_err()
         *          and returns. Second, checks m_params.m_enable_log_runtime and
         *          returns early if logging is disabled. Third, delegates to
         *          m_manager->write() to perform the actual logging.
         *
         */
        void LogRuntime::write(logenum::Level level_, const logtype::string &message_, const logtype::string &file_,
                               logtype::sd_int line_) {

            if (!m_init_done && !m_once_msgs) {
                m_once_msgs = true;
                std::stringstream ss;
                ss << "You must init log runtime first : " << logtime::get_time();
                ss << DebugT::instance().ostrs("", __FILE__, __LINE__);
                Message::instance().stdout_err(ss.str());
                return;
            }

            if (!m_params.m_enable_log_runtime) {
                return;
            }

            m_manager->write(level_, message_, file_, line_);
        }

    } // namespace api

} // namespace ruac::rstd::logsystem
