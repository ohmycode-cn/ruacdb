/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_userpower.hpp
 * src/usersystem/ruac_userpower.cpp
 */

#include "usersystem/ruac_userpower.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac::usersystem {

    auto UserPower::instance() -> UserPower & {
        static UserPower instance_object;
        return instance_object;
    }

    auto UserPower::get_power(const std::string &username_) -> UserPowerTable {
        std::lock_guard<std::mutex> lock(M_USER_POWER_MTX);
        auto itr = m_user_power_table.find(username_);
        if (itr != m_user_power_table.end()) {
            return itr->second;
        }
        return {};
    }

    auto UserPower::add_user(const std::string &username_, const UserPowerTable &power_) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_POWER_MTX);
        auto itr = m_user_power_table.find(username_);
        if (itr != m_user_power_table.end()) {
            std::stringstream ss;
            ss << "Error: User '" << username_ << "' already has power configuration";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        m_user_power_table[username_] = power_;
        return true;
    }

} // namespace ruac::usersystem
