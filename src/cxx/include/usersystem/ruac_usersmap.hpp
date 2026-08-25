/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_usersmap.hpp
 * src/usersystem/ruac_usersmap.cpp
 *
 * @brief Defines the UsersMap class for displaying nested user-group-permission maps with formatted column output.
 */

#pragma once
#ifndef RUAC_USERSMAP_HPP
#define RUAC_USERSMAP_HPP

#include "ruac_user_group_perm.hpp"
#include <cstddef>
#include <mutex>
#include <string>
#include <unordered_map>

namespace ruac::usersystem {

    class UsersMap {
      private:
        // user name [user id [group name [group permission]]
        std::unordered_map<std::string, std::unordered_map<int, std::unordered_map<std::string, Permission>>> m_usmap;
        std::mutex M_USERS_MAP_MTX;
        size_t m_max_width_name{0};
        size_t m_max_width_uid{0};
        size_t m_max_width_group{0};
        size_t m_max_width_r{0}; // read
        size_t m_max_width_w{0}; // write
        size_t m_max_width_x{0}; // execute
        size_t m_max_width_l{0};  // link
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

} // namespace ruac::usersystem

#endif // RUAC_USERSMAP_HPP
