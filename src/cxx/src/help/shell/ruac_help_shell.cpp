/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/shell/ruac_help_shell.hpp
 * src/help/shell/ruac_help_shell.cpp
 */

#include "help/ref/ruac_help_commands.hpp"
#include "help/ref/ruac_help_syntax.hpp"
#include "help/shell/ruac_help_shell.hpp"
#include "rstd/cmdlex/ruac_cmdlex.hpp"
#include "rstd/convert/ruac_lowercase.hpp"
#include "rstd/convert/ruac_rmspace.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <syncstream>
#include <vector>

namespace ruac::help::shell {

    namespace {

        /**
         * @brief Compile-time FNV-1a hash and exit-command tables
         *
         * @details fnv1a_hash computes a 64-bit FNV-1a hash for short strings.
         *          exit_cmd_hashes holds the pre-computed hashes of the two
         *          valid exit commands ("help --exit", "help --quit") so that
         *          is_exit_command can reject non-exit inputs in O(1)
         *          before falling through to an exact string comparison.
         *
         */
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
     * @brief Construct the HelpShell with a cmdlex and default prompt
     *
     * @details Allocates a CmdLex via std::make_unique and stores it
     *          in m_cmdlex for semicolon-based command splitting in run().
     *          Also initialises m_prompt to "ruac-db-(help)-> " which is
     *          displayed before each input line in the interactive loop.
     *
     */
    HelpShell::HelpShell() {
        m_cmdlex = std::make_unique<ruac::rstd::cmdlex::api::CmdLex>();
        m_prompt = "ruac-db-(help)-> ";
    }

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
    auto HelpShell::is_exit_command(std::string_view input_) noexcept -> bool {
        const auto h = fnv1a_hash(input_);
        if (std::find(exit_cmd_hashes.begin(), exit_cmd_hashes.end(), h) == exit_cmd_hashes.end()) {
            return false;
        }
        return std::find(exit_commands.begin(), exit_commands.end(), input_) != exit_commands.end();
    }

    /**
     * @brief Dispatch a single help query line
     *
     * @param line_ - A pre-processed input line (spaces removed,
     *               lowercased) produced by run()'s filter pipeline
     *
     * @return int - 0 if the command is an exit command,
     *         1 otherwise
     *
     * @details Recognised commands:
     *          - "help --exit" / "help --quit": returns 0 to signal exit.
     *          - "help --syntax": calls show_help_syntax() to print the
     *            syntax reference.
     *          - "help --command": prints a not-implemented error.
     *          - invalid_exit_commands ("exit", "quit", "exit help",
     *            "quit help", "help exit", "help quit", "exit --help",
     *            "quit --help"): guesses the user likely intended to exit
     *            and prints a hint directing them to the correct syntax
     *            "help --exit" or "help --quit".
     *          Any other input prints an invalid-query error.
     *
     */
    auto HelpShell::dispatch(const std::string &line_) -> int {

        constexpr std::array<std::string_view, 8> invalid_exit_commands = {
            {"exit", "quit", "exit help", "quit help", "help exit", "help quit", "exit --help", "quit --help"}};

        if ("help --quit" == line_ || "help --exit" == line_) {
            return 0;
        } else if ("help --syntax" == line_) {
            {
                ruac::help::ref::syntax::show_help_syntax();
            }
        } else if ("help --command" == line_) {
            {
                ruac::help::ref::commands::show_help_commands();
            }
        } else if (std::find(invalid_exit_commands.begin(), invalid_exit_commands.end(), line_) != invalid_exit_commands.end()) {
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
     *          prompt, reads a line from stdin, and preprocesses it by
     *          removing all spaces (rmspace) and lowercasing. Skips
     *          empty lines and comments (# or //). Checks m_cmdlex
     *          for null and aborts with a fatal error if missing. Splits
     *          the input into semicolon-separated commands via
     *          m_cmdlex->lex(); aborts if lexing produces no lines.
     *          For each split line, applies rmspace again then
     *          dispatches to dispatch(); if dispatch() returns 0
     *          (exit command), the function returns immediately.
     *
     */
    void HelpShell::run() {
        std::lock_guard<std::mutex> lock(M_HELP_SHELL_MTX);

        while (true) {

            std::osyncstream(std::cout) << m_prompt;
            std::string lines;
            if (!std::getline(std::cin, lines)) {
                break;
            }

            {
                ruac::rstd::convert::rmspace::remove_string_spaces(lines);
                ruac::rstd::convert::lowercase::to_lower_string(lines);
            }

            if (lines.empty() || "#" == lines.substr(0, 1) || "//" == lines.substr(0, 2)) {
                continue;
            }

            std::vector<std::string> line_list;

            if (nullptr == m_cmdlex) {
                {
                    std::stringstream ss;
                    ss << "Fatal: Program error ! Shell filter program lose, please contact the developer !";
                    std::osyncstream(std::cout) << ss.str() << std::endl;
                }
                return;
            }

            if (!m_cmdlex.get()->lex(lines, line_list)) {
                return;
            }

            for (auto &line : line_list) {
                {
                    ruac::rstd::convert::rmspace::remove_string_spaces(line);
                }
                if (0 == dispatch(line)) {
                    return;
                }
            }
        };
    }

} // namespace ruac::help::shell
