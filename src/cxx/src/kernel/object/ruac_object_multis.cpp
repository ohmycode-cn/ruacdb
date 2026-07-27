/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_multis.hpp
 * Source File : src/kernel/object/ruac_object_multis.cpp
 *
 * File Function Description:
 * Implementation file for ruac_object_multis.hpp.
 *
 */

#include "kernel/object/ruac_object_kernel.hpp"
#include "kernel/object/ruac_object_multis.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Constructs a Multis object and initializes database copy.
     */
    Multis::Multis() : m_databases{ruac::kernel::object::Kernel::obitan().getdbs()} {}

    /**
     * @brief Gets a reference to the database collection.
     * @return Reference to the database vector.
     */
    auto Multis::getdbs() -> std::vector<ruac::kernel::core::data::Database> & {
        return m_databases;
    }

} // namespace ruac::kernel::object
