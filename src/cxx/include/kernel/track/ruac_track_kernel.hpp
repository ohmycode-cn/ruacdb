/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_kernel.hpp
 * Source File : src/kernel/track/ruac_track_kernel.cpp
 *
 * @brief Defines mapper structs and provides CRUD operations for database, table, row, and field metadata tracking with nested unordered_map storage.
 */

#pragma once
#ifndef RUAC_TRACK_KERNEL_HPP
#define RUAC_TRACK_KERNEL_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

namespace ruac::kernel::track {

    namespace mapper {
        /**
         * @brief Map entry for database metadata.
         *
         * Stores the index, id, and version for a database entry.
         */
        struct DatabasesMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
        /**
         * @brief Map entry for table metadata.
         *
         * Stores the index, id, and version for a table entry.
         */
        struct TablesMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
        /**
         * @brief Map entry for row metadata.
         *
         * Stores the index, id, and version for a row entry.
         */
        struct RowsMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
        /**
         * @brief Map entry for field metadata.
         *
         * Stores the index, id, and version for a field entry.
         */
        struct FieldsMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
    } // namespace mapper

    /**
     * @brief Tracks and manages kernel object metadata.
     *
     * Provides CRUD operations for database, table, row, and field metadata tracking
     * with nested unordered_map storage. Each entity level is stored in a separate
     * unordered_map hierarchy: databases by name, tables by database and table name,
     * rows by database, table, and row id, and fields by database, table, and field name.
     */
    class Kernel {
      public:
        Kernel() = default;
        ~Kernel() = default;

      private:
        uint32_t m_database_name_max_width{0};
        std::unordered_map<std::string, mapper::DatabasesMap> m_database_map;

      private:
        uint32_t m_table_name_max_width{0};
        std::unordered_map<std::string, std::unordered_map<std::string, mapper::TablesMap>> m_table_map;

      private:
        uint32_t m_row_id_max_width{0};
        std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<uint64_t, mapper::RowsMap>>> m_row_map;

      private:
        uint32_t m_field_name_max_width{0};
        std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, mapper::FieldsMap>>> m_field_map;

      public:
        auto empty_database() -> bool;
        auto exist_database(const std::string &database_name_) -> bool;
        void add_database(const std::string &database_name_, uint64_t id_, uint64_t version_);
        void update_database_index(const std::string &database_name_, uint64_t index_);
        void update_database_id(const std::string &database_name_, uint64_t id_);
        void update_database_version(const std::string &database_name_, uint64_t version_);
        void delete_database(const std::string &database_name_);
        auto get_database_index(const std::string &database_name_) -> uint64_t;
        auto get_database_id(const std::string &database_name_) -> uint64_t;
        auto get_database_version(const std::string &database_name_) -> uint64_t;
        auto get_database_name_max_width() -> uint32_t;

      public:
        auto exist_table(const std::string &database_name_, const std::string &table_name_) -> bool;
        void add_table(const std::string &database_name_, const std::string &table_name_, uint64_t id_, uint64_t version_);
        void update_table_index(const std::string &database_name_, const std::string &table_name_, uint64_t index_);
        void update_table_id(const std::string &database_name_, const std::string &table_name_, uint64_t id_);
        void update_table_version(const std::string &database_name_, const std::string &table_name_, uint64_t version_);
        void delete_table(const std::string &database_name_, const std::string &table_name_);
        auto get_table_index(const std::string &database_name_, const std::string &table_name_) -> uint64_t;
        auto get_table_id(const std::string &database_name_, const std::string &table_name_) -> uint64_t;
        auto get_table_version(const std::string &database_name_, const std::string &table_name_) -> uint64_t;
        auto get_table_name_max_width() -> uint32_t;

      public:
        void add_row(const std::string &database_name_, const std::string &table_name_, uint64_t id_, uint64_t version_);
        void update_row_index(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t index_);
        void update_row_id(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t new_id_);
        void update_row_version(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t version_);
        void delete_row(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_);
        auto get_row_index(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t;
        auto get_row_id(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t;
        auto get_row_version(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t;
        auto get_row_id_max_width() -> uint32_t;

      public:
        void add_field(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t id_, uint64_t version_);
        void update_field_index(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t index_);
        void update_field_id(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t id_);
        void update_field_version(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t version_);
        void delete_field(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_);
        auto get_field_index(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t;
        auto get_field_id(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t;
        auto get_field_version(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t;
        auto get_field_name_max_width() -> uint32_t;
    }; // Kernel

} // namespace ruac::kernel::track

#endif // RUAC_TRACK_KERNEL_HPP
