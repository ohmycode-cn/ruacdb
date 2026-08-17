/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_prexec.hpp
 * src/syntax_lite/tree/ruac_prexec.cpp
 *
 * @brief Defines the PrExec class for dispatching parsed syntax nodes to their execution handlers.
 */

#pragma once
#ifndef RUAC_PREXEC_HPP
#define RUAC_PREXEC_HPP

#include "syntax_lite/tree/node/ruac_nodeproc.hpp" // IWYU pragma: keep
#include "syntax_lite/tree/ruac_synxlist.hpp"
#include <memory>

namespace ruac::syntax_lite::tree {

    struct PrExecNodeList {
        node::CreateDatabase M_CREATE_DATABASE;
        node::CreateTable M_CREATE_TABLE;
        node::UseDatabase M_USE_DATABASE;
        node::ShowDatabases M_SHOW_DATABASES;
        node::ShowTables M_SHOW_TABLES;

        explicit PrExecNodeList(int uid)
            : M_CREATE_DATABASE(uid),
              M_CREATE_TABLE(uid),
              M_USE_DATABASE(uid),
              M_SHOW_DATABASES(uid),
              M_SHOW_TABLES(uid) {}
    };

    class PrExec {
      private:
        std::unique_ptr<PrExecNodeList> M_EXEC_NODE_LIST;

      public:
        explicit PrExec(int uid = 1);
        ~PrExec() = default;

      public:
        void dispatcher(SynxList *synx_list_);
    };

} // namespace ruac::syntax_lite::tree

#endif // RUAC_PREXEC_HPP
