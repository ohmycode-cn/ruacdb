/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_multis.hpp
 * Source File : src/kernel/object/ruac_object_multis.cpp
 *
 * File Function Description:
 * Multi-instance object manager for kernel object operations.
 * Manages the lifecycle of the Kernel instance.
 *
 */

#pragma once
#ifndef RUAC_OBJECT_MULTIS_HPP
#define RUAC_OBJECT_MULTIS_HPP

#include "kernel/core/ruac_data.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Multi-instance object manager for kernel object operations.
     */
    class Multis {
      private:
        std::vector<ruac::kernel::core::data::Database> m_databases;

      public:
        Multis();
        ~Multis() = default;

      public:
        auto getdbs() -> std::vector<ruac::kernel::core::data::Database> &;
    }; // Multis

} // namespace ruac::kernel::object

#endif // RUAC_OBJECT_MULTIS_HPP
