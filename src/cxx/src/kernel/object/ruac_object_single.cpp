/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/object/ruac_object_single.hpp
 * Source File : src/kernel/object/ruac_object_single.cpp
 *
 * File Function Description:
 * Implementation file for ruac_object_single.hpp.
 *
 */

#include "kernel/object/ruac_object_kernel.hpp"
#include "kernel/object/ruac_object_single.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Constructs a Single object and initializes database copy.
     */
    Single::Single() : m_databases{ruac::kernel::object::Kernel::obitan().getdbs()} {}

    /**
     * @brief Gets the singleton instance of Single.
     * @return Reference to the single Single instance.
     */
    auto Single::obitan() -> Single & {
        static Single instance;
        return instance;
    }

    /**
     * @brief Gets a reference to the database collection.
     * @return Reference to the database vector.
     */
    auto Single::getdbs() -> std::vector<ruac::kernel::core::data::Database> & {
        return m_databases;
    }

} // namespace ruac::kernel::object
