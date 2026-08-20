/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/ruac_help_entry.hpp
 * src/help/ruac_help_entry.cpp
 */

#include "help/ruac_help_entry.hpp"
#include "help/shell/ruac_help_shell.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::help::api {

    /**
     * @brief Print the welcome banner and available help commands
     *
     * @details Acquires M_HELP_ENTRY_MTX to serialise output, then writes
     *          the RUACDB help shell banner (version, author) and a list of
     *          available commands (syntax help, exit help) to stdout via a
     *          thread-safe osyncstream.
     *
     */
    void HelpEntry::show_banner() {
        std::lock_guard<std::mutex> lock(M_HELP_ENTRY_MTX);
        {
            std::stringstream ss;
            ss << "+-------------------------------------+\n";
            ss << "|WELCOME TO USE RAUCDB HELP LITE SHELL|\n";
            ss << "|VERSION: 0.0.1                       |\n";
            ss << "|AUTHOR: ohmycode-cn(ohcode@163.com)  |\n";
            ss << "+-------------------------------------+\n";
            ss << "Get command help:                     help --command\n";
            ss << "Get syntax help:                      help --syntax\n";
            ss << "Exit help:                            help --exit\n";
            ss << "  |___________________________________help --quit\n";
            std::osyncstream(std::cout) << ss.str() << std::endl;
        }
    }

    /**
     * @brief Entry point that prints the banner then starts the help shell
     *
     * @details Calls show_banner() to display the welcome banner, then
     *          constructs a HelpShell instance and enters its run()
     *          read-eval loop. The mutex is held for the entire interactive
     *          session so that only one help shell can run at a time.
     *
     */
    void HelpEntry::run() {
        std::lock_guard<std::mutex> lock(M_HELP_ENTRY_MTX);
        {
            show_banner();
            ruac::help::shell::HelpShell hsh;
            hsh.run();
        }
    }

} // namespace ruac::help::api
