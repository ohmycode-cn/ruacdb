/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_users_map.hpp
 * src/system/user/ruac_users_map.cpp
 *
 * @brief Defines the UsersMap class for displaying nested user-group-permission maps with formatted column output.
 */

#pragma once
#ifndef RUAC_USERS_MAP_HPP
#define RUAC_USERS_MAP_HPP

#include "system/user/ruac_permission.hpp"

#include <cstddef>
#include <mutex>
#include <string>
#include <unordered_map>

namespace ruac::system::user {

    class UsersMap {
      private:
        // user name [user id [group name [group permission]]
        std::unordered_map<std::string, std::unordered_map<int, std::unordered_map<std::string, Permission>>> m_usmap;
        std::mutex M_USERS_MAP_MTX;
        size_t m_max_width_name{0};
        size_t m_max_width_uid{0};
        size_t m_max_width_group{0};
        size_t m_max_width_rd{0}; // read
        size_t m_max_width_we{0}; // write
        size_t m_max_width_xe{0}; // execute
        size_t m_max_width_lk{0}; // link
        size_t m_max_width_os{0}; // system

      private:
        void merge_user_info();
        auto print_user_info() -> std::string;

      public:
        UsersMap() = default;
        ~UsersMap() = default;

      public:
        void show_users_map();
    };

} // namespace ruac::system::user

#endif // RUAC_USERS_MAP_HPP
