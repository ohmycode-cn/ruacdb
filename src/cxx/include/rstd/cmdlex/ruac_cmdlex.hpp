/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/cmdlex/ruac_cmdlex.hpp
 * src/rstd/cmdlex/ruac_cmdlex.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_CMDLEX_HPP
#define RUAC_CMDLEX_HPP

#include "rstd/cmdlex/lib/ruac_funnel.hpp"
#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace ruac::rstd::cmdlex::api {

    class CmdLex {
      private:
        std::mutex M_INTERFACE_MTX;
        std::unique_ptr<ruac::rstd::cmdlex::lib::Funnel> m_funnel;

      public:
        CmdLex();
        ~CmdLex() = default;

      public:
        auto lex(std::string &lines_, std::vector<std::string> &line_list_) -> bool;
    };

} // namespace ruac::rstd::cmdlex::api

#endif // RUAC_CMDLEX_HPP
