/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_nullproc.hpp
 * src/rstd/logsystem/ruac_nullproc.cpp
 */

#include "rstd/logsystem/ruac_nullproc.hpp"

namespace ruac::rstd::logsystem {

    namespace nullproc {

        /**
         * @brief Returns an empty string, used as a null-output placeholder.
         *
         * @return An empty logtype::string instance.
         */
        auto nostr() -> logtype::string {
            return "";
        }

        /**
         * @brief No-op function, used as a null-callback placeholder.
         */
        void donot() {
            return;
        }

        /**
         * @brief Returns a newline string, used as a line-separator placeholder.
         *
         * @return A logtype::string containing "\\n".
         */
        auto next_line() -> logtype::string {
            return "\n";
        }

    } // namespace nullproc

} // namespace ruac::rstd::logsystem
