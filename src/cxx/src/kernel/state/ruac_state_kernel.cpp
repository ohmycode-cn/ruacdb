/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/state/ruac_state_kernel.hpp
 * Source File : src/kernel/state/ruac_state_kernel.cpp
 *
 * File Function Description:
 * Implementation file for ruac_state_kernel.hpp.
 *
 */

#include "kernel/state/ruac_state_kernel.hpp"

namespace ruac::kernel::state {

    /**
     * @brief Gets the current database name.
     * @return Reference to the current database name string.
     */
    auto Kernel::get_current_database_name() -> std::string & {
        return m_database;
    }

    /**
     * @brief Gets the current table number.
     * @return Reference to the current table number string.
     */
    auto Kernel::get_current_table_number() -> std::string & {
        return m_tbnumber;
    }

    /**
     * @brief Gets the current user.
     * @return Unordered map containing the current user's username and ID.
     */
    auto Kernel::get_current_user() -> std::unordered_map<std::string, int> {
        return {{m_current_user, m_current_user_id}};
    }

    /**
     * @brief Gets the current user name.
     * @return The current user name string.
     */
    auto Kernel::get_current_user_name() -> std::string {
        return m_current_user;
    }

    /**
     * @brief Gets the current user id.
     * @return The current user id integer.
     */
    auto Kernel::get_current_user_id() -> int {
        return m_current_user_id;
    }

    /**
     * @brief Sets the current database name.
     * @param name_ The new database name to set.
     */
    void Kernel::set_current_database_name(const std::string &name_) {
        m_database = name_;
    }

    /**
     * @brief Sets the current table number.
     * @param number_ The new table number to set.
     */
    void Kernel::set_current_table_number(const int number_) {
        m_tbnumber = std::to_string(number_);
    }

    /**
     * @brief Sets the current user.
     * @param username_ The new username to set.
     * @param userid_ The new user ID to set.
     */
    void Kernel::set_current_user(const std::string &username_, const int userid_) {
        m_current_user = username_;
        m_current_user_id = userid_;
    }

} // namespace ruac::kernel::state
