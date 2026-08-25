/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/gen/ruac_stdmsg.hpp
 * src/rstd/gen/ruac_stdmsg.cpp
 */

#include "rstd/gen/ruac_stdmsg.hpp"

namespace ruac::rstd::gen {

    /**
     * @brief Enable or disable printing messages
     *
     * @param enable_ Whether to enable or disable printing messages
     *
     * @details void
     */
    void StdMsg::enable_stdmsg(const bool enable_) {
        m_enable_msg = enable_;
    }

} // namespace ruac::rstd::gen
