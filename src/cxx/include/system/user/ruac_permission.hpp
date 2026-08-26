/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_permission.hpp
 * src/system/user/ruac_permission.cpp
 *
 * @brief Permission model: PowerCode enum and Permission struct.
 */

#pragma once
#ifndef RUAC_PERMISSION_HPP
#define RUAC_PERMISSION_HPP

namespace ruac::system::user {

    enum class PowerCode {
        NO = 0, // No      Permission
        OK = 1, // Have    Permission
        OT = 2  // Unknown Permission
    };

    /**
     * @brief A set of permission flags (read, write, execute, link, system).
     *
     * @details Used as a group-level default permission. When merging,
     *          the group default takes precedence for any field that is
     *          not PowerCode::OT (Unknown).
     */
    struct Permission {
        PowerCode rp{PowerCode::NO}; // Read    Permission
        PowerCode wp{PowerCode::NO}; // Write   Permission
        PowerCode xp{PowerCode::NO}; // Execute Permission
        PowerCode lp{PowerCode::NO}; // Link    Permission
        // All users do not have this permission, which is for development and debugging purposes only
        PowerCode os{PowerCode::NO}; // System  Permission
    };

} // namespace ruac::system::user

#endif // RUAC_PERMISSION_HPP
