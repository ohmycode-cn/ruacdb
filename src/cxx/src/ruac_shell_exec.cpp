/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_exec.hpp
 * src/ruac_shell_exec.cpp
 */

#include "ruac_parser_cmd_line.hpp"
#include "ruac_shell_pipe.hpp"
#include "ruac_shell_exec.hpp"
#include <iostream>
#include <syncstream>
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
    void ShellExec::cat_cmd_history() {
        auto pipe = ShellPipe::instance().get_shell_pipe_list();
        auto cmdh = pipe.m_cmd_history_records_ptr;
        if (nullptr == cmdh) {
            return;
        }
        if (cmdh->empty()) {
            std::osyncstream(std::cout) << "No history records." << std::endl;
            return;
        }
        std::stringstream ss;
        ss << M_B_GREEN << M_F_YELLOW << "From Backup history records:" << M_RESET << "\n";
        for (const auto &cmd : *cmdh) {
            ss << cmd << "\n";
        }
        std::osyncstream(std::cout) << ss.str() << std::endl;
    }

    /**
     * @brief Dump the backup command-history records to stdout
     *
     * @details Iterates the member m_cmd_history_records_bak directly. Uses a
     *          colored header with M_B_RED background + M_F_YELLOW foreground
     *          (red distinguishes backup output from cat_cmd_history()'s green)
     *          and flushes via std::osyncstream. Note: the empty-check guard
     *          is commented out, so the colored header is printed even when
     *          the backup vector is empty.
     *
     */
    void ShellExec::cat_cmd_history_bak() {
        // if (m_cmd_history_records_bak.empty()) {
        //     return;
        // }
        std::stringstream ss;
        ss << M_B_RED << M_F_YELLOW << "From Backup history records:" << M_RESET << "\n";
        for (const auto &cmd : m_cmd_history_records_bak) {
            ss << cmd << "\n";
        }
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
        }
        if ("cat history" == line_) {
            cat_cmd_history();
            cat_cmd_history_bak();
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
        auto pipe = ShellPipe::instance().get_shell_pipe_list();
        auto cmdh = pipe.m_cmd_history_records_ptr;
        auto vect = &m_cmd_history_records_bak;
        if (nullptr != cmdh) {
            vect = &(*cmdh);
        }
        ParserCmdLine pcl;
        std::string tmp = lines_;
        pcl.get_cmd_lines(tmp);
        auto cmd_lines = pcl.ret_cmd_line();
        pcl.clr_cmd_list();
        if (cmd_lines.empty()) {
            return 2;
        }
        for (int i{0}; i < cmd_lines.size(); i++) {
            vect->push_back(cmd_lines.at(i));
            int code = inner_exec(cmd_lines.at(i));
            if (0 == code || 1 == code) {
                return code;
            }
        }
        return 2;
    }

} // namespace ruac
