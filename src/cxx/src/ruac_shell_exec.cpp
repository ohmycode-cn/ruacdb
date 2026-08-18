/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_exec.hpp
 * src/ruac_shell_exec.cpp
 */

#include "help/ruac_help_guide.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "ruac_shell_exec.hpp"
#include "ruac_shell_parser.hpp"
#include "ruac_shell_pipe.hpp"
#include "usersystem/ruac_usersmap.hpp"
#include "usersystem/ruac_usergroup.hpp"
#include "usersystem/ruac_userid.hpp"
#include "login/ruac_registered_user.hpp"
#include <iostream>
#include <mutex>
#include <sstream>
#include <syncstream>

namespace ruac {

    /**
     * @brief Construct a ShellExec bound to a given kernel state
     *
     * @param kernel_state_ - Reference to the shared Kernel object that
     *                        holds the current user identity
     *
     * @details Stores the kernel reference in m_kernel_state and
     *          initialises the inner SynLite instance (M_SYN_LITE) with
     *          the user id currently carried by kernel_state_. The
     *          SynLite instance is used later to execute SQL-like lines.
     *
     */
    ShellExec::ShellExec(kernel::state::Kernel &kernel_state_)
        : m_kernel_state(kernel_state_),
          M_SYN_LITE(kernel_state_.get_current_user_id()) {}

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
     * @details Obtains the ShellPipe shared context and reads the pointer
     *          to the history vector (m_ptr_history_commands_count). Four
     *          exit paths: silent return if the pointer is nullptr;
     *          prints "No history records." if the vector is empty;
     *          otherwise builds a stringstream with a colored header
     *          (M_B_GREEN background + M_F_YELLOW foreground) followed by
     *          each history line, then flushes via std::osyncstream for
     *          thread-safe output.
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
     * @brief Clear the command-history records
     *
     * @details Reads the history vector pointer from ShellPipe context;
     *          returns silently if already empty. Otherwise clears the
     *          vector and prints a colored confirmation message
     *          (M_B_RED background + M_F_YELLOW foreground) via
     *          std::osyncstream.
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
     * @brief Get the current user name from kernel state
     *
     * @return std::string - The user name stored in the shared Kernel
     *         object.
     *
     * @details A thin accessor that delegates to
     *          m_kernel_state.get_current_user_name(). Used by
     *          uid_permission_guard() and shell prompt rendering.
     *
     */
    auto ShellExec::get_current_user() -> std::string {
        return m_kernel_state.get_current_user_name();
    }

    /**
     * @brief Get the current user id from kernel state
     *
     * @return int - The uid stored in the shared Kernel object.
     *
     * @details A thin accessor that delegates to
     *          m_kernel_state.get_current_user_id(). Used to translate
     *          the uid back to a user name for permission checks via
     *          UserId.
     *
     */
    auto ShellExec::get_current_uid() -> int {
        return m_kernel_state.get_current_user_id();
    }

    /**
     * @brief Assign a weight to a group name based on its priority
     *
     * @param group_ - Name of the group to assign a weight to
     *
     * @return int - Weight value for the group, 0 for "root", -1 for "manager", -2 for "visitor", -3 for any other group
     *
     * @details This function is used to compare the priority of two groups. "root" has the highest priority, followed by "manager" and "visitor".
     *
     */
    auto ShellExec::group_weight(const std::string &group_) const -> int {
        if ("root" == group_) {
            return 0;
        } else if ("manager" == group_) {
            return -1;
        } else if ("visitor" == group_) {
            return -2;
        }
        return -3;
    }

    /**
     * @brief Verify that the current user belongs to a required group
     *
     * @param msg_ - Error message text printed when the check fails and
     *               out_msg_ is true
     * @param guard_group_ - Name of the group that the user must belong
     *                       to (e.g. "root", "manager")
     * @param out_msg_ - When true, the failure message is flushed to
     *                   stdout via std::osyncstream
     *
     * @return bool - true if the current user's group matches
     *                guard_group_; false otherwise
     *
     * @details Resolves the current uid to a user name via UserId, then
     *          looks up the user's group via UserGroup, and compares it
     *          against guard_group_. If the groups differ and out_msg_ is
     *          set, msg_ is printed. This is the central gate used by
     *          inner_exec() for every privileged shell command.
     *
     */
    auto ShellExec::uid_permission_guard(const std::string &msg_, const std::string &guard_group_,
                                         bool out_msg_) -> bool {
        auto u = get_current_uid();
        auto user_name = ruac::usersystem::UserId::instance().get_user_name(u);
        auto user_group = ruac::usersystem::UserGroup::instance().get_group(user_name);
        if (group_weight(guard_group_) > group_weight(user_group)) {
            if (out_msg_) {
                std::osyncstream(std::cout) << msg_ << std::endl;
            }
            return false;
        }
        return true;
    }

    /**
     * @brief Dispatch a single parsed command line to the appropriate handler
     *
     * @param line_ - Single, trimmed command line (one entry from ShellParser)
     *
     * @return int - 0 = terminate shell loop (quit/exit), 2 = continue
     *
     * @details First checks end_whiled() and returns 0 on a quit/exit match.
     *          Then tests a series of exact string literals in order:
     *          - "cat history":       calls cat_command_history()
     *          - "clr history":       root-only, calls clr_command_history()
     *          - "stdmsg on"/"off":   root-only, toggles StdMsg debug output
     *          - "ruacdb help":       creates a HelpGuide and enters its shell
     *          - "ruacdb user.info show all": root-only, prints UsersMap
     *          - "add new user.env":  root-only, launches RegisteredUser REPL
     *          All other strings are gated on the "manager" group and then
     *          forwarded to SynLite::syntax_line_hook() for SQL-style parsing.
     *          Return code 1 is reserved/unused in the current
     *          implementation; exec() handles it defensively. Performs no
     *          locking of its own, relying on exec() having already taken
     *          M_SHELL_EXEC_MTX.
     *
     */
    auto ShellExec::inner_exec(const std::string &line_) -> int {
        if (end_whiled(line_)) {
            return 0;
        } else if ("cat history" == line_) {
            cat_command_history();
        } else if ("clr history" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not clear history permission !",
                    "root")) {
                return 2;
            }
            clr_command_history();
        } else if ("stdmsg on" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not enable standard temporarily debug message permission !",
                    "root")) {
                return 2;
            }
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(true);
            std::osyncstream(std::cout) << "Done: Enabled standard temporarily debug message." << std::endl;
        } else if ("stdmsg off" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not disable standard temporarily debug message permission !",
                    "root")) {
                return 2;
            }
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(false);
            std::osyncstream(std::cout) << "Done: Disabled standard temporarily debug message." << std::endl;
        } else if ("ruacdb help" == line_) {
            {
                ruac::help::HelpGuide hge;
                hge.helpshell();
            }
        } else if ("ruacdb user.info show all" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not show users info permission !",
                    "root")) {
                return 2;
            }
            {
                ruac::usersystem::UsersMap usmap;
                usmap.show_users_map();
            }
        } else if ("add new user.env" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not add new user env permission ! You must be root to do this.",
                    "root")) {
                return 2;
            }
            {
                ruac::login::RegisteredUser ru;
                ru.registere();
            }

        } else {
            if (!uid_permission_guard(
                    "Error: Current user is not execute command permission !",
                    "manager")) {
                return 2;
            }
            M_SYN_LITE.syntax_line_hook(line_);
        }
        return 2;
    }

    /**
     * @brief Thread-safe entry point to parse and dispatch shell commands
     *
     * @param lines_ - Raw user input, may contain multiple semicolon-separated
     *                 commands
     *
     * @return int - 0 = terminate (quit/exit), 1 = reserved (currently
     *               unreachable), 2 = continue
     *
     * @details Acquires M_SHELL_EXEC_MTX for the entire parse-dispatch
     *          sequence so inner_exec and the history helpers see a
     *          consistent shared state. Creates a local ShellParser, feeds
     *          it lines_ via get_lines() (which mutates the argument),
     *          retrieves the parsed single-line vector via ret_lines(),
     *          then clears the parser via clr_lines(). Iterates each
     *          parsed command calling inner_exec(); if inner_exec returns
     *          0 or 1, that code is returned immediately so remaining
     *          commands are not dispatched. Returns 2 when all parsed
     *          commands have been handled without an early exit.
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
