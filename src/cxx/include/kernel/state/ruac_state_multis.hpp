/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/state/ruac_state_multis.hpp
 * Source File : src/kernel/state/ruac_state_multis.cpp
 *
 * File Function Description:
 * Multi-instance state manager for kernel state operations.
 * Manages the lifecycle of the Kernel instance.
 *
 */

#pragma once
#ifndef RUAC_STATE_MULTIS_HPP
#define RUAC_STATE_MULTIS_HPP

#include "kernel/state/ruac_state_kernel.hpp"

namespace ruac::kernel::state {

    /**
     * @brief Multi-instance state manager for kernel state operations.
     */
    class Multis {
      private:
        Kernel *m_kernel{nullptr};

        void init();
        void over();

      public:
        Multis();
        ~Multis();
        auto getKernelState() -> Kernel &;
    }; // Multis

} // namespace ruac::kernel::state

#endif // RUAC_STATE_MULTIS_HPP
