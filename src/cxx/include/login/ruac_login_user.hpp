/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_login_user.hpp
 * src/login/ruac_login_user.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#include "login/ruac_login_absr.hpp"
#ifndef RUAC_LOGIN_USER_HPP
#define RUAC_LOGIN_USER_HPP

#include "login/ruac_login_remote.hpp"
#include "login/ruac_login_local.hpp"
#include <memory>

namespace ruac::login {

    enum class LoginMethod {
        LOCAL = 0,
        REMOTE,
        OTHER
    };

    class LoginUser {
      private:
        std::unique_ptr<LoginAbsr> m_login;
        LoginMethod m_login_method;
        std::string m_user_name;
        int m_user_id;

      public:
        LoginUser() = default;
        ~LoginUser() = default;

      public:
        void conf_login(const LoginMethod login_method_ = LoginMethod::LOCAL);
        void init_login();
        auto get_uname() -> std::string;
        auto get_uid() -> int;
    };

} // namespace ruac::login

#endif // RUAC_LOGIN_USER_HPP
