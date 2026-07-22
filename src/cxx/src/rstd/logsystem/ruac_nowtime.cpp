/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_nowtime.hpp
 * src/rstd/logsystem/ruac_nowtime.cpp
 */

#include "rstd/logsystem/ruac_nowtime.hpp"
#include <chrono>
#include <format>

namespace ruac::rstd::logsystem {

    namespace nowtime {

        /**
         * @brief Generates a formatted local-time string in C++26 chrono style.
         *
         * @return Formatted timestamp string in "YYYY-MM-DD-HH-MM-SS" format.
         */
        auto get_time() -> logtype::String {
            auto now = std::chrono::system_clock::now();
            auto ltm = std::chrono::current_zone()->to_local(now);
            return std::format("{:%Y-%m-%d-%H-%M-%S}", ltm);
        }

    } // namespace nowtime

} // namespace ruac::rstd::logsystem
