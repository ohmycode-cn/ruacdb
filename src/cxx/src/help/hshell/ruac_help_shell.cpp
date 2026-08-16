/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/hshell/ruac_help_shell.hpp
 * src/help/hshell/ruac_help_shell.cpp
 */

#include "help/hlib/ruac_help_syntax.hpp"
#include "help/hshell/ruac_help_shell.hpp"
#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::help::hshell {

    /**
     * @brief Construct the HelpShell with the default prompt string
     *
     * @details Initialises m_prompt to "ruac-db-(help)-> " which is
     *          displayed before each input line in the interactive loop.
     *
     */
    HelpShell::HelpShell() : m_prompt("ruac-db-(help)-> ") {}

    /**
     * @brief Dispatch a single help query line
     *
     * @param line_ - The raw input line entered by the user
     *
     * @return bool - true if the line matched a known help command,
     *         false if the line is unrecognised
     *
     * @details Recognised commands:
     *          - "syntax help": calls show_help_syntax() to print the
     *            syntax reference.
     *          - "exit" / "quit": prints a hint directing the user to
     *            use "exit help" or "quit help" to leave the shell.
     *          Any other input returns false so the caller can report
     *          an error.
     *
     */
    auto HelpShell::query(const std::string &line_) -> bool {
        if ("syntax help" == line_) {
            {
                ruac::help::hlib::syntax::show_help_syntax();
            }
            return true;
        } else if ("exit" == line_ || "quit" == line_) {
            {
                std::stringstream ss;
                ss << "Error: Not supported help shell syntax: exit, ";
                ss << "You maybe mean exit help shell. So ! You should use 'exit help' or 'quit help'";
                std::osyncstream(std::cout) << ss.str() << std::endl;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Run the interactive help shell read-eval loop
     *
     * @details Acquires M_HELP_SHELL_MTX, then repeatedly prints the
     *          prompt, reads a line from stdin, skips empty lines and
     *          comments (# or //), breaks on "exit help"/"quit help",
     *          and otherwise dispatches the line to query(). Unmatched
     *          lines produce an error message.
     *
     */
    void HelpShell::runhsh() {
        std::lock_guard<std::mutex> lock(M_HELP_SHELL_MTX);
        while (true) {
            std::osyncstream(std::cout) << m_prompt;
            std::string line;
            std::getline(std::cin, line);
            if (line.empty() || "#" == line.substr(0, 1) || "//" == line.substr(0, 2)) {
                continue;
            }
            if ("exit help" == line || "quit help" == line) {
                break;
            }
            if (!query(line)) {
                std::osyncstream(std::cout) << "Error: Invalid help query sentence: " << line << std::endl;
            }
        };
    }

} // namespace ruac::help::hshell
