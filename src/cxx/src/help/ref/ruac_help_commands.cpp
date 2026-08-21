/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/ref/ruac_help_commands.hpp
 * src/help/ref/ruac_help_commands.cpp
 */

#include "help/ref/ruac_help_commands.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::help::ref::commands {

    /**
     * @brief Print the supported RUAC command reference
     *
     * @details Builds a formatted command guide listing the supported
     *          commands, then writes it to stdout via a thread-safe osyncstream.
     *
     */
    void show_help_commands() {
        std::stringstream ss;
        ss << "\n";
        ss << "[COMMANDS]\n";
        ss << "  |\n";
        ss << "  |- add new user               : Entry user environment and add a new user.\n";
        ss << "  |- stdmsg off                 : Turn off standard message output.\n";
        ss << "  |- stdmsg on                  : Turn on standard message output.\n";
        ss << "  |- ruacdb user.info show all  : Show all user information.\n";
        ss << "  |- ruacdb help                : Show help message.\n";
        ss << "  |\n";
        ss << "(ENDOF)\n";
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }
} // namespace ruac::help::ref::commands
