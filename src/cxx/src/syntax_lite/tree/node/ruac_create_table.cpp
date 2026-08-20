/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_table.hpp
 * src/syntax_lite/tree/node/ruac_create_table.cpp
 */

#include "syntax_lite/tree/node/ruac_create_table.hpp"

namespace ruac::syntax_lite::tree::node {

    /**
     * @brief Construct a CreateTable handler
     *
     * @param uid_ - User ID for the execution context
     *
     */
    CreateTable::CreateTable(int uid_) : m_uid(uid_) {}

} // namespace ruac::syntax_lite::tree::node
