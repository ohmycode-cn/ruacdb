/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_userpower.hpp
 * src/usersystem/ruac_userpower.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_USERPOWER_HPP
#define RUAC_USERPOWER_HPP

#include <mutex>
#include <string>
#include <unordered_map>

namespace ruac::usersystem {

    struct UserPowerTable {
        std::string m_name;
        int m_uid;
        std::string m_role;
        bool m_rp{false}; // Read Permission
        bool m_wp{false}; // Write Permission
        bool m_xp{false}; // Execute Permission
        bool m_lp{false}; // Link Permission
    };

    class UserPower {
      private:
        std::mutex M_USER_POWER_MTX;
        std::unordered_map<std::string, UserPowerTable> m_user_power_table{
            {"root", {"root", 0, "root", true, true, true, true}},
            {"live", {"live", 1, "live", false, false, false, false}}};

      private:
        UserPower() = default;
        ~UserPower() = default;
        UserPower(const UserPower &) = delete;
        UserPower &operator=(const UserPower &) = delete;

      public:
        static auto instance() -> UserPower &;
        auto get_power(const std::string &username_) -> UserPowerTable;
        auto add_user(const std::string &username_, const UserPowerTable &power_) -> bool;
    };

} // namespace ruac::usersystem

#endif // RUAC_USERPOWER_HPP
