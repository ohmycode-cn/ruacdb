/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_usersmap.hpp
 * src/usersystem/ruac_usersmap.cpp
 */

#include "usersystem/ruac_usersmap.hpp"
#include "usersystem/ruac_usergroup.hpp"
#include "usersystem/ruac_userid.hpp"
#include <algorithm>
#include <mutex>
#include <sstream>
#include <string_view>
#include <syncstream>
#include <iostream>
#include <iomanip>

namespace ruac::usersystem {

    static auto perm_code_str(UserPowerCode code_) -> const char * {
        switch (code_) {
        case UserPowerCode::OK:
            return "OK";
        case UserPowerCode::NO:
            return "NO";
        case UserPowerCode::OT:
            return "OT";
        }
        return "??";
    }

    void UsersMap::merge_user_info() {
        std::lock_guard<std::mutex> lock(M_USERS_MAP_MTX);
        auto uid_map = ruac::usersystem::UserId::instance().get_users_map();
        auto ugp_map = ruac::usersystem::UserGroup::instance().get_groups();

        m_max_width_name = 0;
        m_max_width_uid = 0;
        m_max_width_group = 0;
        m_max_width_r = 0;
        m_max_width_w = 0;
        m_max_width_x = 0;
        m_max_width_l = 0;

        m_usmap.clear();
        for (const auto &[name, uid] : uid_map) {
            const auto git = ugp_map.find(name);
            const std::string &group = (git != ugp_map.end()) ? git->second : G_EMPTY_GROUP;
            const auto rit = M_GROUP_REGISTRY.find(group);
            if (rit == M_GROUP_REGISTRY.end()) {
                m_usmap[name][uid][G_EMPTY_GROUP] = {};
            } else {
                m_usmap[name][uid][group] = rit->second;
            }

            m_max_width_name = std::max(m_max_width_name, name.size());
            m_max_width_uid = std::max(m_max_width_uid, std::to_string(uid).size());
            m_max_width_group = std::max(m_max_width_group, group.size());

            const Permission &p = (rit != M_GROUP_REGISTRY.end()) ? rit->second : Permission{};
            m_max_width_r = std::max(m_max_width_r, std::string_view(perm_code_str(p.rp)).size());
            m_max_width_w = std::max(m_max_width_w, std::string_view(perm_code_str(p.wp)).size());
            m_max_width_x = std::max(m_max_width_x, std::string_view(perm_code_str(p.xp)).size());
            m_max_width_l = std::max(m_max_width_l, std::string_view(perm_code_str(p.lp)).size());
        }
    }

    auto UsersMap::print_user_info() -> std::string {
        std::lock_guard<std::mutex> lock(M_USERS_MAP_MTX);
        std::stringstream ss;
        ss << std::left
           << std::setw(static_cast<int>(m_max_width_name)) << "NAME" << "  "
           << std::right
           << std::setw(static_cast<int>(m_max_width_uid)) << "UID" << "  "
           << std::left
           << std::setw(static_cast<int>(m_max_width_group)) << "GROUP" << "  "
           << std::left
           << std::setw(static_cast<int>(m_max_width_r)) << "R" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_w)) << "W" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_x)) << "X" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_l)) << "L"
           << '\n';

        const std::string sep(
            m_max_width_name + m_max_width_uid + m_max_width_group +
                m_max_width_r + m_max_width_w + m_max_width_x + m_max_width_l +
                20,
            '-');
        ss << sep << '\n';

        for (const auto &[name, uid_map] : m_usmap) {
            for (const auto &[uid, group_map] : uid_map) {
                for (const auto &[group, perm] : group_map) {
                    ss << std::left
                       << std::setw(static_cast<int>(m_max_width_name)) << name << "  "
                       << std::right
                       << std::setw(static_cast<int>(m_max_width_uid)) << uid << "    "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_group)) << group << "  "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_r)) << perm_code_str(perm.rp) << "    "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_w)) << perm_code_str(perm.wp) << "    "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_x)) << perm_code_str(perm.xp) << "    "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_l)) << perm_code_str(perm.lp);
                    ss << '\n';
                }
            }
        }
        return ss.str();
    }

    void UsersMap::show_users_map() {
        {
            merge_user_info();
        }
        std::osyncstream(std::cout) << print_user_info() << std::endl;
    }

} // namespace ruac::usersystem
