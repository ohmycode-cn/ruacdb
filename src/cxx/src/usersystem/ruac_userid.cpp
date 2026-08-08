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
