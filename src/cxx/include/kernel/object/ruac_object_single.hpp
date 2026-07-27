/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_single.hpp
 * Source File : src/kernel/object/ruac_object_single.cpp
 *
 * File Function Description:
 * Singleton object manager for kernel object operations.
 * Manages the lifecycle of the Kernel instance.
 *
 */

#pragma once
#ifndef RUAC_OBJECT_SINGLE_HPP
#define RUAC_OBJECT_SINGLE_HPP

#include "kernel/core/ruac_data.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Singleton object manager for kernel object operations.
     */
    class Single {
      private:
        std::vector<ruac::kernel::core::data::Database> m_databases;

        Single();
        ~Single() = default;
        Single(const Single &) = delete;
        Single &operator=(const Single &) = delete;

      public:
        static auto obitan() -> Single &;
        auto getdbs() -> std::vector<ruac::kernel::core::data::Database> &;
    }; // Single

} // namespace ruac::kernel::object

#endif // RUAC_OBJECT_SINGLE_HPP
