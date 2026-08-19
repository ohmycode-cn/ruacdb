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
#include <algorithm>
#include <array>
#include <cstdint>
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
     * @brief Compile-time FNV-1a hash and exit-command tables
     *
     * @details fnv1a_hash computes a 64-bit FNV-1a hash for short strings.
     *          exit_cmd_hashes holds the pre-computed hashes of the two
     *          valid exit commands ("help --exit", "help --quit") so that
     *          is_exit_command_safe can reject non-exit inputs in O(1)
     *          before falling through to an exact string comparison.
     *
     */
    namespace {

        constexpr auto fnv1a_hash(std::string_view sv_) noexcept -> std::uint64_t {
            auto hash = std::uint64_t{0xcbf29ce484222325};
            for (auto c : sv_) {
                hash ^= static_cast<std::uint64_t>(c);
                hash *= std::uint64_t{0x100000001b3};
            }
            return hash;
        }

        constexpr std::array<std::uint64_t, 2> exit_cmd_hashes = {
            fnv1a_hash("help --exit"),
            fnv1a_hash("help --quit"),
        };

        constexpr std::array<std::string_view, 2> exit_commands = {"help --exit", "help --quit"};

    } // anonymous namespace

    /**
     * @brief Check whether the input is a valid exit command
     *
     * @param input_ - the trimmed, lowercased user input
     *
     * @return bool - true if input_ is exactly "help --exit" or "help --quit"
     *
     * @details Two-stage check: first compare the FNV-1a hash of input_
     *          against the pre-computed exit_cmd_hashes for a fast reject,
     *          then verify with an exact string comparison to guard
     *          against hash collisions.
     *
     */
    auto HelpShell::is_exit_command_safe(std::string_view input_) noexcept -> bool {
        const auto h = fnv1a_hash(input_);
        if (std::find(exit_cmd_hashes.begin(), exit_cmd_hashes.end(), h) == exit_cmd_hashes.end()) {
            return false;
        }
        return std::find(exit_commands.begin(), exit_commands.end(), input_) != exit_commands.end();
    }

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
     *          - "help --command": prints a not-implemented error.
     *          - invailed_exit_commands ("exit", "quit", "exit help",
     *            "quit help", "help exit", "help quit", "exit --help",
     *            "quit --help"): prints a hint directing the user to
     *            use "help --exit" or "help --quit".
     *          Any other input prints an invalid-query error.
     *
     */
    auto HelpShell::query(const std::string &line_) -> int {

        constexpr std::array<std::string_view, 8> invailed_exit_commands = {
            {"exit", "quit", "exit help", "quit help", "help exit", "help quit", "exit --help", "quit --help"}};

        if ("help --quit" == line_ || "help --exit" == line_) {
            return 0;
        } else if ("help --syntax" == line_) {
            {
                ruac::help::hlib::syntax::show_help_syntax();
            }
        } else if ("help --command" == line_) {
            std::osyncstream(std::cout) << "Error: Current not implemented." << std::endl;
        } else if (std::find(invailed_exit_commands.begin(), invailed_exit_commands.end(), line_) != invailed_exit_commands.end()) {
            {
                std::stringstream ss;
                ss << "Error: Not supported help shell syntax: '" << line_ << "' ";
                ss << "You maybe mean exit help shell. So ! You should use 'help --exit' or 'help --quit'";
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
