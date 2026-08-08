/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_prexec.hpp
 * src/syntax_lite/tree/ruac_prexec.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_PREXEC_HPP
#define RUAC_PREXEC_HPP

#include "syntax_lite/tree/node/ruac_nodeproc.hpp" // IWYU pragma: keep
#include <memory>

namespace ruac::syntax_lite::tree {

    struct PrExecNodeList {
        node::CreateDatabase M_NODE_CREATE_DATABASE;
        node::CreateTable M_NODE_CREATE_TABLE;
        node::UseDatabase M_NODE_USE_DATABASE;
        node::ShowDatabases M_NODE_SHOW_DATABASES;
        node::ShowTables M_NODE_SHOW_TABLES;
    };

    class PrExec {
      private:
        std::unique_ptr<PrExecNodeList> M_EXEC_NODE_LIST;

      public:
        PrExec();
        ~PrExec() = default;

      public:
        auto get_execute_node_list() const -> const PrExecNodeList &;
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_PREXEC_HPP
