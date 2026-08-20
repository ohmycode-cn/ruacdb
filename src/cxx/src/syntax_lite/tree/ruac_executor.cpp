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

    /**
     * @brief Construct an Executor with node handlers for the given user
     *
     * @param uid_ - User ID for the execution context
     *
     */
    Executor::Executor(int uid_) : m_node_map{std::make_unique<ExecutorNodeMap>(uid_)} {}

    /**
     * @brief Dispatch a parsed node tree to the appropriate handler
     *
     * @param node_store_ - Pointer to the NodeStore containing the parsed node tree
     *
     * @details Uses std::visit to pattern-match the variant held in NodeStore. Routes
     *          CreateDatabase, ShowDatabases, and other node types to their respective
     *          handler's execute() method. Unhandled types are silently ignored.
     *
     */
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
