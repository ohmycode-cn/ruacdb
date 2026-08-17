/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_userid.hpp
 * src/usersystem/ruac_userid.cpp
 *
 * @brief Defines the UserId singleton class for managing user ID assignments with thread-safe access.
 */

#pragma once
#ifndef RUAC_USERID_HPP
#define RUAC_USERID_HPP

#include <mutex>
#include <string>
#include <unordered_map>

namespace ruac::usersystem {

    class UserId {
      private:
        std::unordered_map<std::string, int> m_user_id_table{
            /*user name, user id*/
            {"root", 0},
            {"live", 1}, // default user
        }; // Predefined user "root" with ID 0
        std::mutex M_USER_ID_MTX;

      private:
        UserId() = default;
        ~UserId() = default;
        UserId(const UserId &) = delete;
        UserId &operator=(const UserId &) = delete;

      public:
        static auto instance() -> UserId &;

      public:
        auto get_users_map() -> std::unordered_map<std::string, int>;
        auto get_user_id(const std::string &username_) -> int;
        auto get_user_name(int user_id_) -> std::string;

      public:
        auto add_user(const std::string &username_) -> bool;
    };

} // namespace ruac::usersystem

#endif // RUAC_USERID_HPP
