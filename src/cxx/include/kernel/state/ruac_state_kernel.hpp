/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/state/ruac_state_kernel.hpp
 * Source File : src/kernel/state/ruac_state_kernel.cpp
 *
 * @brief State tracker holding current database name and table number with getter/setter methods for state management.
 */

#pragma once
#ifndef RUAC_STATE_KERNEL_HPP
#define RUAC_STATE_KERNEL_HPP

#include <string>
#include <unordered_map>

namespace ruac::kernel::state {

    /**
     * @brief Kernel state data structure for tracking current database and table number.
     */
    class Kernel {
      private:
        std::string m_database{"none"};
        std::string m_tbnumber{"0"};
        std::string m_current_user{"live"};
        int m_current_user_id{1};

      public:
        Kernel() = default;
        ~Kernel() = default;

      public:
        auto get_current_database_name() -> std::string &;
        auto get_current_table_number() -> std::string &;
        auto get_current_user() -> std::unordered_map<std::string, int>;
        auto get_current_user_name() -> std::string;
        auto get_current_user_id() -> int;

      public:
        void set_current_database_name(const std::string &name_);
        void set_current_table_number(const int number_);
        void set_current_user(const std::string &username_, const int userid_);
    }; // Kernel

} // namespace ruac::kernel::state

#endif // RUAC_STATE_KERNEL_HPP
