/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_output_console.hpp
 * src/rstd/logsystem/ruac_output_console.cpp
 */

#include "rstd/logsystem/ruac_output_console.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Writes a log message to standard output with thread-safe synchronization.
     *
     * @param message_  The formatted log message string to write.
     */
    void OutputConsole::output(const logtype::string &message_) {
        std::osyncstream(std::cout) << message_ << std::endl;
    }

} // namespace ruac::rstd::logsystem
