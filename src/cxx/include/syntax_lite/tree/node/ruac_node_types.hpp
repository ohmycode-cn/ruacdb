/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_node_types.hpp
 *
 * @brief Defines AST node data structures for parsed RUAC statements.
 */

#pragma once
#ifndef RUAC_NODE_TYPES_HPP
#define RUAC_NODE_TYPES_HPP

#include <string>

namespace ruac::syntax_lite::tree::node {

    namespace types {

        struct CreateDatabase {
            std::string name;
            bool if_not_exists{false};
        };

        struct CreateTable {
            std::string name;
            bool if_not_exists{false};
        };

        struct UseDatabase {
            std::string name;
        };

        struct ShowDatabases {
            std::string name;
            bool if_not_exists{false};
        };

        struct ShowTables {
            std::string name;
        };

    } // namespace types

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_NODE_TYPES_HPP
