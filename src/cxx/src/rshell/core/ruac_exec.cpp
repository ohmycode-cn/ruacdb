/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/core/ruac_exec.hpp
 * src/rshell/core/ruac_exec.cpp
 */

#include "rshell/core/ruac_exec.hpp"
#include "help/ruac_help_entry.hpp"
#include "login/ruac_registered_user.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "rshell/lib/ruac_guard.hpp"
#include "usersystem/ruac_usersmap.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::rshell::core {

    /**
     * @brief Construct an Exec bound to a kernel state
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Stores the kernel reference in m_kstate and initialises
     *          the SynLite instance (m_synlite) with the user id from
     *          kstate_. SynLite handles SQL-style command parsing.
     *
     */
    Exec::Exec(kernel::state::Kernel &kstate_)
        : m_synlite(kstate_.get_current_user_id()),
          m_kstate(kstate_) {}

    /**
     * @brief Get the current user name from kernel state
     *
     * @return std::string - The user name stored in the shared Kernel
     *         object.
     *
     */
    auto Exec::get_current_user() -> std::string {
        return m_kstate.get_current_user_name();
    }

    /**
     * @brief Get the current user id from kernel state
     *
     * @return int - The uid stored in the shared Kernel object.
     *
     */
    auto Exec::get_current_uid() -> int {
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
     */
    auto Exec::uid_permission_guard(const std::string &msg_, const std::string &guard_group_, bool out_msg_) -> bool {
        return ruac::rshell::lib::guard::uid_permission_guard(get_current_uid(), msg_, guard_group_, out_msg_);
    }

    /**
     * @brief Dispatch a single command line to the appropriate handler
     *
     * @param line_ - A pre-processed command line (spaces removed,
     *               lowercased)
     *
     * @return status_code - NORMAL_EXIT for "exit"/"quit",
     *                       CONTINUE for all other commands
     *
     * @details Recognised commands:
     *          - "stdmsg on"/"off": root-only, toggles StdMsg debug output.
     *          - "ruacdb help": creates a HelpEntry and enters its shell.
     *          - "exit"/"quit": returns NORMAL_EXIT to terminate the loop.
     *          - "ruacdb user.info show all": root-only, prints UsersMap.
     *          - "add new user.env": root-only, launches RegisteredUser REPL.
     *          All other strings are gated on the "manager" group and then
     *          forwarded to m_synlite.syntax_line_hook() for SQL-style
     *          parsing. Permission failures return CONTINUE.
     *
     */
    auto Exec::dispatch(const std::string &line_) -> status_code {
        if ("stdmsg on" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not enable standard temporarily debug message permission !",
                    "root")) {
                return status_code::CONTINUE;
            }
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(true);
            std::osyncstream(std::cout) << "Done: Enabled standard temporarily debug message." << std::endl;
        } else if ("stdmsg off" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not disable standard temporarily debug message permission !",
                    "root")) {
                return status_code::CONTINUE;
            }
            ruac::rstd::messages::StdMsg::instance().enable_stdmsg(false);
            std::osyncstream(std::cout) << "Done: Disabled standard temporarily debug message." << std::endl;
        } else if ("ruacdb help" == line_) {
            {
                ruac::help::api::HelpEntry hge;
                hge.run();
            }
        } else if ("exit" == line_ || "quit" == line_) {
            return status_code::NORMAL_EXIT;
        } else if ("ruacdb user.info show all" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not show users info permission !",
                    "root")) {
                return status_code::CONTINUE;
            }
            {
                ruac::usersystem::UsersMap usmap;
                usmap.show_users_map();
            }
        } else if ("add new user.env" == line_) {
            if (!uid_permission_guard(
                    "Error: Current user is not add new user env permission ! You must be root to do this.",
                    "root")) {
                return status_code::CONTINUE;
            }
            {
                ruac::login::RegisteredUser ru;
                ru.registere();
            }
        } else {
            if (!uid_permission_guard(
                    "Error: Current user is not execute command permission !",
                    "manager")) {
                return status_code::CONTINUE;
            }
            m_synlite.syntax_line_hook(line_);
        }
        return status_code::CONTINUE;
    }

    /**
     * @brief Execute a single command line
     *
     * @param line_ - A pre-processed command line
     *
     * @return status_code - The status code returned by dispatch()
     *
     */
    auto Exec::exec(const std::string &line_) -> status_code {
        return dispatch(line_);
    }

} // namespace ruac::rshell::core
