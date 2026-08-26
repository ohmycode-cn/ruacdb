/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_group.hpp
 * src/system/user/ruac_group.cpp
 *
 * @brief Defines the UserGroup singleton class for managing user-to-group
 *        mappings with thread-safe access. Group definitions and their
 *        default permissions are sourced from the shared G_GROUP_REGISTRY
 *        in ruac_group_registry.hpp.
 */

#pragma once
#ifndef RUAC_GROUP_HPP
#define RUAC_GROUP_HPP

#include <mutex>
#include <string>
#include <unordered_map>

namespace ruac::system::user {

    class UserGroup {
      private:
        std::mutex M_USER_GROUP_MTX;

        // username to group_name (group validity is checked against
        // G_GROUP_REGISTRY in ruac_group_registry.hpp)
        std::unordered_map<std::string, std::string> m_user_group_table{
            /*user name, group name*/
            {"syst", "syst"},
            {"root", "root"},
            {"live", "visitor"},
        };

      private:
        UserGroup() = default;
        ~UserGroup() = default;
        UserGroup(const UserGroup &) = delete;
        UserGroup &operator=(const UserGroup &) = delete;

      public:
        static auto instance() -> UserGroup &;
        auto get_groups() -> std::unordered_map<std::string, std::string>;
        auto get_group(const std::string &username_) -> std::string;
        auto exist_group(const std::string &username_, const std::string &group_) -> bool;
        void add_group(const std::string &username_, const std::string &group_);
    };

} // namespace ruac::system::user

#endif // RUAC_GROUP_HPP
