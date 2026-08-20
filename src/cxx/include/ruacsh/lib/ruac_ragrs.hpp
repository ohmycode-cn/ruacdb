/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/lib/ruac_ragrs.hpp
 * src/ruacsh/lib/ruac_ragrs.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RAGRS_HPP
#define RUAC_RAGRS_HPP

namespace ruac::ruacsh::lib {

    namespace ragrs {

        struct RshellArgs {
            bool m_enable_ce{true};  // MODE: Enable console compatible : true is "\033",           false is "\x1b"
            bool m_enable_ht{false}; // MODE: Enable highlight          : true is highlight string, false if text string
            bool m_enable_bf{false}; // MODE: Enable bold font          : true is bold,             false is normal
            bool m_enable_dp{false}; // MODE: Enable background         : true is dark,             false is tint
        };

    } // namespace ragrs

} // namespace ruac::ruacsh::lib

#endif // RUAC_RAGRS_HPP
