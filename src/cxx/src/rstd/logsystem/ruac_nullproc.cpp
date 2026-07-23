/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_nullproc.hpp
 * src/rstd/logsystem/ruac_nullproc.cpp
 */

#include "rstd/logsystem/ruac_nullproc.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"

namespace ruac::rstd::logsystem {

    namespace nullproc {

        /**
         * @brief Returns an empty string, used as a null-output placeholder.
         *
         * @return An empty logtype::String instance.
         */
        auto nostr() -> logtype::String {
            return "";
        }

        /**
         * @brief No-op function, used as a null-callback placeholder.
         */
        void donot() {
            return;
        }

        auto nextline() -> logtype::String {
            return "\n";
        }

    } // namespace nullproc

} // namespace ruac::rstd::logsystem
