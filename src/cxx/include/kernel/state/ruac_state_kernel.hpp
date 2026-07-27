/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/state/ruac_state_kernel.hpp
 * Source File : src/kernel/state/ruac_state_kernel.cpp
 *
 * File Function Description:
 * Defines the kernel state data structure for tracking current database
 * and table number state in the RUAC database system.
 *
 */

#pragma once
#ifndef RUAC_STATE_KERNEL_HPP
#define RUAC_STATE_KERNEL_HPP

#include <string>

namespace ruac::kernel::state {

    /**
     * @brief Kernel state data structure for tracking current database and table number.
     */
    class Kernel {
      private:
        std::string m_database{"none"};
        std::string m_tbnumber{"0"};

      public:
        Kernel() = default;
        ~Kernel() = default;

        auto getCurrentDatabaseName() -> std::string &;
        auto getCurrentTableNumber() -> std::string &;
        void setCurrentDatabaseName(const std::string &name_);
        void setCurrentTableNumber(const int number_);
    }; // Kernel

} // namespace ruac::kernel::state

#endif // RUAC_STATE_KERNEL_HPP
