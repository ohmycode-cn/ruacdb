/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_kernel.hpp
 * Source File : src/kernel/object/ruac_object_kernel.cpp
 *
 * File Function Description:
 * Implementation file for ruac_object_kernel.hpp.
 *
 */

#include "kernel/object/ruac_object_kernel.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Gets the singleton instance of Kernel.
     * @return Reference to the single Kernel instance.
     */
    auto Kernel::obitan() -> Kernel & {
        static Kernel instance;
        return instance;
    }

    /**
     * @brief Gets a safe copy of all databases.
     * @return Vector containing database copies.
     */
    auto Kernel::getdbs() -> std::vector<ruac::kernel::core::data::Database> {
        return m_databases;
    }

} // namespace ruac::kernel::object
