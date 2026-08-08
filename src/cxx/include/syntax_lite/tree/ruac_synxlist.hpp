/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_synxlist.hpp
 * src/syntax_lite/tree/ruac_synxlist.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_SYNXLIST_HPP
#define RUAC_SYNXLIST_HPP

#include "syntax_lite/tree/node/ruac_nodelist.hpp"
#include <variant>
#include <mutex>

namespace ruac::syntax_lite::tree {

    class SynxList {
      private:
        mutable std::mutex M_SYNX_LIST_MTX;
        std::variant<
            std::monostate,
            node::nodelist::CreateDatabase,
            node::nodelist::CreateTable,
            node::nodelist::UseDatabase,
            node::nodelist::ShowDatabases,
            node::nodelist::ShowTables>
            M_NODE_TREE;

      public:
        SynxList() = default;
        ~SynxList() = default;

      public:
        void set_node_tree(const decltype(M_NODE_TREE) &node_tree_);
        auto get_node_tree() const -> const decltype(M_NODE_TREE) &;
        void clr_node_tree();
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_SYNXLIST_HPP
