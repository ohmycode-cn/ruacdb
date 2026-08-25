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
#include "permission_guard/ruac_guardlock.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "usersystem/ruac_usersmap.hpp"

#include <iostream>
#include <syncstream>

namespace ruac::rshell::core {

    /**
     * @brief Construct an Exec bound to a kernel state
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Stores the kernel reference in m_kstate and initialises
     *          the SynxLite instance (m_synlite) with the user id from
     *          kstate_. SynxLite handles SQL-style command parsing.
     *
     */
    Exec::Exec(kernel::state::Kernel &kstate_)
        : m_synlite(kstate_.get_current_user_id()),
          m_kstate(kstate_) {
        M_ROOT_LINES = {
            "add new user",
            "ruacdb.host user show.all",
            "stdmsg off",
            "stdmsg on",
        };
    }

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
     * @param guard_ - Minimum GuardList level required
     * @param msg_ - Error message text printed when the check fails
     *
     * @return bool - true if the current user's group meets guard_;
     *                false otherwise (prints msg_ on failure)
     *
     */
    auto Exec::uid_permission_guard(ruac::permission_guard::GuardList guard_, const std::string &msg_) -> bool {
        auto &gl = ruac::permission_guard::GuardLock::get();
        if (!gl.judgment_lock(get_current_uid(), guard_)) {
            gl.print_message("Error: ", msg_);
            return false;
        }
        return true;
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
     *          forwarded to m_synlite.process() for SQL-style
     *          parsing. Permission failures return CONTINUE.
     *
     */
    auto Exec::dispatch(const std::string &line_) -> status_code {

        if ("permission guard msg on" == line_) {
            ruac::permission_guard::GuardLock::get().output_judgment_lock_message(true);
            return status_code::CONTINUE;
        }

        if ("permission guard msg off" == line_) {
            ruac::permission_guard::GuardLock::get().output_judgment_lock_message(false);
            return status_code::CONTINUE;
        }

        if ("exit" == line_ || "quit" == line_) {
            return status_code::NORMAL_EXIT;
        }
        if ("ruacdb help" == line_) {
            ruac::help::api::HelpEntry hge;
            hge.run();
            return status_code::CONTINUE;
        }

        auto itr = std::find(M_ROOT_LINES.begin(), M_ROOT_LINES.end(), line_);
        if (itr != M_ROOT_LINES.end()) {
            if (!uid_permission_guard(
                    ruac::permission_guard::GuardList::ROOT,
                    "Root permission required for this command.")) {
                return status_code::CONTINUE;
            }

            if ("stdmsg on" == line_) {
                ruac::rstd::messages::StdMsg::instance().enable_stdmsg(true);
                std::osyncstream(std::cout) << "Done: Enabled standard temporarily debug message." << std::endl;
            } else if ("stdmsg off" == line_) {
                ruac::rstd::messages::StdMsg::instance().enable_stdmsg(false);
                std::osyncstream(std::cout) << "Done: Disabled standard temporarily debug message." << std::endl;
            } else if ("ruacdb.host user show.all" == line_) {
                ruac::usersystem::UsersMap usmap;
                usmap.show_users_map();
            } else if ("add new user" == line_) {
                ruac::login::RegisteredUser ru;
                ru.registere();
            }
            return status_code::CONTINUE;
        }

        if (!uid_permission_guard(
                ruac::permission_guard::GuardList::MANAGER,
                "Manager permission required to execute command.")) {
            return status_code::CONTINUE;
        }

        m_synlite.process(line_);
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
