/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_login_user.hpp
 * src/login/ruac_login_user.cpp
 */

#include "login/ruac_login_user.hpp"
#include "share/ruac_userlist.hpp"
#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::login {

    /**
     * @brief Configure the login method to be used
     *
     * @param login_method_ - The LoginMethod enum value (LOCAL, REMOTE,
     *                        or OTHER)
     *
     * @details Stores the method in m_login_method for later use by
     *          init_login(). No validation or side effects.
     *
     */
    void LoginUser::conf_login(const LoginMethod login_method_) {
        m_login_method = login_method_;
    }

    /**
     * @brief Set the user name for this login session
     *
     * @param user_name_ - The user name to store
     *
     * @details Stores the name in m_user_name. No validation.
     *
     */
    void LoginUser::sets_login(const std::string &user_name_) {
        m_user_name = user_name_;
    }

    /**
     * @brief Initialise the login backend based on the configured method
     *
     * @details Switches on m_login_method:
     *          - LOCAL:  creates a LoginLocal instance.
     *          - REMOTE: creates a LoginRemote instance.
     *          - default (OTHER): fallback for testing; registers a
     *            root user (uid 0) in UserList, sets m_user_name to
     *            "root" and m_user_id to 0, then prints a warning that
     *            the method is unsupported and root is being used.
     *
     */
    void LoginUser::init_login() {
        switch (m_login_method) {
        case LoginMethod::LOCAL:
            m_login = std::make_unique<LoginLocal>();
            break;
        case LoginMethod::REMOTE:
            m_login = std::make_unique<LoginRemote>();
            break;
        default: // Default use live user. -> LoginMethod::OTHER
                 // Temporary test. It not last release.
            ruac::share::UserList::instance().add_map(0, "root");
            m_user_name = "root";
            m_user_id = 0;
            {
                std::stringstream ss;
                ss << "[Error :(]: Login method is not supported. Default use " << m_user_name << " user";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
        }
    }

    /**
     * @brief Get the user name for the current session
     *
     * @return std::string - The user name stored in m_user_name
     *
     */
    auto LoginUser::get_uname() -> std::string {
        return m_user_name;
    }

    /**
     * @brief Get the user id for the current session
     *
     * @return int - The uid stored in m_user_id
     *
     */
    auto LoginUser::get_uid() -> int {
        return m_user_id;
    }

} // namespace ruac::login
