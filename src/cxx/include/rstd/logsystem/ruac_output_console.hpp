/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_output_console.hpp
 * src/rstd/logsystem/ruac_output_console.cpp
 * Description of header file function declaration
 *
 * Defines the console output sink for writing log messages to stdout
 *
 */

#pragma once
#ifndef RUAC_OUTPUT_CONSOLE_HPP
#define RUAC_OUTPUT_CONSOLE_HPP

#include "rstd/logsystem/ruac_logtype.hpp"
#include "rstd/logsystem/ruac_output.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Console-output sink that writes formatted log messages to stdout.
     *        Uses std::osyncstream for thread-safe output synchronization.
     */
    class OutputConsole : public Output {
      public:
        OutputConsole() = default;
        ~OutputConsole() = default;

      public:
        void output(const logtype::string &message_);
    }; // class OutputConsole

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_CONSOLE_HPP
