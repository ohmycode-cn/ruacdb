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

#include <string>
#include <vector>
#include <mutex>

namespace ruac::syntax_lite::tree::node {

    struct TableItem {
        std::string dbname;
        std::string tbname;
        std::vector<std::string> ftypes;
        std::vector<std::string> fnames;
        bool if_not_exists{false};
    };

    class CreateTable {
      private:
        std::mutex M_CREATE_TABLE_MTX;
        int m_uid{1};

      private:
        auto exist_database(const std::string &dbname_) -> bool;
        auto exist_table(const TableItem &item_) -> bool;
        void create_table(const TableItem &item_);

      public:
        explicit CreateTable(int uid_ = 1);
        ~CreateTable() = default;

      public:
        void execute(const TableItem &item_);
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_CREATE_TABLE_HPP
