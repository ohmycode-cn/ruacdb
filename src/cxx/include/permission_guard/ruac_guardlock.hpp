/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/permission_guard/ruac_guardlock.hpp
 * src/permission_guard/ruac_guardlock.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_GUARDLOCK_HPP
#define RUAC_GUARDLOCK_HPP

#include <mutex>
#include <string>
#include <string_view>

namespace ruac::permission_guard {

    enum class GuardList {
        SYSTEM = 0,
        ROOT,
        MANAGER,
        VISITOR,
        UNKNOWN,
    };

    class GuardLock {
      private:
        std::mutex M_GUARD_LOCK_MTX;
        bool m_outmsg{false};

      private:
        auto grep(std::string_view group_) -> GuardList;
        auto group_weight(GuardList guard_) -> int;

      public:
        GuardLock() = default;
        ~GuardLock() = default;
        GuardLock(const GuardLock &) = delete;
        GuardLock &operator=(const GuardLock &) = delete;

      public:
        static auto get() -> GuardLock &;
        void output_judgment_lock_message(bool is_lock_);
        auto judgment_lock(const int uid_, GuardList guard_) -> bool;
        void print_message(std::string_view msg_header, std::string_view msg_body);
    };

} // namespace ruac::permission_guard

#endif // RUAC_GUARDLOCK_HPP
