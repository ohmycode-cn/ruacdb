/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/state/ruac_state_kernel.hpp
 * Source File : src/kernel/state/ruac_state_kernel.cpp
 *
 * File Function Description:
 * Implementation file for ruac_state_kernel.hpp.
 *
 */

#include "kernel/state/ruac_state_kernel.hpp"

namespace ruac::kernel::state {

    /**
     * @brief Gets the current database name.
     * @return Reference to the current database name string.
     */
    auto Kernel::getCurrentDatabaseName() -> std::string & {
        return m_database;
    }

    /**
     * @brief Gets the current table number.
     * @return Reference to the current table number string.
     */
    auto Kernel::getCurrentTableNumber() -> std::string & {
        return m_tbnumber;
    }

    /**
     * @brief Sets the current database name.
     * @param name_ The new database name to set.
     */
    void Kernel::setCurrentDatabaseName(const std::string &name_) {
        m_database = name_;
    }

    /**
     * @brief Sets the current table number.
     * @param number_ The new table number to set.
     */
    void Kernel::setCurrentTableNumber(const int number_) {
        m_tbnumber = std::to_string(number_);
    }

} // namespace ruac::kernel::state
