/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/lib/ruac_guard.hpp
 * src/ruacsh/lib/ruac_guard.cpp
 */

#include "usersystem/ruac_usergroup.hpp"
#include "usersystem/ruac_userid.hpp"
#include "ruacsh/lib/ruac_guard.hpp"
#include <syncstream>
#include <iostream>

namespace ruac::ruacsh::lib::guard {

    namespace {
        /**
         * @brief Assign a weight to a group name based on its priority
         *
         * @param group_ - Name of the group to assign a weight to
         *
         * @return int - Weight value for the group, 0 for "root", -1 for "manager", -2 for "visitor", -3 for any other group
         *
         * @details This function is used to compare the priority of two groups. "root" has the highest priority, followed by "manager" and "visitor".
         *
         */
        auto group_weight(const std::string &group_) -> int {
            if ("root" == group_) {
                return 0;
            } else if ("manager" == group_) {
                return -1;
            } else if ("visitor" == group_) {
                return -2;
            }
            return -3;
        }
    } // namespace

    /**
     * @brief Verify that the current user's group meets a required priority
     *
     * @param uid_ - The user id to check
     * @param msg_ - Error message text printed when the check fails and
     *               out_msg_ is true
     * @param guard_group_ - Name of the minimum-priority group required
     *                       (e.g. "root", "manager", "visitor")
     * @param out_msg_ - When true, the failure message is flushed to
     *                   stdout via std::osyncstream
     *
     * @return bool - true if the user's group weight is >= the required
     *                group's weight; false otherwise
     *
     * @details Resolves uid_ to a user name via UserId, then looks up
     *          the user's group via UserGroup. Compares group weights
     *          using group_weight(): root=0, manager=-1, visitor=-2,
     *          others=-3. The check passes when the user's weight is
     *          less than or equal to (i.e. higher or equal priority than)
     *          the guard group's weight. If the check fails and out_msg_
     *          is set, msg_ is printed.
     *
     */
    auto uid_permission_guard(const int uid_, const std::string &msg_, const std::string &guard_group_, bool out_msg_) -> bool {
        auto u = uid_;
        auto user_name = ruac::usersystem::UserId::instance().get_user_name(u);
        auto user_group = ruac::usersystem::UserGroup::instance().get_group(user_name);
        if (group_weight(guard_group_) > group_weight(user_group)) {
            if (out_msg_) {
                std::osyncstream(std::cout) << msg_ << std::endl;
            }
            return false;
        }
        return true;
    }

} // namespace ruac::ruacsh::lib::guard
