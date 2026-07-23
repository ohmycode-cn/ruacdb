/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_nullproc.hpp
 * src/rstd/logsystem/ruac_nullproc.cpp
 * Description of header file function declaration
 * Declares null-operation placeholder utilities for the RUAC log system.
 * Provides two no-op functions within the nullproc namespace: nostr()
 * returns an empty string as a null-output placeholder, and donot()
 * serves as a null-callback placeholder. These utilities implement the
 * null-object pattern, enabling optional log sinks and formatters to
 * be safely omitted without conditional checks at call sites.
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
         * @return An empty logtype::String instance.
         */
        auto nostr() -> logtype::String;

        /**
         * @brief No-op function, used as a null-callback placeholder.
         */
        void donot();

        auto nextline() -> logtype::String;

    } // namespace nullproc

} // namespace ruac::rstd::logsystem

#endif // RUAC_NULLPROC_HPP
