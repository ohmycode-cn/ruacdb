/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_output.hpp
 * src/rstd/logsystem/ruac_output.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_OUTPUT_HPP
#define RUAC_OUTPUT_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    /**
     * @brief Abstract interface for log message output destinations.
     *
     * Implementations define where a formatted log message is written
     * (e.g. console, file, network socket, remote collector).
     * Concrete backends should derive from this class and override output().
     */
    class Output {
      public:
        /**
         * @brief Write a formatted log message to the destination.
         *
         * @param message_ The fully formatted log message to output.
         */
        virtual void output(const logtype::string &message_) = 0;

        virtual ~Output() = default;
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_OUTPUT_HPP
