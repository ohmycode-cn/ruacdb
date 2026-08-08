/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/kernel/ruac_controller_table.hpp
 * src/kernel/ruac_controller_table.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_CONTROLLER_TABLE_HPP
#define RUAC_CONTROLLER_TABLE_HPP

#include "kernel/ruac_controller.hpp"
#include <unordered_map>

namespace ruac::kernel {

    class ControllerTable {
      private:
        std::unordered_map<int, ruac::kernel::controller::Operation *> m_controller_table;

      private:
        ControllerTable() = default;
        ~ControllerTable() = default;
        ControllerTable(const ControllerTable &) = delete;
        ControllerTable &operator=(const ControllerTable &) = delete;

      public:
        static auto instance() -> ControllerTable &;
        auto set_controller(int uid, ruac::kernel::controller::Operation &controller) -> bool;
        auto get_controller(int uid) -> ruac::kernel::controller::Operation &;
    };

} // namespace ruac::kernel

#endif // RUAC_CONTROLLER_TABLE_HPP
