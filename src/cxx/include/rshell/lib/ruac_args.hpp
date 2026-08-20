/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/lib/ruac_args.hpp
 * src/rshell/lib/ruac_args.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_ARGS_HPP
#define RUAC_ARGS_HPP

namespace ruac::rshell::lib {

    namespace args {

        struct ShellArgs {
            bool m_enable_ce{true};  // MODE: Enable console compatible : true is "\033",           false is "\x1b"
            bool m_enable_ht{false}; // MODE: Enable highlight          : true is highlight string, false if text string
            bool m_enable_bf{false}; // MODE: Enable bold font          : true is bold,             false is normal
            bool m_enable_dp{false}; // MODE: Enable background         : true is dark,             false is tint
        };

    } // namespace args

} // namespace ruac::rshell::lib

#endif // RUAC_ARGS_HPP
