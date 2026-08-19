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

    void LoginUser::conf_login(const LoginMethod login_method_) {
        m_login_method = login_method_;
    }

    void LoginUser::sets_login(const std::string &user_name_) {
        m_user_name = user_name_;
    }

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
                ss << "Error: Login method is not supported. Default use " << m_user_name << " user.\n";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
        }
    }

    auto LoginUser::get_uname() -> std::string {
        return m_user_name;
    }

    auto LoginUser::get_uid() -> int {
        return m_user_id;
    }

} // namespace ruac::login
