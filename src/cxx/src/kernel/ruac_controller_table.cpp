/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/ruac_controller_table.hpp
 * src/kernel/ruac_controller_table.cpp
 */

#include "kernel/ruac_controller_table.hpp"

namespace ruac::kernel::controller {

    /**
     * @brief Access the singleton instance of ControllerTable.
     *
     * @return ControllerTable & - Reference to the static ControllerTable instance.
     *
     * @details A function-local static object is constructed on first invocation and
     *          its reference is returned on every subsequent call, providing a
     *          thread-safe singleton accessor.
     *
     */
    auto ControllerTable::instance() -> ControllerTable & {
        static ControllerTable instance_object;
        return instance_object;
    }

    /**
     * @brief Register a controller operation for the given uid.
     *
     * @param uid_ - Unique identifier used to look up the controller.
     * @param controller_ - Reference to the controller operation to register.
     *
     * @return bool - true if the controller was stored; false if an entry for the
     *                uid already exists.
     *
     * @details The controller table is searched by uid first; when an existing
     *          entry is found the call returns false without modifying the table.
     *          Otherwise a pointer to the supplied controller is stored under the
     *          uid and the call returns true.
     *
     */
    auto ControllerTable::set_controller(int uid, Operation &controller) -> bool {
        auto itr = m_controller_table.find(uid);
        if (itr != m_controller_table.end()) {
            return false;
        }
        m_controller_table[uid] = &controller;
        return true;
    }

    /**
     * @brief Retrieve the controller operation registered for the given uid.
     *
     * @param uid_ - Unique identifier used to look up the controller.
     *
     * @return Operation & - Reference to the stored controller operation for the uid.
     *
     * @details When the uid is found in the controller table a reference to the
     *          stored controller is returned. If no matching entry exists a
     *          std::runtime_error is thrown describing the missing uid.
     *
     */
    auto ControllerTable::get_controller(int uid) -> Operation & {
        auto itr = m_controller_table.find(uid);
        if (itr != m_controller_table.end()) {
            return *itr->second;
        } else {
            throw std::runtime_error("Controller not found for the given UID");
        }
    }

} // namespace ruac::kernel::controller
