/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_exec.hpp
 * src/ruac_shell_exec.cpp
 */

#include "rstd/messages/ruac_stdmsg.hpp"
#include "ruac_shell_parser.hpp"
#include "ruac_shell_pipe.hpp"
#include "ruac_shell_exec.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac {

    /**
     * @brief Check if the input line matches a quit/exit command
     *
     * @param line_ - Single, trimmed command line to check
     *
     * @return bool - True if the line matches "quit", "exit", "quit;", or "exit;"
     *
     * @details Exact, case-sensitive comparison against four literals. The
     *          semicolon variants allow users to terminate a statement with
     *          ';' and still quit. A pure, side-effect-free predicate safe
     *          to call outside any lock.
     *
     */
    auto ShellExec::end_whiled(const std::string &line_) -> bool {
        return "quit" == line_ || "exit" == line_ || "quit;" == line_ || "exit;" == line_;
    }

    /**
     * @brief Dump the live command-history records to stdout
     *
     * @details Obtains ShellPipe's m_cmd_history_records_ptr (the live history).
     *          Three exit paths: silent return if nullptr, prints "No history
     *          records." if empty, otherwise builds a stringstream with a
     *          colored header (M_B_GREEN background + M_F_YELLOW foreground)
     *          and flushes via std::osyncstream for thread-safe output. Note:
     *          the header text reads "From Backup history records:" despite
     *          printing live records. The green background distinguishes this
     *          output from cat_cmd_history_bak()'s red background.
     *
     */
    void ShellExec::cat_command_history() {
        auto pipe = ShellPipe::instance().get_context();
        auto cmdh = pipe.m_ptr_history_commands_count;
        if (nullptr == cmdh) {
            return;
        }
        if (cmdh->empty()) {
            std::osyncstream(std::cout) << "No history records." << std::endl;
            return;
        }
        std::stringstream ss;
        ss << M_B_GREEN << M_F_YELLOW << "From history records:" << M_RESET << "\n";
        for (const auto &cmd : *cmdh) {
            ss << cmd << "\n";
        }
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

    /**
     * @brief Clear the command-history records in the parser
     *
     * @details Calls ShellParser::clr_lines() to clear the parser's list of
     *          parsed command lines.
     *
     */
    void ShellExec::clr_command_history() {
        auto history = ShellPipe::instance().get_context().m_ptr_history_commands_count;
        if (history->empty()) {
            return;
        }
        history->clear();
        std::stringstream ss;
        ss << M_B_RED << M_F_YELLOW << "Clear history records done." << M_RESET << "\n";
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

    /**
     * @brief Dispatch a single parsed command line to the appropriate handler
     *
     * @param line_ - Single, trimmed command line (one entry from ParserCmdLine)
     *
     * @return int - 0 = terminate shell loop (quit/exit), 2 = continue
     *
     * @details First checks end_whiled() and returns 0 on a quit/exit match.
     *          On the exact literal "cat history", calls cat_cmd_history()
     *          then cat_cmd_history_bak() so the user sees green (live) then
     *          red (backup) in one shot, then falls through to return 2.
     *          Return code 1 is reserved/unused in the current implementation;
     *          exec() handles it defensively. Performs no locking of its own,
     *          relying on exec() having taken M_SHELL_EXEC_MTX.
     *
     */
    auto ShellExec::inner_exec(const std::string &line_) -> int {
        if (end_whiled(line_)) {
            return 0;
        } else if ("cat history" == line_) {
            cat_command_history();
        } else if ("clr history" == line_) {
            clr_command_history();
        } else if ("stdmsg on" == line_) {
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(true);
            std::osyncstream(std::cout) << "Enable stdmsg done." << std::endl;
        } else if ("stdmsg off" == line_) {
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(false);
            std::osyncstream(std::cout) << "Disable stdmsg done." << std::endl;
        } else {
            M_SYN_LITE.syntax_line_hook(line_);
        }
        return 2;
    }

    /**
     * @brief Thread-safe entry point to parse, record, and dispatch commands
     *
     * @param lines_ - Raw user input, may contain multiple semicolon-separated
     *                 commands
     *
     * @return int - 0 = terminate (quit/exit), 1 = reserved (currently
     *               unreachable), 2 = continue
     *
     * @details Acquires M_SHELL_EXEC_MTX for the entire parse-append-dispatch
     *          sequence so inner_exec/cat_cmd_history* can read shared history
     *          safely. Selects the history vector via fallback: defaults to
     *          m_cmd_history_records_bak, but overrides to the live
     *          m_cmd_history_records_ptr from ShellPipe when non-null. Copies
     *          lines_ into a temp (get_cmd_lines mutates its argument), parses
     *          via ParserCmdLine, then clears the parser list. Returns 2 early
     *          if no commands were parsed. Otherwise pushes each command to the
     *          history vector before dispatching via inner_exec(); if inner_exec
     *          returns 0 or 1, returns that code immediately (remaining
     *          commands are not dispatched).
     *
     */
    auto ShellExec::exec(const std::string &lines_) -> int {
        std::lock_guard<std::mutex> lock(M_SHELL_EXEC_MTX);
        std::string lines = lines_;

        ShellParser shell_parser;
        shell_parser.get_lines(lines);
        auto cmd_lines = shell_parser.ret_lines();
        shell_parser.clr_lines();

        for (unsigned long index{0}; index < cmd_lines.size(); index++) {
            int code = inner_exec(cmd_lines.at(index));
            if (0 == code || 1 == code) {
                return code;
            }
        }

        return 2;
    }

} // namespace ruac
