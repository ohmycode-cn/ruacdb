/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_single.hpp
 * Source File : src/kernel/track/ruac_track_single.cpp
 *
 * File Function Description:
 * Singleton track manager for kernel track operations.
 * Manages the lifecycle of the Kernel instance.
 *
 */

#pragma once
#ifndef RUAC_TRACK_SINGLE_HPP
#define RUAC_TRACK_SINGLE_HPP

#include "kernel/track/ruac_track_kernel.hpp"

namespace ruac::kernel::track {

    /**
     * @brief Singleton track manager for kernel track operations.
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
