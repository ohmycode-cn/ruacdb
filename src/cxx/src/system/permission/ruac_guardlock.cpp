/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/system/permission/ruac_guardlock.hpp
 * src/system/permission/ruac_guardlock.cpp
 */

#include "system/permission/ruac_guardlock.hpp"
#include "system/user/ruac_group.hpp"
#include "system/user/ruac_id.hpp"

#include <iostream>
#include <syncstream>

namespace ruac::system::permission {

    auto GuardLock::get() -> GuardLock & {
        static GuardLock instance;
        return instance;
    }
    auto GuardLock::grep(std::string_view group_) -> GuardList {
        if ("syst" == group_) {
            return GuardList::SYSTEM;
        } else if ("root" == group_) {
            return GuardList::ROOT;
        } else if ("manager" == group_) {
            return GuardList::MANAGER;
        } else if ("visitor" == group_) {
            return GuardList::VISITOR;
        }
        return GuardList::UNKNOWN;
    }

    auto GuardLock::group_weight(GuardList guard_) -> int {
        switch (guard_) {
        case GuardList::SYSTEM:
            return 0;
        case GuardList::ROOT:
            return -1;
        case GuardList::MANAGER:
            return -2;
        case GuardList::VISITOR:
            return -3;
        default:
            return -4;
        }
    }

    void GuardLock::output_judgment_lock_message(bool is_lock_) {
        if (m_outmsg) {
            if (is_lock_) {
                std::osyncstream(std::cout) << "[LOCK] Permission denied" << std::endl;
            } else {
                std::osyncstream(std::cout) << "[LOCK] Permission granted" << std::endl;
            }
        }
    }

    auto GuardLock::judgment_lock(const int uid_, GuardList guard_) -> bool {
        std::lock_guard<std::mutex> lock(M_GUARD_LOCK_MTX);
        auto u = uid_;
        auto user_name = ruac::system::user::UserId::instance().get_user_name(u);
        auto user_group = ruac::system::user::UserGroup::instance().get_group(user_name);
        if (group_weight(guard_) > group_weight(grep(user_group))) {
            return false;
        }
        return true;
    }

    void GuardLock::print_message(std::string_view msg_header, std::string_view msg_body) {
        std::lock_guard<std::mutex> lock(M_GUARD_LOCK_MTX);
        if (m_outmsg) {
            std::osyncstream(std::cout) << msg_header << msg_body << std::endl;
        }
    }

} // namespace ruac::system::permission
