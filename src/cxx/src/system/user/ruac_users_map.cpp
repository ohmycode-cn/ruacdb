/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_users_map.hpp
 * src/system/user/ruac_users_map.cpp
 */

#include "system/user/ruac_group.hpp"
#include "system/user/ruac_group_registry.hpp"
#include "system/user/ruac_id.hpp"
#include "system/user/ruac_users_map.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>
#include <syncstream>
#include <unordered_map>

namespace ruac::system::user {

    /**
     * @brief Convert a PowerCode enum value to its string representation
     *
     * @param code_ - The PowerCode to convert
     *
     * @return const char * - "OK", "NO", "OT", or "??" for unknown values
     *
     */
    auto perm_code_str(PowerCode code_) -> const char * {
        switch (code_) {
        case PowerCode::OK:
            return "OK";
        case PowerCode::NO:
            return "NO";
        case PowerCode::OT:
            return "OT";
        }
        return "??";
    }

    void UsersMap::merge_user_info_locked() {
        auto uid_map = UserId::instance().get_users_map();
        auto ugp_map = UserGroup::instance().get_groups();

        m_max_width_name = 0;
        m_max_width_uid = 0;
        m_max_width_group = 0;
        m_max_width_rd = 0;
        m_max_width_we = 0;
        m_max_width_xe = 0;
        m_max_width_lk = 0;
        m_max_width_os = 0;

        m_usmap.clear();
        for (const auto &[name, uid] : uid_map) {
            const auto git = ugp_map.find(name);
            const std::string &group = (git != ugp_map.end()) ? git->second : G_EMPTY_GROUP;
            const auto rit = G_GROUP_REGISTRY.find(group);
            if (rit == G_GROUP_REGISTRY.end()) {
                m_usmap[name][uid][G_EMPTY_GROUP] = {};
            } else {
                m_usmap[name][uid][group] = rit->second;
            }

            m_max_width_name = std::max(m_max_width_name, name.size());
            m_max_width_uid = std::max(m_max_width_uid, std::to_string(uid).size());
            m_max_width_group = std::max(m_max_width_group, group.size());

            const Permission &p = (rit != G_GROUP_REGISTRY.end()) ? rit->second : Permission{};
            m_max_width_rd = std::max(m_max_width_rd, std::string_view(perm_code_str(p.rp)).size());
            m_max_width_we = std::max(m_max_width_we, std::string_view(perm_code_str(p.wp)).size());
            m_max_width_xe = std::max(m_max_width_xe, std::string_view(perm_code_str(p.xp)).size());
            m_max_width_lk = std::max(m_max_width_lk, std::string_view(perm_code_str(p.lp)).size());
            m_max_width_os = std::max(m_max_width_os, std::string_view(perm_code_str(p.os)).size());
        }
    }

    /**
     * @brief Merge user identity and permission data into the display map
     *
     * @details Acquires M_USERS_MAP_MTX, then fetches the full uid map
     *          from UserId and the full group map from UserGroup. Clears
     *          m_usmap and all column-width trackers. For each user,
     *          looks up their group; if the group exists in
     *          G_GROUP_REGISTRY, stores the group's Permission; otherwise
     *          stores an empty Permission with G_EMPTY_GROUP. Updates
     *          the maximum column widths for name, uid, group, and each
     *          permission code (R/W/X/L/OS) so print_user_info() can align
     *          the table.
     *
     */
    void UsersMap::merge_user_info() {
        std::lock_guard<std::mutex> lock(M_USERS_MAP_MTX);
        merge_user_info_locked();
    }

    /**
     * @brief Build a formatted text table of all users and their permissions
     *
     * @return std::string - The formatted table as a single string
     *
     * @details Acquires M_USERS_MAP_MTX, then constructs a header row
     *          (NAME, UID, GROUP, R, W, X, L, OS) using the column widths
     *          computed by merge_user_info(). Draws a separator line of
     *          dashes, then iterates m_usmap (name to uid to group to
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
           << std::setw(static_cast<int>(m_max_width_rd)) << "READ" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_we)) << "WRITE" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_xe)) << "EXECUTE" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_lk)) << "LINK" << "    "
           << std::left
           << std::setw(static_cast<int>(m_max_width_os)) << "OS"
           << '\n';

        const std::string sep(
            m_max_width_name + m_max_width_uid + m_max_width_group +
                m_max_width_rd + m_max_width_we + m_max_width_xe +
                m_max_width_lk + m_max_width_os +
                36,
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
                       << std::setw(static_cast<int>(m_max_width_rd)) << perm_code_str(perm.rp) << "      "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_we)) << perm_code_str(perm.wp) << "       "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_xe)) << perm_code_str(perm.xp) << "         "
                       << std::left
                       << std::setw(static_cast<int>(m_max_width_lk)) << perm_code_str(perm.lp) << "      "
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

    auto UsersMap::get_users_map(const std::string &user_name_) -> std::unordered_map<std::string, Permission> {
        std::lock_guard<std::mutex> lock(M_USERS_MAP_MTX);
        merge_user_info_locked();
        std::unordered_map<std::string, Permission> perm_map;

        auto itr = m_usmap.find(user_name_);
        if (itr == m_usmap.end()) {
            return perm_map;
        }

        for (const auto &[uid, group_map] : itr->second) {
            for (const auto &[group, perm] : group_map) {
                perm_map[group] = perm;
            }
        }

        return perm_map;
    }

} // namespace ruac::system::user
