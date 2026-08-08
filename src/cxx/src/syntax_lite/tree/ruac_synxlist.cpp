/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_synxlist.hpp
 * src/syntax_lite/tree/ruac_synxlist.cpp
 */

#include "syntax_lite/tree/ruac_synxlist.hpp"

namespace ruac::syntax_lite::tree {

    /**
     * @brief Store a parsed AST node into the syntax-tree variant
     *
     * @param node_tree_ - Variant holding the parsed statement node (or
     *                     std::monostate to clear a previous result)
     *
     * @details Acquires M_SYNX_LIST_MTX exclusively and replaces
     *          M_NODE_TREE with node_tree_. The parameter accepts the
     *          same variant type that M_NODE_TREE uses; callers may pass
     *          a concrete node struct directly because std::variant has
     *          an implicit converting constructor from each alternative.
     *
     */
    void SynxList::set_node_tree(const decltype(M_NODE_TREE) &node_tree_) {
        std::lock_guard<std::mutex> lock(M_SYNX_LIST_MTX);
        M_NODE_TREE = node_tree_;
    }

    /**
     * @brief Get the current AST node from the syntax-tree variant
     *
     * @return const decltype(M_NODE_TREE) & - Variant holding the parsed statement node
     *
     * @details Acquires M_SYNX_LIST_MTX exclusively and returns M_NODE_TREE.
     *
     */
    auto SynxList::get_node_tree() const -> const decltype(M_NODE_TREE) & {
        std::lock_guard<std::mutex> lock(M_SYNX_LIST_MTX);
        return M_NODE_TREE;
    }

    /**
     * @brief Clear the current AST node from the syntax-tree variant
     *
     * @details Acquires M_SYNX_LIST_MTX exclusively and replaces M_NODE_TREE with
     *          std::monostate.
     *
     */
    void SynxList::clr_node_tree() {
        std::lock_guard<std::mutex> lock(M_SYNX_LIST_MTX);
        M_NODE_TREE = std::monostate();
    }

} // namespace ruac::syntax_lite::tree
