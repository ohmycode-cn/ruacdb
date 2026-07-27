/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_kernel.hpp
 * Source File : src/kernel/track/ruac_track_kernel.cpp
 *
 * File Function Description:
 * Tracks and manages kernel object metadata.
 * Provides CRUD operations for databases, tables, rows, and fields.
 *
 */

#pragma once
#ifndef RUAC_TRACK_KERNEL_HPP
#define RUAC_TRACK_KERNEL_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

namespace ruac::kernel::track {

    namespace mapper {
        struct DatabasesMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
        struct TablesMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
        struct RowsMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
        struct FieldsMap {
            uint64_t m_index{0};
            uint64_t m_id{0};
            uint64_t m_version{0};
        };
    } // namespace mapper

    /**
     * @brief Tracks and manages kernel object metadata.
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
        void addDatabase(const std::string &database_name_, uint64_t id_, uint64_t version_);
        void updateDatabaseIndex(const std::string &database_name_, uint64_t index_);
        void updateDatabaseId(const std::string &database_name_, uint64_t id_);
        void updateDatabaseVersion(const std::string &database_name_, uint64_t version_);
        void deleteDatabase(const std::string &database_name_);
        auto getDatabaseIndex(const std::string &database_name_) -> uint64_t;
        auto getDatabaseId(const std::string &database_name_) -> uint64_t;
        auto getDatabaseVersion(const std::string &database_name_) -> uint64_t;
        auto getDatabaseNameMaxWidth() -> uint32_t;

      public:
        void addTable(const std::string &database_name_, const std::string &table_name_, uint64_t id_, uint64_t version_);
        void updateTableIndex(const std::string &database_name_, const std::string &table_name_, uint64_t index_);
        void updateTableId(const std::string &database_name_, const std::string &table_name_, uint64_t id_);
        void updateTableVersion(const std::string &database_name_, const std::string &table_name_, uint64_t version_);
        void deleteTable(const std::string &database_name_, const std::string &table_name_);
        auto getTableIndex(const std::string &database_name_, const std::string &table_name_) -> uint64_t;
        auto getTableId(const std::string &database_name_, const std::string &table_name_) -> uint64_t;
        auto getTableVersion(const std::string &database_name_, const std::string &table_name_) -> uint64_t;
        auto getTableNameMaxWidth() -> uint32_t;

      public:
        void addRow(const std::string &database_name_, const std::string &table_name_, uint64_t id_, uint64_t version_);
        void updateRowIndex(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t index_);
        void updateRowId(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t new_id_);
        void updateRowVersion(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t version_);
        void deleteRow(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_);
        auto getRowIndex(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t;
        auto getRowId(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t;
        auto getRowVersion(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t;
        auto getRowIdMaxWidth() -> uint32_t;

      public:
        void addField(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t id_, uint64_t version_);
        void updateFieldIndex(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t index_);
        void updateFieldId(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t id_);
        void updateFieldVersion(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t version_);
        void deleteField(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_);
        auto getFieldIndex(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t;
        auto getFieldId(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t;
        auto getFieldVersion(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t;
        auto getFieldNameMaxWidth() -> uint32_t;
    }; // Kernel

} // namespace ruac::kernel::track

#endif // RUAC_TRACK_KERNEL_HPP
