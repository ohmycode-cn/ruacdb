/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/messages/ruac_stdmsg.hpp
 * src/rstd/messages/ruac_stdmsg.cpp
 */

#include "rstd/messages/ruac_stdmsg.hpp"

namespace ruac::rstd::messages {

    /**
     * @brief Get the singleton instance of StdMsg
     *
     * @return StdMsg& - Reference to the singleton instance
     *
     * @details Implements the singleton pattern using a static local variable.
     *          Returns a reference to the single StdMsg instance, ensuring
     *          only one instance exists throughout the application.
     *
     */
    auto StdMsg::instance() -> StdMsg & {
        static StdMsg instance_object;
        return instance_object;
    }

} // namespace ruac::rstd::messages
