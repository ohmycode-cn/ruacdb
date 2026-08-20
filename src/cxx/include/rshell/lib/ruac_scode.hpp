/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/lib/ruac_scode.hpp
 * src/rshell/lib/ruac_scode.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_SCODE_HPP
#define RUAC_SCODE_HPP

namespace ruac::rshell::lib::scode {

    enum class StatusCode {
        ABNORMAL_EXIT = 0,
        NORMAL_EXIT,
        CONTINUE
    };

} // namespace ruac::rshell::lib::scode

#endif // RUAC_SCODE_HPP
