/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_nullproc.hpp
 * src/rstd/logsystem/ruac_nullproc.cpp
 * Description of header file function declaration
 *
 * Defines null-output placeholder functions for no-op operations
 *
 */

#pragma once
#ifndef RUAC_NULLPROC_HPP
#define RUAC_NULLPROC_HPP

#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace nullproc {

        /**
         * @brief Returns an empty string, used as a null-output placeholder.
         *
         * @return An empty logtype::string instance.
         */
        auto nostr() -> logtype::string;

        /**
         * @brief No-op function, used as a null-callback placeholder.
         */
        void donot();

        auto next_line() -> logtype::string;

    } // namespace nullproc

} // namespace ruac::rstd::logsystem

#endif // RUAC_NULLPROC_HPP
