/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_prexec.hpp
 * src/syntax_lite/tree/ruac_prexec.cpp
 */

#include "syntax_lite/tree/ruac_prexec.hpp"
#include <variant>
#include <memory>

namespace ruac::syntax_lite::tree {

    PrExec::PrExec() : M_EXEC_NODE_LIST{std::make_unique<PrExecNodeList>()} {}

    void PrExec::dispatcher(SynxList *synx_list_) {
        auto &node = synx_list_->get_node_tree();
        std::visit([this](auto &arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, node::nodelist::CreateDatabase>) {
                M_EXEC_NODE_LIST->M_CREATE_DATABASE.create_database(arg.name, arg.if_not_exists);
            } else if constexpr (std::is_same_v<T, node::nodelist::CreateTable>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::UseDatabase>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::ShowDatabases>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::ShowTables>) {
            }
        },
                   node);
    }

} // namespace ruac::syntax_lite::tree
