/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_show_databases.hpp
 * src/syntax_lite/tree/node/ruac_show_databases.cpp
 *
 * @brief Defines the ShowDatabases class for displaying databases with thread-safe access.
 */

#pragma once
#ifndef RUAC_SHOW_DATABASES_HPP
#define RUAC_SHOW_DATABASES_HPP

#include "syntax_lite/tree/node/fmt/ruac_format_row.hpp"
#include "syntax_lite/tree/node/fmt/ruac_format_col.hpp"

#include <mutex>
#include <string>
#include <memory>

namespace ruac::syntax_lite::tree::node {

    class ShowDatabases {
      private:
        std::mutex M_SHOW_DATABASES_MTX;
        [[maybe_unused]] int m_uid{1};
        std::unique_ptr<ruac::syntax_lite::tree::node::fmt::FormatRow> m_frow;
        std::unique_ptr<ruac::syntax_lite::tree::node::fmt::FormatCol> m_fcol;

      private:
        auto exist_database(const std::string &name_) -> bool;
        void show_database(const std::string &name_, const bool in_advance_check_ = false);
        void show_all_databases();

      public:
        explicit ShowDatabases(int uid_ = 1);
        ~ShowDatabases() = default;

      public:
        void execute(const std::string &name_, bool in_advance_check_ = false);
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_SHOW_DATABASES_HPP
