/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_login_remote.hpp
 * src/login/ruac_login_remote.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LOGIN_REMOTE_HPP
#define RUAC_LOGIN_REMOTE_HPP

#include "login/ruac_login_absr.hpp"
namespace ruac::login {

    class LoginRemote : public LoginAbsr {
      public:
        LoginRemote() = default;
        ~LoginRemote() = default;

      public:
        void init_login() override;
    };

} // namespace ruac::login

#endif // RUAC_LOGIN_REMOTE_HPP
