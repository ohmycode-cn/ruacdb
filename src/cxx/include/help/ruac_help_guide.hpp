/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/ruac_help_guide.hpp
 * src/help/ruac_help_guide.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_HELP_GUIDE_HPP
#define RUAC_HELP_GUIDE_HPP

#include <mutex>

namespace ruac::help {

    class HelpGuide {
      private:
        std::mutex M_HELP_GUIDE_MTX;

      private:
        void hello();
        void runsh();

      public:
        HelpGuide() = default;
        ~HelpGuide() = default;

      public:
        void helpshell();
    };

} // namespace ruac::help

#endif // RUAC_HELP_GUIDE_HPP
