/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/user/ruac_group.hpp
 * src/system/user/ruac_group.cpp
 */
#include "system/user/ruac_group.hpp"
#include "system/user/ruac_group_registry.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::system::user {

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
     * @param username_ - Name of the user whose group is requested.
     *
     * @return std::string - The group name for the user, or an empty string
     *         when no entry exists.
     *
     * @details The mutex is locked before the table is searched. When the
     *          user is found the stored group name is returned; otherwise an
     *          empty string is returned to indicate absence. The returned
     *          group name is guaranteed to exist in G_GROUP_REGISTRY.
     *
     */
    auto UserGroup::get_group(const std::string &username_) -> std::string {
        std::lock_guard<std::mutex> lock(M_USER_GROUP_MTX);
        auto itr = m_user_group_table.find(username_);
        if (itr != m_user_group_table.end()) {
            return itr->second;
        }
        return "";
    }

    /**
     * @brief Check whether a group assignment is valid for a user.
     *
     * @param username_ - Name of the user to check.
     * @param group_ - Name of the group to validate.
     *
     * @return bool - true if the assignment is valid; false if the user
     *                already has a group or the group is not valid.
     *
     * @details The mutex is locked before any check is performed. If the
     *          user already has a group an error message including the
     *          existing group is streamed to cout via std::osyncstream and
     *          false is returned. If the supplied group is not present in
     *          G_GROUP_REGISTRY a second error message is emitted and false
     *          is returned. Only when both checks pass is true returned.
     *
     */
    auto UserGroup::exist_group(const std::string &username_, const std::string &group_) -> bool {
        std::lock_guard<std::mutex> lock(M_USER_GROUP_MTX);
        auto itr = m_user_group_table.find(username_);
        if (itr != m_user_group_table.end()) {
            std::stringstream ss;
            ss << "Error: User '" << username_ << "' already exists in group '"
               << itr->second << "'";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        if (G_GROUP_REGISTRY.find(group_) == G_GROUP_REGISTRY.end()) {
            std::stringstream ss;
            ss << "Error: Group '" << group_ << "' is not a valid group";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @brief Add a group assignment to the internal table.
     *
     * @param username_ - Name of the user to assign the group to.
     * @param group_ - Name of the group to assign; must exist in
     *                 G_GROUP_REGISTRY.
     *
     * @details The mutex is locked before the assignment is stored. If the
     *          user already has a group an error message is streamed to cout via
     *          std::osyncstream and the assignment is not stored. If the
     *          group is not valid in G_GROUP_REGISTRY a second error message is
     *          emitted and the assignment is not stored.
     *
     */
    void UserGroup::add_group(const std::string &username_, const std::string &group_) {
        m_user_group_table[username_] = group_;
    }

} // namespace ruac::system::user
