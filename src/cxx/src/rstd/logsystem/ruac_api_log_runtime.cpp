/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_api_log_runtime.hpp
 * src/rstd/logsystem/ruac_api_log_runtime.cpp
 */

#include "rstd/logsystem/ruac_api_log_runtime.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include <sstream>

namespace ruac::rstd::logsystem {

    namespace api {

        auto LogRuntime::instance() -> LogRuntime & {
            static LogRuntime instance_object;
            return instance_object;
        }

        void LogRuntime::init(const LoaderParamList &params_) {
            m_manager = std::make_unique<Manager>();
            m_manager->init(params_);
            m_init_done = true;
        }

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
            m_manager->write(level_, message_, file_, line_);
        }

    } // namespace api

} // namespace ruac::rstd::logsystem
