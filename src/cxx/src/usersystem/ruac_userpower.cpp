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

    /**
     * @brief Access the singleton instance of UserPower.
     *
     * @return UserPower & - Reference to the static UserPower instance.
     *
     * @details A function-local static object is constructed on first invocation and
     *          its reference is returned on every subsequent call, providing a
     *          thread-safe singleton accessor.
     *
     */
    auto UserPower::instance() -> UserPower & {
        static UserPower instance_object;
        return instance_object;
    }

    /**
     * @brief Look up the power configuration for a given username.
     *
     * @param username_ - Name of the user whose power table is requested.
     *
     * @return UserPowerTable - The stored power configuration, or a default
     *         value-initialized UserPowerTable when the user is not found.
     *
     * @details The internal mutex is held for the duration of the lookup so the
     *          operation is thread-safe. When no entry exists for the user an
     *          empty UserPowerTable is returned.
     *
     */
    auto UserPower::get_power(const std::string &username_) -> UserPowerTable {
        std::lock_guard<std::mutex> lock(M_USER_POWER_MTX);
        auto itr = m_user_power_table.find(username_);
        if (itr != m_user_power_table.end()) {
            return itr->second;
        }
        return {};
    }

    /**
     * @brief Add a power configuration entry for a user.
     *
     * @param username_ - Name of the user to register.
     * @param power_ - Power configuration to associate with the user.
     *
     * @return bool - true if the entry was added; false if the user already
     *                exists.
     *
     * @details The mutex is locked before any access to the table. If the user
     *          already has a configuration an error message is streamed to cout
     *          via std::osyncstream and false is returned; otherwise the pair is
     *          stored and true is returned.
     *
     */
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
