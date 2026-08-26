/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_registered_user.hpp
 * src/login/ruac_registered_user.cpp
 */

#include "login/lib/ruac_legal_characters.hpp"
#include "login/ruac_registered_user.hpp"
#include "rstd/cmdlex/ruac_cmdlex.hpp"
#include "rlib/ruac_tdebug.hpp"
#include "system/user/ruac_group.hpp"
#include "system/user/ruac_id.hpp"
#include "system/user/ruac_name.hpp"

#include <iostream>
#include <mutex>
#include <vector>
#include <sstream>
#include <string>
#include <syncstream>

namespace {

    auto trim(const std::string &s_) -> std::string {
        auto start = s_.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
            return "";
        auto end = s_.find_last_not_of(" \t\r\n");
        return s_.substr(start, end - start + 1);
    }

} // anonymous namespace

namespace ruac::login {

    /**
     * @brief Validate a user name: must be non-empty, alphanumeric only,
     *        and must not already exist in UserId.
     */
    auto RegisteredUser::validate_user_name(const std::string &name_) -> bool {
        if (name_.empty()) {
            std::osyncstream(std::cout)
                << "Error: User name is empty." << std::endl;
            return false;
        }

        for (auto &c : name_) {
            if (!isalpha(c) && !isdigit(c) && '_' != c) {
                std::osyncstream(std::cout)
                    << "Error: Invalid user name. Because user name include "
                       "invalid character: '"
                    << c << "'" << std::endl;
                return false;
            }
        }

        if (-1 != ruac::system::user::UserId::instance().get_user_id(name_)) {
            std::osyncstream(std::cout)
                << "Error: User name '" << name_ << "' already exists."
                << std::endl;
            return false;
        }

        return true;
    }

    /**
     * @brief Register a validated user name into UserName and UserId singletons.
     *        Caller must ensure validate_user_name() returned true.
     */
    auto RegisteredUser::reg_user(const std::string &name_) -> bool {
        ruac::system::user::UserName::instance().add_user(name_);
        ruac::system::user::UserId::instance().add_user(name_);
        return true;
    }

    /**
     * @brief Assign a group to the given user. Returns false if the user
     *        already has a group or the group name is invalid.
     */
    auto RegisteredUser::reg_group(
        const std::string &name_, const std::string &group_) -> bool {
        auto &ug = ruac::system::user::UserGroup::instance();
        if (!ug.exist_group(name_, group_)) {
            return false;
        }
        ug.add_group(name_, group_);
        return true;
    }

    /**
     * @brief Parse and execute a single command line.
     *
     * @param cmd_          The trimmed command string
     * @param current_user_ In/out: the user name established by a prior
     *                      "add user" command within the same session
     *
     * @return true  if the command was a recognized, successfully executed
     *               registration command ("add user" or "add group")
     * @return false in two cases:
     *               - command was recognized but the registration failed
     *                 (e.g. duplicate name, invalid group)
     *               - command was not recognized at all (not a registration
     *                 error, just unknown syntax)
     *
     * @details Unrecognized commands print an error and return false without
     *          side effects; the caller should NOT count them as registration
     *          failures.
     */
    auto RegisteredUser::dispatch_cmd(const std::string &cmd_, std::string &current_user_) -> bool {

        {
            auto &u = ruac::rlib::tdebug::Info::get();
            std::string msg{cmd_};
            auto str = u.fmt("RegisteredUser", "dispatch_cmd(...)", std::move(msg));
            u.print(str, __FILE__, __LINE__);
        }

        if (cmd_.size() > 9 && cmd_.substr(0, 9) == "add user ") {
            auto name = trim(cmd_.substr(9));

            if (!validate_user_name(name)) {
                return false;
            }

            reg_user(name);

            current_user_ = name;
            std::osyncstream(std::cout) << "Done: setting user name to " << name << "." << std::endl;
            return true;
        }

        /* "add group <name>" */
        {
            auto &u = ruac::rlib::tdebug::Info::get();
            std::string msg{cmd_};
            auto str = u.fmt("RegisteredUser", "dispatch_cmd(...)", std::move(msg));
            u.print(str, __FILE__, __LINE__);
        }
        if (cmd_.size() > 10 && cmd_.substr(0, 10) == "add group ") {
            auto group = trim(cmd_.substr(10));

            if (current_user_.empty()) {
                std::stringstream ss;
                ss << "Error: No user registered in this session. ";
                ss << "Use 'add user' first.";
                std::osyncstream(std::cout) << ss.str() << std::endl;
                return false;
            }
            if (group.empty()) {
                std::osyncstream(std::cout) << "Error: Group name is empty." << std::endl;
                return false;
            }

            if (!reg_group(current_user_, group)) {
                return false;
            }

            std::osyncstream(std::cout) << "Done: setting user group to " << group << "." << std::endl;
            current_user_.clear();
            return true;
        }

        /* Unrecognized command — not a registration failure */
        std::osyncstream(std::cout) << "Error: Unknown command '" << cmd_ << "'" << std::endl;
        return false;
    }

    /**
     * @brief Run the interactive user registration REPL.
     *
     * @return true  if registration completed successfully
     * @return false after 3 consecutive registration failures
     *
     * @details Commands are split on ';' by CmdLex. Each segment is trimmed
     *          then dispatched independently.
     *
     *          - "stdmsg on"/"stdmsg off": toggle debug output (not counted
     *            as registration actions)
     *          - "exit/quit user.env": exit the loop
     *          - "add user <name>": register a user name
     *          - "add group <name>": assign a group to the current user,
     *            then exit the loop on success
     *
     *          Only recognized commands that fail validation increment the
     *          failure counter. Unrecognized input and meta-commands do not.
     */
    auto RegisteredUser::registere() -> bool {
        std::lock_guard<std::mutex> lock(M_REGISTERE_USER_MTX);

        auto &info = rlib::tdebug::Info::get();

        rstd::cmdlex::api::CmdLex cmdlex;
        std::vector<std::string> lines;
        std::string current_user;
        int fail_count{0};

        while (true) {
            std::osyncstream(std::cout) << "register-user-> ";
            std::string field;
            if (!std::getline(std::cin, field)) {
                return false;
            }

            if (field.empty()) {
                continue;
            }

            if (field[0] == '#' || (field.size() >= 2 && field.substr(0, 2) == "//")) {
                continue;
            }

            if (!ruac::login::lib::legal_char(field)) {
                std::osyncstream(std::cout) << "Error: command line include illegal characters." << std::endl;
                continue;
            }

            if (fail_count >= 3) {
                std::osyncstream(std::cout) << "Error: Register failed. Because of 3 times try." << std::endl;
                return false;
            }

            if (!cmdlex.lex(field, lines)) {
                std::stringstream ss;
                ss << "Error: Invalid setting syntax !";
                ss << "       |____ '" << field << "'";
                std::osyncstream(std::cout) << ss.str() << std::endl;
                continue;
            }

            bool should_exit = false;

            for (auto &line : lines) {

                auto cmd = trim(line);

                if (cmd.empty()) {
                    continue;
                }

                if (cmd == "stdmsg on") {
                    info.enable_stdmsg(true);
                    continue;
                }

                if (cmd == "stdmsg off") {
                    info.enable_stdmsg(false);
                    continue;
                }

                if (cmd == "exit user.env" || cmd == "quit user.env") {
                    should_exit = true;
                    break;
                }

                bool ok = dispatch_cmd(cmd, current_user);

                if (ok && current_user.empty()) {
                    should_exit = true;
                    break;
                }

                if (!ok && !current_user.empty()) {
                    /*
                     * Recognized command failed (e.g. duplicate user name,
                     * invalid group) while a session is active.
                     */
                    fail_count++;
                }
            }

            if (should_exit) {
                break;
            }
        }

        return true;
    }

} // namespace ruac::login
