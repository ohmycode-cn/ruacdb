/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-09
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/core/ruac_data.hpp
 * Source File : src/kernel/core/ruac_data.cpp
 * 
 * File Function Description:
 * Defines core data structures (Field, Row, Table, Database) for the RUAC
 * database system, providing schema definitions with versioning and identification.
 * 
 */

#pragma once
#ifndef RUAC_DATA_HPP
#define RUAC_DATA_HPP

#include "kernel/core/ruac_type.hpp"
#include "kernel/core/ruac_vals.hpp"
#include <vector>

namespace ruac::kernel::core {

    namespace data {

        /**
         * @brief Field definition in a table schema.
         *
         * Represents a single column definition with its name, data type,
         * and versioning information.
         */
        struct Field {
            std::string name;                     // field name
            ruac::kernel::core::type::rtype type; // data type
            unsigned long long version;           // schema version
            unsigned long long id;                // unique field identifier
        };

        /**
         * @brief Row data container.
         *
         * Stores a single row of data as a vector of variant values,
         * along with versioning and identification metadata.
         */
        struct Row {
            std::vector<ruac::kernel::core::vals::rval> value; // column values
            unsigned long long version;                        // data version
            unsigned long long id;                             // unique row identifier
        };

        /**
         * @brief Table structure containing rows.
         *
         * Represents a database table with its name, row data,
         * and versioning information.
         */
        struct Table {
            std::string name;           // table name
            std::vector<Field> fields;  // field collection
            std::vector<Row> rows;      // row data
            unsigned long long version; // schema version
            unsigned long long id;      // unique table identifier
        };

        /**
         * @brief Database structure containing tables.
         *
         * Top-level container representing a database with its name,
         * collection of tables, and versioning information.
         */
        struct Database {
            std::string name;           // database name
            std::vector<Table> table;   // table collection
            unsigned long long version; // schema version
            unsigned long long id;      // unique database identifier
        };
    } // namespace data

} // namespace ruac::kernel::core

#endif // RUAC_DATA_HPP