/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_usergroup.hpp
 * src/usersystem/ruac_usergroup.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_USERGROUP_HPP
#define RUAC_USERGROUP_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>

namespace ruac::usersystem {

    class UserGroup {
      private:
        std::mutex M_USER_GROUP_MTX;

      private:
        const std::vector<std::string> group_list = {"root", "live", "manager", "visitor"};
        // username -> group
        std::unordered_map<std::string, std::string> m_user_group_table{
            {"root", group_list[0]},
            {"live", group_list[1]}};

      private:
        UserGroup() = default;
        ~UserGroup() = default;
        UserGroup(const UserGroup &) = delete;
        UserGroup &operator=(const UserGroup &) = delete;

      public:
        static auto instance() -> UserGroup &;
        auto get_group(const std::string &username) -> std::string;
        auto add_group(const std::string &username, const std::string &group) -> bool;
    };

} // namespace ruac::usersystem

#endif // RUAC_USERGROUP_HPP
