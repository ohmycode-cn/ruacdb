/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_nodelist.hpp
 * src/syntax_lite/tree/node/ruac_nodelist.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_NODELIST_HPP
#define RUAC_NODELIST_HPP

#include <string>

namespace ruac::syntax_lite::tree::node {

    namespace nodelist {

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

    } // namespace nodelist

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_NODELIST_HPP
