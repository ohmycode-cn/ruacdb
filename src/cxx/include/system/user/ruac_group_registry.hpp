/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_group_registry.hpp
 *
 * @brief Authoritative group registry: group_name to base Permission mapping.
 *        The single source of truth for which groups exist and what
 *        default permissions each group grants.
 */

#pragma once
#ifndef RUAC_GROUP_REGISTRY_HPP
#define RUAC_GROUP_REGISTRY_HPP

#include "system/user/ruac_permission.hpp"

#include <string>
#include <unordered_map>

namespace ruac::system::user {

    /**
     * @brief Name of the fallback "empty" group used when a user has no
     *        group assignment. Maps to an all-NO Permission via the
     *        entry below in G_GROUP_REGISTRY.
     */
    inline constexpr const char *G_EMPTY_GROUP{"empty"};

    /**
     * @brief Authoritative group registry: group_name to base Permission.
     *
     * @details Both UserGroup and UserPower reference this map so there
     *          is no duplication.
     *
     *          - system:  full permissions (including system)
     *          - root:    full permissions (read, write, execute, link)
     *          - manager: read + write, no execute/link
     *          - visitor: read only
     *          - empty:   no permissions (fallback for users without a group)
     */
    inline const std::unordered_map<std::string, Permission> G_GROUP_REGISTRY{
        {"syst",
         {
             .rp = PowerCode::OK,
             .wp = PowerCode::OK,
             .xp = PowerCode::OK,
             .lp = PowerCode::OK,
             .os = PowerCode::OK,
         }},
        {"root",
         {
             .rp = PowerCode::OK,
             .wp = PowerCode::OK,
             .xp = PowerCode::OK,
             .lp = PowerCode::OK,
         }},
        {"manager",
         {
             .rp = PowerCode::OK,
             .wp = PowerCode::OK,
             .xp = PowerCode::NO,
             .lp = PowerCode::NO,
         }},
        {"visitor",
         {
             .rp = PowerCode::OK,
             .wp = PowerCode::NO,
             .xp = PowerCode::NO,
             .lp = PowerCode::NO,
         }},
        {G_EMPTY_GROUP,
         {
             .rp = PowerCode::NO,
             .wp = PowerCode::NO,
             .xp = PowerCode::NO,
             .lp = PowerCode::NO,
         }},
    };

} // namespace ruac::system::user

#endif // RUAC_GROUP_REGISTRY_HPP
