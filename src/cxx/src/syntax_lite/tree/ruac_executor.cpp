/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_executor.hpp
 * src/syntax_lite/tree/ruac_executor.cpp
 */

#include "syntax_lite/tree/ruac_executor.hpp"

#include <memory>
#include <variant>

namespace ruac::syntax_lite::tree {

    Executor::Executor(int uid_) : m_node_map{std::make_unique<ExecutorNodeMap>(uid_)} {}

    void Executor::dispatch(NodeStore *node_store_) {
        auto &node = node_store_->get_node_tree();
        std::visit([this](auto &arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, node::types::CreateDatabase>) {
                m_node_map->m_create_database.execute(arg.name, arg.if_not_exists);
            } else if constexpr (std::is_same_v<T, node::types::CreateTable>) {
            } else if constexpr (std::is_same_v<T, node::types::UseDatabase>) {
            } else if constexpr (std::is_same_v<T, node::types::ShowDatabases>) {
                m_node_map->m_show_databases.execute(arg.name, arg.if_not_exists);
            } else if constexpr (std::is_same_v<T, node::types::ShowTables>) {
            }
        },
                   node);
    }

} // namespace ruac::syntax_lite::tree
