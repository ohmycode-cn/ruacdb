/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_database.hpp
 * src/syntax_lite/tree/node/ruac_create_database.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_CREATE_DATABASE_HPP
#define RUAC_CREATE_DATABASE_HPP

#include <string>

namespace ruac::syntax_lite::tree::node {

    class CreateDatabase {
      private:
        auto exist_database(const std::string &name) -> bool;

      public:
        CreateDatabase() = default;
        ~CreateDatabase() = default;

      public:
        void create_database(const std::string &name, bool in_advance_check = false);
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_CREATE_DATABASE_HPP
