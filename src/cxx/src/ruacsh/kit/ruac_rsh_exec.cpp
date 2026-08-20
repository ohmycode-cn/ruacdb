/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/kit/ruac_rsh_exec.hpp
 * src/ruacsh/kit/ruac_rsh_exec.cpp
 */

#include "ruacsh/kit/ruac_rsh_exec.hpp"
#include "help/ruac_help_guide.hpp"
#include "login/ruac_registered_user.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "ruacsh/lib/ruac_guard.hpp"
#include "usersystem/ruac_usersmap.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::ruacsh::kit {

    /**
     * @brief Construct an RshExec bound to a kernel state
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Stores the kernel reference in m_kstate and initialises
     *          the SynLite instance (m_synlite) with the user id from
     *          kstate_. SynLite handles SQL-style command parsing.
     *
     */
    RshExec::RshExec(kernel::state::Kernel &kstate_)
        : m_synlite(kstate_.get_current_user_id()),
          m_kstate(kstate_) {}

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
    auto RshExec::get_current_user() -> std::string {
        return m_kstate.get_current_user_name();
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
    auto RshExec::get_current_uid() -> int {
        return m_kstate.get_current_user_id();
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
    auto RshExec::uid_permission_guard(const std::string &msg_, const std::string &guard_group_, bool out_msg_) -> bool {
        return ruac::ruacsh::lib::guard::uid_permission_guard(get_current_uid(), msg_, guard_group_, out_msg_);
    }

    /**
     * @brief Dispatch a single command line to the appropriate handler
     *
     * @param line_ - A pre-processed command line (spaces removed,
     *               lowercased)
     *
     * @return STAUTS_CODE - NORMAL_EXIT for "exit"/"quit",
     *                       CONTINUE for all other commands
     *
     * @details Recognised commands:
     *          - "stdmsg on"/"off": root-only, toggles StdMsg debug output.
     *          - "ruacdb help": creates a HelpGuide and enters its shell.
     *          - "exit"/"quit": returns NORMAL_EXIT to terminate the loop.
     *          - "ruacdb user.info show all": root-only, prints UsersMap.
     *          - "add new user.env": root-only, launches RegisteredUser REPL.
     *          All other strings are gated on the "manager" group and then
     *          forwarded to m_synlite.syntax_line_hook() for SQL-style
     *          parsing. Permission failures return CONTINUE.
     *
     */
    auto RshExec::query(const std::string &line_) -> STAUTS_CODE {
        if ("stdmsg on" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not enable standard temporarily debug message permission !",
                    "root")) {
                return STAUTS_CODE::CONTINUE;
            }
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(true);
            std::osyncstream(std::cout) << "Done: Enabled standard temporarily debug message." << std::endl;
        } else if ("stdmsg off" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not disable standard temporarily debug message permission !",
                    "root")) {
                return STAUTS_CODE::CONTINUE;
            }
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(false);
            std::osyncstream(std::cout) << "Done: Disabled standard temporarily debug message." << std::endl;
        } else if ("ruacdb help" == line_) {
            {
                ruac::help::HelpGuide hge;
                hge.helpshell();
            }
        } else if ("exit" == line_ || "quit" == line_) {
            return STAUTS_CODE::NORMAL_EXIT;
        } else if ("ruacdb user.info show all" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not show users info permission !",
                    "root")) {
                return STAUTS_CODE::CONTINUE;
            }
            {
                ruac::usersystem::UsersMap usmap;
                usmap.show_users_map();
            }
        } else if ("add new user.env" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not add new user env permission ! You must be root to do this.",
                    "root")) {
                return STAUTS_CODE::CONTINUE;
            }
            {
                ruac::login::RegisteredUser ru;
                ru.registere();
            }
        } else {
            if (!uid_permission_guard(
                    "Error: Current user is not execute command permission !",
                    "manager")) {
                return STAUTS_CODE::CONTINUE;
            }
            m_synlite.syntax_line_hook(line_);
        }
        return STAUTS_CODE::CONTINUE;
    }

    /**
     * @brief Execute a single command line
     *
     * @param line_ - A pre-processed command line
     *
     * @return STAUTS_CODE - The status code returned by query()
     *
     * @details Thin wrapper that delegates directly to query().
     *
     */
    auto RshExec::exec(const std::string &line_) -> STAUTS_CODE {
        return query(line_);
    }

} // namespace ruac::ruacsh::kit
