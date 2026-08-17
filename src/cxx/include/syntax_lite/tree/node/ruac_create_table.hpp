/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_table.hpp
 * src/syntax_lite/tree/node/ruac_create_table.cpp
 *
 * @brief Defines the CreateTable class as a stub for table creation node processing.
 */

#pragma once
#ifndef RUAC_CREATE_TABLE_HPP
#define RUAC_CREATE_TABLE_HPP

namespace ruac::syntax_lite::tree::node {

    class CreateTable {
      private:
        [[maybe_unused]] int m_uid{1};

      public:
        explicit CreateTable(int uid = 1);
        ~CreateTable() = default;
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_CREATE_TABLE_HPP
