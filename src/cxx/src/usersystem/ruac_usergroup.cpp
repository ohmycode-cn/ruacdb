/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/usersystem/ruac_usergroup.hpp
 * src/usersystem/ruac_usergroup.cpp
 */
#include "usersystem/ruac_user_group_perm.hpp"
#include "usersystem/ruac_usergroup.hpp"
#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::usersystem {

    /**
     * @brief Access the singleton instance of UserGroup.
     *
     * @return UserGroup & - Reference to the static UserGroup instance.
     *
     * @details A function-local static object is constructed on first invocation and
     *          its reference is returned on every subsequent call, providing a
     *          thread-safe singleton accessor.
     *
     */
    auto UserGroup::instance() -> UserGroup & {
        static UserGroup instance_object;
        return instance_object;
    }

    /**
     * @brief Get the current user-to-group mappings.
     *
     * @return std::unordered_map<std::string, std::string> - A copy of the
     *        internal user-to-group table.
     *
     * @details The mutex is locked before the table is copied to ensure
     *          thread-safety. The copy is then returned to the caller.
     *
     */
    auto UserGroup::get_groups() -> std::unordered_map<std::string, std::string> {
        return m_user_group_table;
    }

    /**
     * @brief Look up the group associated with a user.
     *
     * @param username - Name of the user whose group is requested.
     *
     * @return std::string - The group name for the user, or an empty string
     *         when no entry exists.
     *
     * @details The mutex is locked before the table is searched. When the
     *          user is found the stored group name is returned; otherwise an
     *          empty string is returned to indicate absence. The returned
     *          group name is guaranteed to exist in M_GROUP_REGISTRY.
     *
     */
    auto UserGroup::get_group(const std::string &username) -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_GROUP_MTX);
        auto itr = m_user_group_table.find(username);
        if (itr != m_user_group_table.end()) {
            return itr->second;
        }
        return "";
    }

    /**
     * @brief Assign a group to a user.
     *
     * @param username - Name of the user to assign the group to.
     * @param group - Name of the group to assign; must exist in
     *                M_GROUP_REGISTRY.
     *
     * @return bool - true if the assignment was stored; false if the user
     *                already has a group or the group is not valid.
     *
     * @details The mutex is locked before any check is performed. If the
     *          user already has a group an error message including the
     *          existing group is streamed to cout via std::osyncstream and
     *          false is returned. If the supplied group is not present in
     *          M_GROUP_REGISTRY a second error message is emitted and false
     *          is returned. Only when both checks pass is the mapping stored
     *          and true returned.
     *
     */
    auto UserGroup::add_group(const std::string &username, const std::string &group) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_GROUP_MTX);
        auto itr = m_user_group_table.find(username);
        if (itr != m_user_group_table.end()) {
            std::stringstream ss;
            ss << "Error: User '" << username << "' already exists in group '"
               << itr->second << "'";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        if (M_GROUP_REGISTRY.find(group) == M_GROUP_REGISTRY.end()) {
            std::stringstream ss;
            ss << "Error: Group '" << group << "' is not a valid group";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        m_user_group_table[username] = group;
        return true;
    }

} // namespace ruac::usersystem
