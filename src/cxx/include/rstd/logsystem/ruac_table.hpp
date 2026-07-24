/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_table.hpp
 * src/rstd/logsystem/ruac_table.cpp
 * Description of header file function declaration
 * Table renderer that prints key-value maps as ASCII-formatted tables to stdout.
 *
 */

#pragma once
#ifndef RUAC_TABLE_HPP
#define RUAC_TABLE_HPP

#include "rstd/logsystem/ruac_logtype.hpp"
#include <vector>

namespace ruac::rstd::logsystem {

    /**
     * @brief Parameter list for configuring table headers and data source
     *
     */
    struct TableParamList {
        std::vector<logtype::String> m_table_headers{};
        logtype::StringMap m_strmap{};
    };

    /**
     * @brief Enumeration of supported table data source types
     *
     */
    enum class TableType {
        VECTOR = 0,
        STRMAP
    };

    /**
     * @brief ASCII table renderer that formats key-value data into bordered
     *        rows with dynamic column widths and row count footer
     *
     */
    class Table {
      private:
        TableParamList m_params{};

      private:
        auto print_strmap() -> logtype::String;

      public:
        Table() = default;
        ~Table() = default;

      public:
        void set_param_list(const TableParamList &params = {});
        void print(TableType type);
    };

} // namespace ruac::rstd::logsystem

#endif // RUAC_TABLE_HPP
