/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_show_tables.hpp
 * src/syntax_lite/tree/node/ruac_show_tables.cpp
 *
 * @brief Defines the ShowTables class as a stub for table listing node processing.
 */

#pragma once
#ifndef RUAC_SHOW_TABLES_HPP
#define RUAC_SHOW_TABLES_HPP

namespace ruac::syntax_lite::tree::node {

    class ShowTables {
      private:
        [[maybe_unused]] int m_uid{1};

      public:
        explicit ShowTables(int uid_ = 1);
        ~ShowTables() = default;
    };

} // namespace ruac::syntax_lite::tree::node

#endif // RUAC_SHOW_TABLES_HPP
