/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/kit/ruac_safemsg.hpp
 * src/google_test/kit/ruac_safemsg.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"

#include <iostream>
#include <syncstream>
#include <sstream>

namespace ruac::google_test::kit {

    auto SafeMsg::get() -> SafeMsg & {
        static SafeMsg instance;
        return instance;
    }

    void SafeMsg::set_output_mode(const bool stdout_) {
        std::lock_guard<std::mutex> lock(M_SAFE_MSG_MTX);
        m_stdout = stdout_;
    }

    void SafeMsg::println(const std::string &msg_header_, const std::string &msg_body_) {
        std::lock_guard<std::mutex> lock(M_SAFE_MSG_MTX);
        {
            std::stringstream ss;
            ss << msg_header_ << msg_body_;
            if (m_stdout) {
                std::osyncstream(std::cout) << ss.str() << std::endl;
            } else {
                std::osyncstream(std::cerr) << ss.str() << std::endl;
            }
        }
    }

    void SafeMsg::print(const std::string &msg_header_, const std::string &msg_body_) {
        std::lock_guard<std::mutex> lock(M_SAFE_MSG_MTX);
        {
            std::stringstream ss;
            ss << msg_header_ << msg_body_;
            if (m_stdout) {
                std::osyncstream(std::cout) << ss.str() << std::flush;
            } else {
                std::osyncstream(std::cerr) << ss.str() << std::flush;
            }
        }
    }

} // namespace ruac::google_test::kit
