/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_use_database.hpp
 * src/syntax_lite/tree/node/ruac_use_database.cpp
 */

#include "syntax_lite/tree/node/ruac_use_database.hpp"

namespace ruac::syntax_lite::tree::node {

    /**
     * @brief Construct a UseDatabase handler
     *
     * @param uid_ - User ID for the execution context
     *
     */
    UseDatabase::UseDatabase(int uid_) : m_uid(uid_) {}

} // namespace ruac::syntax_lite::tree::node
