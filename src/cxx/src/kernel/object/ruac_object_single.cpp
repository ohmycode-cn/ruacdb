/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/object/ruac_object_single.hpp
 * src/kernel/object/ruac_object_single.cpp
 */

#include "kernel/object/ruac_object_kernel.hpp"
#include "kernel/object/ruac_object_single.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Constructs a Single object and initializes database copy.
     */
    Single::Single() : m_databases{ruac::kernel::object::Kernel::instance().getdbs()} {}

    /**
     * @brief Gets the singleton instance of Single.
     * @return Reference to the single Single instance.
     */
    auto Single::instance() -> Single & {
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
