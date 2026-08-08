/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_usergroup.hpp
 * src/usersystem/ruac_usergroup.cpp
 */

#include "usersystem/ruac_usergroup.hpp"
#include <syncstream>
#include <algorithm>
#include <iostream>
#include <sstream>

namespace ruac::usersystem {

    auto UserGroup::instance() -> UserGroup & {
        static UserGroup instance_object;
        return instance_object;
    }

    auto UserGroup::get_group(const std::string &username) -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_GROUP_MTX);
        auto itr = m_user_group_table.find(username);
        if (itr != m_user_group_table.end()) {
            return itr->second;
        }
        return "";
    }

    auto UserGroup::add_group(const std::string &username, const std::string &group) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_GROUP_MTX);
        auto itr = m_user_group_table.find(username);
        if (itr != m_user_group_table.end()) {
            std::stringstream ss;
            ss << "Error: User '" << username << "' already exists in group '"
               << itr->second << "'";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        if (std::find(group_list.begin(), group_list.end(), group) == group_list.end()) {
            std::stringstream ss;
            ss << "Error: Group '" << group << "' is not a valid group";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        m_user_group_table[username] = group;
        return true;
    }

} // namespace ruac::usersystem
