/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/ruac_registered_user.hpp
 * src/login/ruac_registered_user.cpp
 *
 * @brief Defines the RegisteredUser class for handling new user registration
 *        with thread-safe group and username assignment.
 */

#pragma once
#ifndef RUAC_REGISTERED_USER_HPP
#define RUAC_REGISTERED_USER_HPP

#include <mutex>
#include <string>

namespace ruac::login {

    class RegisteredUser {
      private:
        std::mutex M_REGISTERE_USER_MTX;

      private:
        auto validate_user_name(const std::string &name_) -> bool;
        auto reg_user(const std::string &name_) -> bool;
        auto reg_group(const std::string &name_, const std::string &group_) -> bool;
        auto dispatch_stdmsg(const std::string &line_) -> bool;
        auto dispatch_cmd(const std::string &cmd_, std::string &current_user_) -> bool;

      public:
        RegisteredUser() = default;
        ~RegisteredUser() = default;

      public:
        auto registere() -> bool;
    };

} // namespace ruac::login

#endif // RUAC_REGISTERED_USER_HPP
