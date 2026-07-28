/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/ruac_donone.hpp
 * src/rstd/ruac_donone.cpp
 */

#include "rstd/ruac_donone.hpp"

namespace ruac::rstd {

    namespace donone {

        /**
         * @brief Get a null/empty string
         *
         * @return std::string - An empty string
         *
         * @details Returns an empty string. Used as a placeholder or default
         *          value where a string is expected but no content is needed.
         *
         */
        auto null_string() -> std::string {
            return "";
        }

        /**
         * @brief Perform no operation
         *
         * @details A no-op function that simply returns without doing anything.
         *          Used as a placeholder or default action where no operation
         *          is required (e.g., when color output is disabled).
         *
         */
        void notdo() {
            return;
        }

    } // namespace donone

} // namespace ruac::rstd
