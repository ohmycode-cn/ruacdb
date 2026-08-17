/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_registered_user.hpp
 * src/login/ruac_registered_user.cpp
 */

#include "login/ruac_registered_user.hpp"
#include "usersystem/ruac_usergroup.hpp"
#include "usersystem/ruac_userid.hpp"
#include "usersystem/ruac_username.hpp"
#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include <string>
#include <syncstream>
#include <iostream>
#include <sstream>
#include <mutex>

namespace ruac::login {

    /**
     * @brief Validate and register a new user name
     *
     * @param user_ne_ - The user name to register
     *
     * @return bool - true if the name was accepted and registered; false
     *         if it already exists or contains invalid characters
     *
     * @details First checks UserId for an existing uid; if found, reports
     *          a duplicate-name error to stderr and returns false. Then
     *          scans every character requiring isalpha or isdigit; any
     *          invalid character produces an error and false. On success
     *          the name is appended to both UserName and UserId singletons.
     *
     */
    auto RegisteredUser::set_user_ne(const std::string &user_ne_) -> bool {
        auto uid = ruac::usersystem::UserId::instance().get_user_id(user_ne_);

        if (-1 != uid) {
            {
                std::stringstream ss;
                ss << "Error: User name '" << user_ne_ << "' already exists.";
                std::cerr << ss.str() << std::endl;
            }
            return false;
        }

        for (auto &c : user_ne_) {
            if (!isalpha(c) && !isdigit(c)) {
                {
                    std::stringstream ss;
                    ss << "Error: Invalid user name. Because include invalid character." << c;
                    std::cerr << ss.str() << std::endl;
                }
                return false;
            }
        }

        ruac::usersystem::UserName::instance().add_user(user_ne_);
        ruac::usersystem::UserId::instance().add_user(user_ne_);
        return true;
    }

    /**
     * @brief Assign a group to the current registering user
     *
     * @param user_gp_ - Group name to assign; must exist in M_GROUP_REGISTRY
     *
     * @return bool - true if the group was assigned; false otherwise
     *
     * @details Delegates to UserGroup::add_group() with the current user
     *          name (set by a prior set_user_ne call) and the supplied
     *          group name. The group validity check is performed inside
     *          UserGroup against M_GROUP_REGISTRY.
     *
     */
    auto RegisteredUser::set_user_gp(const std::string &user_gp_) -> bool {
        auto &u = ruac::usersystem::UserGroup::instance();
        if (!u.add_group(m_current_user_name, user_gp_)) {
            return false;
        }
        return true;
    }

    /**
     * @brief Handle the "add user" command from the registration REPL
     *
     * @param user_ne - The user name extracted from the command line
     *
     * @return bool - true if the user was registered; false if validation
     *         failed
     *
     * @details Emits a debug trace via StdMsg/StdDug on entry, then calls
     *          set_user_ne() to validate and register the name. On
     *          success stores the name in m_current_user_name and prints
     *          a confirmation message to stdout.
     *
     */
    auto RegisteredUser::hdl_add_user(const std::string &user_ne) -> bool {
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();
        std::stringstream ss;
        ss << "Class: RegisteredUser, Func: registere, Branch: add user -> " << user_ne;
        stdmsg.print(stdbug.ostrs(ss.str(), __FILE__, __LINE__));

        if (!set_user_ne(user_ne))
            return false;

        m_current_user_name = user_ne;
        std::osyncstream(std::cout) << "Done: setting user name to " << user_ne << "." << std::endl;
        return true;
    }

    /**
     * @brief Handle the "add group" command from the registration REPL
     *
     * @param user_gp - The group name extracted from the command line
     *
     * @return bool - true if the group was assigned; false if assignment
     *         failed
     *
     * @details Emits a debug trace via StdMsg/StdDug on entry, then calls
     *          set_user_gp() to assign the group to the current user. On
     *          success clears m_current_user_name and prints a
     *          confirmation message to stdout. The caller (registere)
     *          uses the return value to decide whether to break the loop.
     *
     */
    auto RegisteredUser::hdl_add_group(const std::string &user_gp) -> bool {
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();
        std::stringstream ss;
        ss << "Class: RegisteredUser, Func: registere, Branch: add group -> " << user_gp;
        stdmsg.print(stdbug.ostrs(ss.str(), __FILE__, __LINE__));

        if (!set_user_gp(user_gp))
            return false;

        m_current_user_name.clear();
        std::osyncstream(std::cout) << "Done: setting user group to " << user_gp << "." << std::endl;
        return true;
    }

    /**
     * @brief Run the interactive user registration flow
     *
     * @return bool - true if registration completed or the user chose to
     *         exit; false if the user exceeded 3 failed attempts
     *
     * @details Acquires M_REGISTERE_USER_MTX and enters a REPL loop that
     *          prompts "user-register-env-> " and reads lines from stdin.
     *          Tracks a failure counter (time_count); on reaching 3 the
     *          function reports an error and returns false. Recognised
     *          commands:
     *          - "add user <name>":  delegates to hdl_add_user() to
     *            validate and register the name.
     *          - "add group <grp>": delegates to hdl_add_group() to assign
     *            the group, then breaks out of the loop to finish.
     *          - "stdmsg on"/"stdmsg off": toggle debug message output.
     *          - "exit ruser"/"quit ruser": break out of the loop.
     *          Unrecognised input prints an error and continues without
     *          incrementing time_count. Each successful step resets
     *          time_count to 0.
     *
     */
    auto RegisteredUser::registere() -> bool {
        std::lock_guard<std::mutex> lock(M_REGISTERE_USER_MTX);
        int time_count{0};

        while (true) {
            std::osyncstream(std::cout) << "user-register-env-> ";
            std::string field;
            std::getline(std::cin, field);

            if (time_count >= 3) {
                std::cerr << "Error: Register failed. Because of 3 times try." << std::endl;
                return false;
            }
            if ("stdmsg on" == field) {
                rstd::messages::StdMsg::instance().enable_stdmsg(true);
                continue;
            }
            if ("stdmsg off" == field) {
                rstd::messages::StdMsg::instance().enable_stdmsg(false);
                continue;
            }
            if ("exit ruser" == field || "quit ruser" == field) {
                break;
            }

            bool should_break = false;
            bool success = false;

            if ("add user " == field.substr(0, 9)) {
                success = hdl_add_user(field.substr(9));
            } else if ("add group " == field.substr(0, 10)) {
                success = hdl_add_group(field.substr(10));
                should_break = true;
            } else {
                std::osyncstream(std::cout) << "Error: Invalid setting syntax !" << std::endl;
                continue;
            }

            if (!success) {
                time_count++;
                continue;
            }

            time_count = 0;
            if (should_break) {
                break;
            }
        }

        return true;
    }

} // namespace ruac::login
