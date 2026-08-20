/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_executor.hpp
 * src/syntax_lite/tree/ruac_executor.cpp
 *
 * @brief Defines the Executor class for dispatching parsed syntax nodes to their execution handlers.
 */

#pragma once
#ifndef RUAC_EXECUTOR_HPP
#define RUAC_EXECUTOR_HPP

#include "syntax_lite/tree/node/ruac_node_all.hpp" // IWYU pragma: keep
#include "syntax_lite/tree/ruac_node_store.hpp"
#include <memory>

namespace ruac::syntax_lite::tree {

    struct ExecutorNodeMap {
        node::CreateDatabase m_create_database;
        node::CreateTable m_create_table;
        node::UseDatabase m_use_database;
        node::ShowDatabases m_show_databases;
        node::ShowTables m_show_tables;

        explicit ExecutorNodeMap(int uid_)
            : m_create_database(uid_),
              m_create_table(uid_),
              m_use_database(uid_),
              m_show_databases(uid_),
              m_show_tables(uid_) {}
    };

    class Executor {
      private:
        std::unique_ptr<ExecutorNodeMap> m_node_map;

      public:
        explicit Executor(int uid_ = 1);
        ~Executor() = default;

      public:
        void dispatch(NodeStore *node_store_);
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_EXECUTOR_HPP
