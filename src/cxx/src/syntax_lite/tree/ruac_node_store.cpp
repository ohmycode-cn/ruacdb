/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_node_store.hpp
 * src/syntax_lite/tree/ruac_node_store.cpp
 */

#include "syntax_lite/tree/ruac_node_store.hpp"

namespace ruac::syntax_lite::tree {

    void NodeStore::set_node_tree(const decltype(m_node_tree) &node_tree_) {
        std::lock_guard<std::mutex> lock(M_NODE_STORE_MTX);
        m_node_tree = node_tree_;
    }

    auto NodeStore::get_node_tree() const -> const decltype(m_node_tree) & {
        std::lock_guard<std::mutex> lock(M_NODE_STORE_MTX);
        return m_node_tree;
    }

    void NodeStore::clr_node_tree() {
        std::lock_guard<std::mutex> lock(M_NODE_STORE_MTX);
        m_node_tree = std::monostate();
    }

} // namespace ruac::syntax_lite::tree
