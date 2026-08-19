/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/rshell/filter/lib/ruac_funnel.hpp
 * src/rstd/rshell/filter/lib/ruac_funnel.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_FUNNEL_HPP
#define RUAC_FUNNEL_HPP

#include <string>
#include <vector>
#include <mutex>

namespace ruac::rstd::rshell::filter::lib {

    class Funnel {
      private:
        std::mutex M_FUNNEL_MTX;

      private:
        void filter(std::string &lines_, std::vector<std::string> &line_list_);

      public:
        Funnel() = default;
        ~Funnel() = default;

      public:
        void funnel(std::string &lines_, std::vector<std::string> &line_list_);
    };

} // namespace ruac::rstd::rshell::filter::lib

#endif // RUAC_FUNNEL_HPP
