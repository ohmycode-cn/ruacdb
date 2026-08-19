/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/rshell/filter/ruac_rshfer.hpp
 * src/rstd/rshell/filter/ruac_rshfer.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RSHFER_HPP
#define RUAC_RSHFER_HPP

#include "rstd/rshell/filter/lib/ruac_funnel.hpp"
#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace ruac::rstd::rshell::filter::api {

    class Interface {
      private:
        std::mutex M_INTERFACE_MTX;
        std::unique_ptr<ruac::rstd::rshell::filter::lib::Funnel> m_funnel;

      public:
        Interface();
        ~Interface() = default;

      public:
        auto rshfer(std::string &lines_, std::vector<std::string> &line_list_) -> bool;
    };

} // namespace ruac::rstd::rshell::filter::api

#endif // RUAC_RSHFER_HPP
