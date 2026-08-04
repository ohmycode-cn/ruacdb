/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_single.hpp
 * Source File : src/kernel/track/ruac_track_single.cpp
 *
 * @brief Singleton track manager with static obitan() access wrapping a Kernel pointer with init/over lifecycle management.
 */

#pragma once
#ifndef RUAC_TRACK_SINGLE_HPP
#define RUAC_TRACK_SINGLE_HPP

#include "kernel/track/ruac_track_kernel.hpp"

namespace ruac::kernel::track {

    /**
     * @brief Singleton track manager for kernel track operations.
     *
     * Provides static obitan() access to the single instance.
     * Wraps a Kernel pointer with init/over lifecycle management.
     * Deleted copy constructor and assignment operator enforce
     * the singleton pattern.
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
        auto getKernel() -> Kernel &;
    }; // Single

} // namespace ruac::kernel::track

#endif // RUAC_TRACK_SINGLE_HPP
