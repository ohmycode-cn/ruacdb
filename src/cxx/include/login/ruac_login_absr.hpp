/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_login_absr.hpp
 * src/login/ruac_login_absr.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_LOGIN_ABSR_HPP
#define RUAC_LOGIN_ABSR_HPP

namespace ruac::login {

    class LoginAbsr {
      public:
        virtual void init_login() = 0;
        virtual ~LoginAbsr() = default;
    };

} // namespace ruac::login

#endif // RUAC_LOGIN_ABSR_HPP
