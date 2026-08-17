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
#ifndef RUAC_LOGIN_USER_HPP
#define RUAC_LOGIN_USER_HPP

namespace ruac::login {

    enum class LoginMethod {
        LOCAL = 0,
        REMOTE
    };

    class LoginUser {
      private:
        LoginMethod m_login_method;

      public:
        LoginUser() = default;
        ~LoginUser() = default;

      public:
        void conf_login(const LoginMethod login_method_ = LoginMethod::LOCAL);
        void init_login();
    };

} // namespace ruac::login

#endif // RUAC_LOGIN_USER_HPP
