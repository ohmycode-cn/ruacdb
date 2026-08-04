/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synlite.hpp
 * src/syntax_lite/ruac_synlite.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_SYNLITE_HPP
#define RUAC_SYNLITE_HPP

#include "syntax_lite/ruac_synlite_status_code.hpp"
#include <string>
#include <mutex>

namespace ruac::syntax_lite {

    class SynLite {
      private:
        std::mutex M_SYN_LITE_MTX;

      public:
        SynLite() = default;
        ~SynLite() = default;

      public:
        void syntax_line_hook(const std::string &line_);
        auto syntax_line_hret() -> status_code::HookCode;
    };

} // namespace ruac::syntax_lite

#endif // RUAC_SYNLITE_HPP
