/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_kernel.hpp
 * Source File : src/kernel/object/ruac_object_kernel.cpp
 *
 * @brief Singleton kernel object that manages a vector of Database objects with safe copy access via getdbs().
 */

#pragma once
#ifndef RUAC_OBJECT_KERNEL_HPP
#define RUAC_OBJECT_KERNEL_HPP

#include "kernel/core/ruac_data.hpp"
#include <vector>

namespace ruac::kernel::object {
    /**
     * @brief Singleton kernel object managing database instances.
     *
     * Private constructor and deleted copy semantics enforce the singleton pattern.
     * Manages a vector of Database objects with safe copy access via getdbs(),
     * returning a copy of the database collection rather than a mutable reference.
     */
    class Kernel {
      private:
        Kernel() = default;
        ~Kernel() = default;
        Kernel(const Kernel &) = delete;
        Kernel &operator=(const Kernel &) = delete;
        std::vector<ruac::kernel::core::data::Database> m_databases;

      public:
        static auto instance() -> Kernel &;
        auto getdbs() -> std::vector<ruac::kernel::core::data::Database>;
    }; // Kernel

} // namespace ruac::kernel::object

#endif // RUAC_OBJECT_KERNEL_HPP
