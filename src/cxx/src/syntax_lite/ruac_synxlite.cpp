/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/ruac_synxlite.hpp
 * src/syntax_lite/ruac_synxlite.cpp
 */

#include "syntax_lite/ruac_synxlite.hpp"
#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::api {

    SynxLite::SynxLite(int uid_) {
        M_PARSER = std::make_unique<ruac::syntax_lite::tree::Parser>(uid_);
    }

    void SynxLite::process(const std::string &line_) {
        std::lock_guard<std::mutex> lock(M_SYN_LITE_MTX);
        if (nullptr == M_PARSER) {
            std::osyncstream(std::cout) << "Fatal: Not initialized parser." << std::endl;
            return;
        }
        M_PARSER->process(line_);
    }

} // namespace ruac::syntax_lite::api
