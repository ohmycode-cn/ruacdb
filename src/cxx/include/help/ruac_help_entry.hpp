/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/ruac_help_entry.hpp
 * src/help/ruac_help_entry.cpp
 *
 * @brief Defines the HelpEntry class for dispatching help subcommands in a thread-safe manner.
 */

#pragma once
#ifndef RUAC_HELP_ENTRY_HPP
#define RUAC_HELP_ENTRY_HPP

#include <mutex>

namespace ruac::help::api {

    class HelpEntry {
      private:
        std::mutex M_HELP_ENTRY_MTX;

      private:
        void show_banner();

      public:
        HelpEntry() = default;
        ~HelpEntry() = default;

      public:
        void run();
    };

} // namespace ruac::help::api

#endif // RUAC_HELP_ENTRY_HPP
