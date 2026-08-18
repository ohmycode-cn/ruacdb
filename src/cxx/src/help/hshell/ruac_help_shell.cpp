/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/hshell/ruac_help_shell.hpp
 * src/help/hshell/ruac_help_shell.cpp
 */

#include "help/hlib/ruac_help_syntax.hpp"
#include "help/hshell/ruac_help_shell.hpp"
#include "rstd/convert/ruac_lowercase.hpp"
#include "rstd/convert/ruac_rmspace.hpp"
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
     * @return int - 0 if the command is an exit command,
     *         1 otherwise
     *
     * @details Recognised commands:
     *          - "help --exit" / "help --quit": returns 0 to signal exit.
     *          - "help --syntax": calls show_help_syntax() to print the
     *            syntax reference.
     *          - "exit" / "quit": prints a hint directing the user to
     *            use "exit help" or "quit help" to leave the shell.
     *          Any other input prints an error message.
     *
     */
    auto HelpShell::query(const std::string &line_) -> int {
        if ("help --quit" == line_ || "help --exit" == line_) {
            return 0;
        } else if ("help --syntax" == line_) {
            {
                ruac::help::hlib::syntax::show_help_syntax();
            }
        } else if ("help --command" == line_) {
            std::osyncstream(std::cout) << "Error: Current not implemented." << std::endl;
        } else if ("exit" == line_ || "quit" == line_) {
            {
                std::stringstream ss;
                ss << "Error: Not supported help shell syntax: exit or quit, ";
                ss << "You maybe mean exit help shell. So ! You should use 'exit help' or 'quit help'";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
        } else {
            {
                std::osyncstream(std::cout) << "Error: Invalid help query sentence: " << line_ << std::endl;
            }
        }
        return 1;
    }

    /**
     * @brief Run the interactive help shell read-eval loop
     *
     * @details Acquires M_HELP_SHELL_MTX, then repeatedly prints the
     *          prompt, reads a line from stdin, skips empty lines and
     *          comments (# or //), splits input by semicolons to support
     *          multiple commands per line, dispatches each command to
     *          query(), and clears the command buffer after each dispatch.
     *          Breaks on "help --exit"/"help --quit". Unmatched lines
     *          produce an error message.
     *
     */
    void HelpShell::runhsh() {
        std::lock_guard<std::mutex> lock(M_HELP_SHELL_MTX);

        while (true) {

            std::osyncstream(std::cout) << m_prompt;
            std::string lines;
            std::getline(std::cin, lines);
            ruac::rstd::convert::lowercase::to_lower_string(lines);
            if (lines.empty() || "#" == lines.substr(0, 1) || "//" == lines.substr(0, 2)) {
                continue;
            }

            std::string line;
            for (auto &c : lines) {
                if (';' == c) {
                    ruac::rstd::convert::rmspace::remove_string_spaces(line);
                    if (0 == query(line)) {
                        return;
                    }
                    line.clear();
                } else {
                    line += c;
                }
            }

            if (!line.empty()) {
                ruac::rstd::convert::rmspace::remove_string_spaces(line);
                if (0 == query(line)) {
                    return;
                }
                line.clear();
            }
        };
    }

} // namespace ruac::help::hshell
