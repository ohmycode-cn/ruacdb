/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/ruac_controller_table.hpp
 * src/kernel/ruac_controller_table.cpp
 */

#include "kernel/ruac_controller_table.hpp"

namespace ruac::kernel {

    auto ControllerTable::instance() -> ControllerTable & {
        static ControllerTable instance_object;
        return instance_object;
    }

    auto ControllerTable::set_controller(int uid, ruac::kernel::controller::Operation &controller) -> bool {
        auto itr = m_controller_table.find(uid);
        if (itr != m_controller_table.end()) {
            return false;
        }
        m_controller_table[uid] = &controller;
        return true;
    }

    auto ControllerTable::get_controller(int uid) -> ruac::kernel::controller::Operation & {
        auto itr = m_controller_table.find(uid);
        if (itr != m_controller_table.end()) {
            return *itr->second;
        } else {
            throw std::runtime_error("Controller not found for the given UID");
        }
    }

} // namespace ruac::kernel
