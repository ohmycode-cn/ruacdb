/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/object/ruac_object_kernel.hpp
 * src/kernel/object/ruac_object_kernel.cpp
 */

#include "kernel/object/ruac_object_kernel.hpp"

namespace ruac::kernel::object {

    /**
     * @brief Gets the singleton instance of Kernel.
     * @return Reference to the single Kernel instance.
     */
    auto Kernel::instance() -> Kernel & {
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
