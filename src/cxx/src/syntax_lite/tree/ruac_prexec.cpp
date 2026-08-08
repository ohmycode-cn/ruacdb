/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_prexec.hpp
 * src/syntax_lite/tree/ruac_prexec.cpp
 */

#include "syntax_lite/tree/ruac_prexec.hpp"
#include <memory>

namespace ruac::syntax_lite::tree {

    PrExec::PrExec() : M_EXEC_NODE_LIST{std::make_unique<PrExecNodeList>()} {}

    auto PrExec::get_execute_node_list() const -> const PrExecNodeList & {
        return *M_EXEC_NODE_LIST;
    }

} // namespace ruac::syntax_lite::tree
