/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_registered_user.hpp
 * src/login/ruac_registered_user.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_REGISTERED_USER_HPP
#define RUAC_REGISTERED_USER_HPP

#include <string>
#include <mutex>

namespace ruac::login {

    class RegisteredUser {
      private:
        std::mutex M_REGISTERE_USER_MTX;
        std::string m_current_user_name;

      private:
        auto set_user_ne(const std::string &user_ne_) -> bool;
        auto set_user_gp(const std::string &user_gp_) -> bool;
        auto hdl_add_user(const std::string &user_ne_) -> bool;
        auto hdl_add_group(const std::string &user_gp_) -> bool;

      public:
        RegisteredUser() = default;
        ~RegisteredUser() = default;

      public:
        auto registere() -> bool;
    };

} // namespace ruac::login

#endif // RUAC_REGISTERED_USER_HPP
