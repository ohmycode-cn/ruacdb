/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_login_user.hpp
 * src/login/ruac_login_user.cpp
 */

#include "login/ruac_login_user.hpp"
#include "share/ruac_userlist.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac::login {

    void LoginUser::conf_login(const LoginMethod login_method_) {
        m_login_method = login_method_;
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
        {
            std::stringstream ss;
            ss << "Error: Login method is not supported. Default use live user.\n";
            ss << "Warn : You current use live user login. It not any permission.";
            std::osyncstream(std::cout) << ss.str() << std::endl;
        }
            ruac::share::UserList::instance().add_map(1, "live");
            m_user_name = "live";
            m_user_id = 1;
        }
    }

    auto LoginUser::get_uname() -> std::string {
        return m_user_name;
    }

    auto LoginUser::get_uid() -> int {
        return m_user_id;
    }

} // namespace ruac::login
