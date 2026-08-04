/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synlite_status_code.hpp
 * src/syntax_lite/ruac_synlite_status_code.cpp
 *
 * @brief Defines the HookCode enumeration for syntax analysis status codes.
 */

#pragma once
#ifndef RUAC_SYNLITE_STATUS_CODE_HPP
#define RUAC_SYNLITE_STATUS_CODE_HPP

namespace ruac::syntax_lite {

    namespace status_code {

        enum class HookCode {
            OK = 0,
            NO,
            FL,
        };

    } // namespace status_code

} // namespace ruac::syntax_lite

#endif // RUAC_SYNLITE_STATUS_CODE_HPP
