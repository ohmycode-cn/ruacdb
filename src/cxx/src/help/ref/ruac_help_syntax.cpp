/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/ref/ruac_help_syntax.hpp
 * src/help/ref/ruac_help_syntax.cpp
 */

#include "help/ref/ruac_help_syntax.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::help::ref::syntax {

    /**
     * @brief Print the supported RUAC command syntax reference
     *
     * @details Builds a formatted syntax guide listing the supported
     *          CREATE DATABASE and SHOW DATABASES command forms, then
     *          writes it to stdout via a thread-safe osyncstream.
     *
     */
    void show_help_syntax() {
        std::stringstream ss;
        ss << "\n";
        ss << "[CREATE]:\n";
        ss << "  |\n";
        ss << "  |- CREATE DATABASE <target>\n";
        ss << "  |- CREATE DATABASE IF NOT EXISTS <target>\n";
        ss << "[SHOW]:\n";
        ss << "  |\n";
        ss << "  |- SHOW DATABASES\n";
        ss << "  |- SHOW DATABASE ALL\n";
        ss << "(ENDOF)\n";
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

} // namespace ruac::help::ref::syntax
