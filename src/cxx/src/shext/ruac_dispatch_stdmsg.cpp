/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/shext/ruac_dispatch_stdmsg.hpp
 * src/shext/ruac_dispatch_stdmsg.cpp
 */

#include "rlib/ruac_tdebug.hpp"
#include "shext/ruac_dispatch_stdmsg.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <syncstream>

namespace ruac::shext {

    auto dispatch_stdmsg(const std::string &line_) -> bool {
        std::istringstream iss(line_);
        std::string token;
        std::vector<std::string> tokens;
        while (iss >> token) {
            tokens.push_back(std::move(token));
        }

        if (tokens.empty() || tokens[0] != "stdmsg") {
            return false;
        }

        if (tokens.size() < 2 || (tokens[1] != "on" && tokens[1] != "off")) {
            std::osyncstream(std::cout) << "Error: Usage: stdmsg on|off [--flags]" << std::endl;
            return true;
        }

        if (tokens[1] == "off") {
            rlib::tdebug::Info::get().enable_stdmsg(false);
            std::osyncstream(std::cout) << "Done: Disabled standard temporarily debug message." << std::endl;
            return true;
        }

        rstd::gen::StdDebugParamList params{};
        for (size_t i = 2; i < tokens.size(); ++i) {
            if ("--no-prompt-header" == tokens[i]) {
                params.m_enable_header = false;
            } else if ("--color-prompt" == tokens[i]) {
                params.m_enable_color = true;
                params.m_enable_header = true;
            } else {
                std::osyncstream(std::cout) << "Error: Unknown flag '" << tokens[i] << "'" << std::endl;
                return true;
            }
        }

        rlib::tdebug::Info::get().set_param_mode(params);
        rlib::tdebug::Info::get().enable_stdmsg(true);
        std::osyncstream(std::cout) << "Done: Enabled standard temporarily debug message." << std::endl;
        return true;
    }

} // namespace ruac::shext
