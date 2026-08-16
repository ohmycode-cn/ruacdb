/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/ruac_help_guide.hpp
 * src/help/ruac_help_guide.cpp
 */

#include "help/hshell/ruac_help_shell.hpp"
#include "help/ruac_help_guide.hpp"
#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::help {

    /**
     * @brief Print the welcome banner and available help commands
     *
     * @details Acquires M_HELP_GUIDE_MTX to serialise output, then writes
     *          the RUACDB help shell banner (version, author) and a list of
     *          available commands (syntax help, exit help) to stdout via a
     *          thread-safe osyncstream.
     *
     */
    void HelpGuide::hello() {
        std::lock_guard<std::mutex> lock(M_HELP_GUIDE_MTX);
        {
            std::stringstream ss;
            ss << "+-------------------------------------+\n";
            ss << "|WELCOME TO USE RAUCDB HELP LITE SHELL|\n";
            ss << "|VERSION: 0.0.1                       |\n";
            ss << "|AUTHOR: ohmycode-cn(ohcode@163.com)  |\n";
            ss << "+-------------------------------------+\n";
            ss << "Get syntax help:                      syntax help\n";
            ss << "Exit help:                            exit help\n";
            ss << "  |___________________________________quit help\n";
            std::osyncstream(std::cout) << ss.str() << std::endl;
        }
    }

    /**
     * @brief Launch the interactive help shell
     *
     * @details Acquires M_HELP_GUIDE_MTX, constructs a HelpShell instance
     *          and enters its runhsh() read-eval loop. The mutex is held
     *          for the entire interactive session so that only one help
     *          shell can run at a time.
     *
     */
    void HelpGuide::runsh() {
        std::lock_guard<std::mutex> lock(M_HELP_GUIDE_MTX);
        {
            ruac::help::hshell::HelpShell hsh;
            hsh.runhsh();
        }
    }

    /**
     * @brief Entry point that prints the banner then starts the help shell
     *
     * @details Calls hello() to display the welcome banner, then runsh()
     *          to enter the interactive help shell loop.
     *
     */
    void HelpGuide::helpshell() {
        {
            hello();
        }
        runsh();
    }
} // namespace ruac::help
