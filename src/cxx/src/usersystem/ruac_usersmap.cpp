/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_usersmap.hpp
 * src/usersystem/ruac_usersmap.cpp
 */

#include "usersystem/ruac_usergroup.hpp"
#include "usersystem/ruac_userid.hpp"
#include "usersystem/ruac_usersmap.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>
#include <syncstream>

namespace ruac::usersystem {

    /**
     * @brief Convert a UserPowerCode enum value to its string representation
     *
     * @param code_ - The UserPowerCode to convert
     *
     * @return const char * - "OK", "NO", "OT", or "??" for unknown values
     *
     */
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

    /**
     * @brief Merge user identity and permission data into the display map
     *
     * @details Acquires M_USERS_MAP_MTX, then fetches the full uid map
     *          from UserId and the full group map from UserGroup. Clears
     *          m_usmap and all column-width trackers. For each user,
     *          looks up their group; if the group exists in
     *          M_GROUP_REGISTRY, stores the group's Permission; otherwise
     *          stores an empty Permission with G_EMPTY_GROUP. Updates
     *          the maximum column widths for name, uid, group, and each
     *          permission code (R/W/X/L/OS) so print_user_info() can align
     *          the table.
     *
     */
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
        m_max_width_os = 0;

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
            m_max_width_os = std::max(m_max_width_os, std::string_view(perm_code_str(p.os)).size());
        }
    }

    /**
     * @brief Build a formatted text table of all users and their permissions
     *
     * @return std::string - The formatted table as a single string
     *
     * @details Acquires M_USERS_MAP_MTX, then constructs a header row
     *          (NAME, UID, GROUP, R, W, X, L, OS) using the column widths
     *          computed by merge_user_info(). Draws a separator line of
     *          dashes, then iterates m_usmap (name → uid → group →
     *          Permission) printing each user as a formatted row with
     *          std::setw alignment. Returns the entire table as a string.
     *
     */
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
           << std::setw(static_cast<int>(m_max_width_l)) << "L" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_os)) << "OS"
           << '\n';

        const std::string sep(
            m_max_width_name + m_max_width_uid + m_max_width_group +
                m_max_width_r + m_max_width_w + m_max_width_x +
                m_max_width_l + m_max_width_os +
                24,
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
                       << std::setw(static_cast<int>(m_max_width_l)) << perm_code_str(perm.lp) << "    "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_os)) << perm_code_str(perm.os);
                    ss << '\n';
                }
            }
        }
        return ss.str();
    }

    /**
     * @brief Merge and print the full users map to stdout
     *
     * @details Calls merge_user_info() to populate the internal map,
     *          then calls print_user_info() to build the formatted
     *          table and flushes it to stdout via std::osyncstream.
     *
     */
    void UsersMap::show_users_map() {
        {
            merge_user_info();
        }
        std::osyncstream(std::cout) << print_user_info() << std::endl;
    }

} // namespace ruac::usersystem
