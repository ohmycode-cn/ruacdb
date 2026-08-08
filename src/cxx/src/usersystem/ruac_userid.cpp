/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_userid.hpp
 * src/usersystem/ruac_userid.cpp
 */

#include "usersystem/ruac_userid.hpp"
#include <mutex>
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac::usersystem {

    auto UserId::instance() -> UserId & {
        static UserId instance_object;
        return instance_object;
    }

    auto UserId::get_user_id(const std::string &username) -> int {
        std::lock_guard<std::mutex> lock(M_USER_ID_MTX);
        auto itr = m_user_id_table.find(username);
        if (itr != m_user_id_table.end()) {
            return itr->second;
        }
        return -1;
    }

    auto UserId::add_user(const std::string &username_) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_ID_MTX);
        auto itr = m_user_id_table.find(username_);
        if (itr != m_user_id_table.end()) {
            std::stringstream ss;
            ss << "Error: User '" << username_ << "' already exists with ID " << itr->second;
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        };
        m_user_id_table[username_] = static_cast<int>(m_user_id_table.size());
        return true;
    }

} // namespace ruac::usersystem
