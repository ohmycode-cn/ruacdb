/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_userid.hpp
 * src/usersystem/ruac_userid.cpp
 */

#include "usersystem/ruac_userid.hpp"
#include <iostream>
#include <mutex>
#include <sstream>
#include <syncstream>

namespace ruac::usersystem {

    /**
     * @brief Access the singleton instance of UserId.
     *
     * @return UserId & - Reference to the static UserId instance.
     *
     * @details A function-local static object is constructed on first invocation and
     *          its reference is returned on every subsequent call, providing a
     *          thread-safe singleton accessor.
     *
     */
    auto UserId::instance() -> UserId & {
        static UserId instance_object;
        return instance_object;
    }

    /**
     * @brief Get the current user ID table.
     *
     * @return std::unordered_map<std::string, int> - The current user ID table.
     *
     * @details The mutex is locked before the table is returned to ensure thread safety.
     *
     */
    auto UserId::get_users_map() -> std::unordered_map<std::string, int> {
        std::lock_guard<std::mutex> lock(M_USER_ID_MTX);
        return m_user_id_table;
    }

    /**
     * @brief Look up the numeric id assigned to a user.
     *
     * @param username_ - Name of the user whose id is requested.
     *
     * @return int - The stored user id, or -1 when the user is not found.
     *
     * @details The mutex is locked before the table is searched. When the user is
     *          found the stored id is returned; otherwise -1 is returned to
     *          signal absence.
     *
     */
    auto UserId::get_user_id(const std::string &username) -> int {
        std::lock_guard<std::mutex> lock(M_USER_ID_MTX);
        auto itr = m_user_id_table.find(username);
        if (itr != m_user_id_table.end()) {
            return itr->second;
        }
        return -1;
    }

    /**
     * @brief Look up the name assigned to a user.
     *
     * @param user_id_ - Numeric id of the user whose name is requested.
     *
     * @return std::string - The stored user name, or an empty string when the user is not found.
     *
     * @details The mutex is locked before the table is searched. When the user is
     *          found the stored name is returned; otherwise an empty string is returned
     *          to signal absence.
     *
     */
    auto UserId::get_user_name(int user_id_) -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_ID_MTX);
        for (auto item : m_user_id_table) {
            if (item.second == user_id_) {
                return item.first;
            }
        }
        return "";
    }

    /**
     * @brief Register a new user and assign the next available id.
     *
     * @param username_ - Name of the user to register.
     *
     * @return bool - true if the user was added; false if the user already
     *                exists.
     *
     * @details The mutex is locked before the table is consulted. If the user is
     *          already present an error message including the existing id is
     *          streamed to cout via std::osyncstream and false is returned.
     *          Otherwise the new user is inserted with an id equal to the
     *          current table size and true is returned.
     *
     */
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
