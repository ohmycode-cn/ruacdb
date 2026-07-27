/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/state/ruac_state_single.hpp
 * Source File : src/kernel/state/ruac_state_single.cpp
 *
 * File Function Description:
 * Singleton state manager for kernel state operations.
 * Manages the lifecycle of the Kernel instance.
 *
 */

#pragma once
#ifndef RUAC_STATE_SINGLE_HPP
#define RUAC_STATE_SINGLE_HPP

#include "kernel/state/ruac_state_kernel.hpp"

namespace ruac::kernel::state {

    /**
     * @brief Singleton state manager for kernel state operations.
     */
    class Single {
      private:
        Kernel *m_kernel{nullptr};

        Single();
        ~Single();
        Single(const Single &) = delete;
        Single &operator=(const Single &) = delete;

        void init();
        void over();

      public:
        static auto obitan() -> Single &;
        auto getKernelState() -> Kernel &;
    }; // Single

} // namespace ruac::kernel::state

#endif // RUAC_STATE_SINGLE_HPP
