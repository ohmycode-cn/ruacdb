/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_kernel.hpp
 * Source File : src/kernel/object/ruac_object_kernel.cpp
 *
 * File Function Description:
 * Singleton kernel object that manages database instances.
 * Provides safe copy access to database collections.
 *
 */

#pragma once
#ifndef RUAC_OBJECT_KERNEL_HPP
#define RUAC_OBJECT_KERNEL_HPP

#include "kernel/core/ruac_data.hpp"
#include <vector>

namespace ruac::kernel::object {
    /**
     * @brief Singleton kernel object managing database instances.
     */
    class Kernel {
      private:
        Kernel() = default;
        ~Kernel() = default;
        Kernel(const Kernel &) = delete;
        Kernel &operator=(const Kernel &) = delete;
        std::vector<ruac::kernel::core::data::Database> m_databases;

      public:
        static auto obitan() -> Kernel &;
        auto getdbs() -> std::vector<ruac::kernel::core::data::Database>;
    }; // Kernel

} // namespace ruac::kernel::object

#endif // RUAC_OBJECT_KERNEL_HPP
