/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_prexec.hpp
 * src/syntax_lite/tree/ruac_prexec.cpp
 */

#include "syntax_lite/tree/ruac_prexec.hpp"
#include <memory>
#include <variant>

namespace ruac::syntax_lite::tree {

    /**
     * @brief Construct the PrExec and own its node list
     *
     * @param uid - User ID for controller lookup
     *
     * @details Initialises M_EXEC_NODE_LIST via std::make_unique so the
     *          pre-executor holds a fresh PrExecNodeList ready to act on
     *          parsed nodes.
     *
     */
    PrExec::PrExec(int uid) : M_EXEC_NODE_LIST{std::make_unique<PrExecNodeList>(uid)} {}

    /**
     * @brief Dispatch the parsed node tree to its pre-execution handler
     *
     * @param synx_list_ - Pointer to the SynxList holding the parsed node tree
     *
     * @details Retrieves the node_tree variant from synx_list_ and applies
     *          std::visit with a generic lambda. The lambda uses if constexpr
     *          on std::decay_t of the variant alternative to select the
     *          matching handler; currently only CreateDatabase is wired up
     *          (delegated to M_CREATE_DATABASE.create_database), while
     *          CreateTable, UseDatabase, ShowDatabases and ShowTables are
     *          recognised but left as no-ops.
     *
     */
    void PrExec::dispatcher(SynxList *synx_list_) {
        auto &node = synx_list_->get_node_tree();
        std::visit([this](auto &arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, node::nodelist::CreateDatabase>) {
                M_EXEC_NODE_LIST->M_CREATE_DATABASE.interface(arg.name, arg.if_not_exists);
            } else if constexpr (std::is_same_v<T, node::nodelist::CreateTable>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::UseDatabase>) {
            } else if constexpr (std::is_same_v<T, node::nodelist::ShowDatabases>) {
                M_EXEC_NODE_LIST->M_SHOW_DATABASES.interface(arg.name, arg.if_not_exists);
            } else if constexpr (std::is_same_v<T, node::nodelist::ShowTables>) {
            }
        },
                   node);
    }

} // namespace ruac::syntax_lite::tree
