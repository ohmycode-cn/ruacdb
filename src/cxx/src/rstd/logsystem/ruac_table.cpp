/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/logsystem/ruac_table.hpp
 * src/rstd/logsystem/ruac_table.cpp
 * Table rendering implementation with ASCII border drawing and column width calculation.
 */

#include "rstd/logsystem/ruac_table.hpp"
#include "rstd/logsystem/ruac_logtype.hpp"
#include <syncstream>
#include <algorithm>
#include <iostream>
#include <sstream>

namespace ruac::rstd::logsystem {

    /**
     * @brief Render the stored StringMap as an ASCII table with borders and aligned columns
     *
     * @return The formatted table string, or empty string if headers are not set
     */
    auto Table::print_strmap() -> logtype::string {
        auto &header = m_params.m_table_headers;
        auto &strmap = m_params.m_strmap;

        if (header.empty()) {
            return "";
        }

        const size_t cols = header.size();

        std::vector<size_t> widths(cols);
        for (size_t i = 0; i < cols; ++i) {
            widths.at(i) = header.at(i).size();
        }
        for (const auto &[key, val] : strmap) {
            widths.at(0) = std::max(widths.at(0), key.size());
            widths.at(1) = std::max(widths.at(1), val.size());
        }

        std::stringstream ss;

        auto line = [&]() -> void {
            ss << "+";
            for (size_t i = 0; i < cols; ++i) {
                ss << std::string(widths.at(i) + 2, '-') << "+";
            }
            ss << "\n";
        };

        auto row_line = [&](const std::vector<logtype::string> &cells) -> void {
            ss << "|";
            for (size_t i = 0; i < cols; ++i) {
                const auto &val = cells.at(i);
                size_t pad = widths.at(i) - val.size();
                ss << " " << val
                   << std::string(pad, ' ') << " |";
            }
            ss << "\n";
        };

        line();
        row_line(header);
        line();

        size_t count = 0;
        for (const auto &[key, val] : strmap) {
            row_line({key, val});
            ++count;
        }

        line();
        ss << count << " row" << (count != 1 ? "s" : "") << " in set\n";

        return ss.str();
    }

    /**
     * @brief Set the table headers and data source for rendering
     *
     * @param params  Configuration containing column headers and StringMap data
     */
    void Table::set_param_list(const TableParamList &params) {
        m_params = params;
    }

    /**
     * @brief Print the table to stdout using osyncstream for thread-safe output
     *
     * @param type  The table data source type to render (currently supports STRMAP)
     */
    auto Table::print(TableType type) -> void {
        switch (type) {
        case TableType::STRMAP: {
            auto result = print_strmap();
            std::osyncstream(std::cout) << result;
            break;
        }
        default:
            break;
        }
    }

    /**
     * @brief Render the stored StringMap as an ASCII table with borders and aligned columns
     *
     * @return The formatted table string, or empty string if headers are not set
     */
    auto Table::print_fmt_string() -> logtype::string {
        return print_strmap();
    }

} // namespace ruac::rstd::logsystem
