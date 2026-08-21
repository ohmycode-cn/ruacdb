/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_user_group_perm.hpp
 *
 * @brief Shared definitions for user roles, permissions, and the authoritative
 *        group registry used by both UserGroup and UserPower.
 */

#pragma once
#ifndef RUAC_USER_GROUP_PERM_HPP
#define RUAC_USER_GROUP_PERM_HPP

#include <string>
#include <unordered_map>

namespace ruac::usersystem {

    enum class UserPowerCode {
        NO = 0, // No      Permission
        OK = 1, // Have    Permission
        OT = 2  // Unknown Permission
    };

    /**
     * @brief A set of four permission flags (read, write, execute, link).
     *
     * @details Used as a group-level default permission. When merging,
     *          the group default takes precedence for any field that is
     *          not UserPowerCode::OT (Unknown).
     */
    struct Permission {
        UserPowerCode rp{UserPowerCode::NO}; // Read    Permission
        UserPowerCode wp{UserPowerCode::NO}; // Write   Permission
        UserPowerCode xp{UserPowerCode::NO}; // Execute Permission
        UserPowerCode lp{UserPowerCode::NO}; // Link    Permission
    };

    /**
     * @brief Authoritative group registry: group_name → base Permission.
     *
     * @details The single source of truth for which groups exist and what
     *          default permissions each group grants. Both UserGroup and
     *          UserPower reference this map so there is no duplication.
     *
     *          - root:    full permissions (read, write, execute, link)
     *          - manager: read + write, no execute/link
     *          - visitor: read only
     *          - empty:   no permissions (fallback for users without a group)
     */
    /**
     * @brief Name of the fallback "empty" group used when a user has no
     *        group assignment. Maps to an all-NO Permission via the
     *        entry below in M_GROUP_REGISTRY.
     */
    inline constexpr const char *G_EMPTY_GROUP{"empty"};

    inline const std::unordered_map<std::string, Permission> M_GROUP_REGISTRY{
        {"root",
         {
             .rp = UserPowerCode::OK,
             .wp = UserPowerCode::OK,
             .xp = UserPowerCode::OK,
             .lp = UserPowerCode::OK,
         }},
        {"manager",
         {
             .rp = UserPowerCode::OK,
             .wp = UserPowerCode::OK,
             .xp = UserPowerCode::NO,
             .lp = UserPowerCode::NO,
         }},
        {"visitor",
         {
             .rp = UserPowerCode::OK,
             .wp = UserPowerCode::NO,
             .xp = UserPowerCode::NO,
             .lp = UserPowerCode::NO,
         }},
        {G_EMPTY_GROUP,
         {
             .rp = UserPowerCode::NO,
             .wp = UserPowerCode::NO,
             .xp = UserPowerCode::NO,
             .lp = UserPowerCode::NO,
         }},
    };

} // namespace ruac::usersystem

#endif // RUAC_USER_GROUP_PERM_HPP
