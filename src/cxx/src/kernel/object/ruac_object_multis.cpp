/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/object/ruac_object_multis.hpp
 * src/kernel/object/ruac_object_multis.cpp
 */

#include "kernel/object/ruac_object_kernel.hpp"
#include "kernel/object/ruac_object_multis.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Constructs a Multis object and initializes database copy.
     */
    Multis::Multis() : m_databases{ruac::kernel::object::Kernel::instance().getdbs()} {}

    /**
     * @brief Gets a reference to the database collection.
     * @return Reference to the database vector.
     */
    auto Multis::getdbs() -> std::vector<ruac::kernel::core::data::Database> & {
        return m_databases;
    }

} // namespace ruac::kernel::object
