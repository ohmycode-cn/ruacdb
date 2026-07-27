/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_multis.hpp
 * Source File : src/kernel/track/ruac_track_multis.cpp
 *
 * File Function Description:
 * Multi-instance track manager for kernel track operations.
 * Manages the lifecycle of the Kernel instance.
 *
 */

#pragma once
#ifndef RUAC_TRACK_MULTIS_HPP
#define RUAC_TRACK_MULTIS_HPP

#include "kernel/track/ruac_track_kernel.hpp"

namespace ruac::kernel::track {

    /**
     * @brief Multi-instance track manager for kernel track operations.
     */
    class Multis {
      private:
        Kernel *m_kernel{nullptr};

        void init();
        void over();

      public:
        Multis();
        ~Multis();
        auto getKernel() -> Kernel &;
    }; // Multis

} // namespace ruac::kernel::track

#endif // RUAC_TRACK_MULTIS_HPP
