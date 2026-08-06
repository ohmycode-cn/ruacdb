/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_synxlist.hpp
 * src/syntax_lite/tree/ruac_synxlist.cpp
 */

#include "syntax_lite/tree/ruac_synxlist.hpp"

namespace ruac::syntax_lite::tree {

    auto SynxList::get_node_tree() const -> const decltype(M_NODE_TREE) & {
        std::lock_guard<std::mutex> lock(M_SYNX_LIST_MTX);
        return M_NODE_TREE;
    }

} // namespace ruac::syntax_lite::tree
