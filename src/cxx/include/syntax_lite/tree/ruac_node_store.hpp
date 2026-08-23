/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_node_store.hpp
 * src/syntax_lite/tree/ruac_node_store.cpp
 *
 * @brief Defines the NodeStore class for holding parsed node trees in a thread-safe variant container.
 */

#pragma once
#ifndef RUAC_NODE_STORE_HPP
#define RUAC_NODE_STORE_HPP

#include "syntax_lite/tree/node/ruac_node_types.hpp"

#include <mutex>
#include <variant>

namespace ruac::syntax_lite::tree {

    class NodeStore {
      private:
        mutable std::mutex M_NODE_STORE_MTX;
        std::variant<
            std::monostate,
            node::types::CreateDatabases,
            node::types::CreateDatabase,
            node::types::CreateTable,
            node::types::UseDatabase,
            node::types::ShowDatabases,
            node::types::ShowTables>
            m_node_tree;

      public:
        NodeStore() = default;
        ~NodeStore() = default;

      public:
        void set_node_tree(const decltype(m_node_tree) &node_tree_);
        auto get_node_tree() const -> const decltype(m_node_tree) &;
        void clr_node_tree();
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_NODE_STORE_HPP
