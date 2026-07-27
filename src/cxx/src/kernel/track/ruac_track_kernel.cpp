/**
 * C/C++ Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * Line Limit: Recommend line breaks at col: 96, force line breaks at col: 120
 * Date Time: 2026-07-01 21:36:00
 * Author: ohmycode-cn(ohcode@163.com)
 * Header File : include/kernel/track/ruac_track_kernel.hpp
 * Source File : src/kernel/track/ruac_track_kernel.cpp
 *
 * File Function Description:
 * Implementation file for ruac_track_kernel.hpp.
 *
 */

#include "kernel/track/ruac_track_kernel.hpp"

namespace ruac::kernel::track {

    /**
     * Adds a new database entry to the tracking map.
     *
     * Args:
     *   database_name_: The name of the database.
     *   id_: The unique identifier for the database.
     *   version_: The version number of the database.
     */
    void Kernel::addDatabase(const std::string &database_name_, uint64_t id_, uint64_t version_) {
        mapper::DatabasesMap map;
        map.m_index = m_database_map.size();
        map.m_id = id_;
        map.m_version = version_;
        m_database_map[database_name_] = map;
        m_database_name_max_width = std::max(m_database_name_max_width, static_cast<uint32_t>(database_name_.size()));
    }

    /**
     * Updates the index of an existing database entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   index_: The new index value.
     */
    void Kernel::updateDatabaseIndex(const std::string &database_name_, uint64_t index_) {
        auto it = m_database_map.find(database_name_);
        if (it != m_database_map.end()) {
            it->second.m_index = index_;
        }
    }

    /**
     * Updates the ID of an existing database entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   id_: The new unique identifier.
     */
    void Kernel::updateDatabaseId(const std::string &database_name_, uint64_t id_) {
        auto it = m_database_map.find(database_name_);
        if (it != m_database_map.end()) {
            it->second.m_id = id_;
        }
    }

    /**
     * Updates the version of an existing database entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   version_: The new version number.
     */
    void Kernel::updateDatabaseVersion(const std::string &database_name_, uint64_t version_) {
        auto it = m_database_map.find(database_name_);
        if (it != m_database_map.end()) {
            it->second.m_version = version_;
        }
    }

    /**
     * Deletes a database and all related data.
     *
     * Args:
     *   database_name_: The name of the database to delete.
     */
    void Kernel::deleteDatabase(const std::string &database_name_) {
        m_database_map.erase(database_name_);
        m_table_map.erase(database_name_);
        m_row_map.erase(database_name_);
        m_field_map.erase(database_name_);
        uint64_t index = 0;
        for (auto &pair : m_database_map) {
            pair.second.m_index = index++;
        }
        m_database_name_max_width = 0;
        for (const auto &pair : m_database_map) {
            m_database_name_max_width = std::max(m_database_name_max_width, static_cast<uint32_t>(pair.first.size()));
        }
    }

    /**
     * Gets the index of a database.
     *
     * Args:
     *   database_name_: The name of the database.
     *
     * Returns:
     *   The index of the database.
     */
    auto Kernel::getDatabaseIndex(const std::string &database_name_) -> uint64_t {
        return m_database_map[database_name_].m_index;
    }

    /**
     * Gets the ID of a database.
     *
     * Args:
     *   database_name_: The name of the database.
     *
     * Returns:
     *   The unique identifier of the database.
     */
    auto Kernel::getDatabaseId(const std::string &database_name_) -> uint64_t {
        return m_database_map[database_name_].m_id;
    }

    /**
     * Gets the version of a database.
     *
     * Args:
     *   database_name_: The name of the database.
     *
     * Returns:
     *   The version number of the database.
     */
    auto Kernel::getDatabaseVersion(const std::string &database_name_) -> uint64_t {
        return m_database_map[database_name_].m_version;
    }

    /**
     * Gets the maximum width of database names.
     *
     * Returns:
     *   The maximum width of database names.
     */
    auto Kernel::getDatabaseNameMaxWidth() -> uint32_t {
        return m_database_name_max_width;
    }

    /**
     * Adds a new table entry to the tracking map.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   id_: The unique identifier for the table.
     *   version_: The version number of the table.
     */
    void Kernel::addTable(const std::string &database_name_, const std::string &table_name_, uint64_t id_, uint64_t version_) {
        mapper::TablesMap map;
        map.m_index = m_table_map[database_name_].size();
        map.m_id = id_;
        map.m_version = version_;
        m_table_map[database_name_][table_name_] = map;
        m_table_name_max_width = std::max(m_table_name_max_width, static_cast<uint32_t>(table_name_.size()));
    }

    /**
     * Updates the index of an existing table entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   index_: The new index value.
     */
    void Kernel::updateTableIndex(const std::string &database_name_, const std::string &table_name_, uint64_t index_) {
        auto db_it = m_table_map.find(database_name_);
        if (db_it != m_table_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                table_it->second.m_index = index_;
            }
        }
    }

    /**
     * Updates the ID of an existing table entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   id_: The new unique identifier.
     */
    void Kernel::updateTableId(const std::string &database_name_, const std::string &table_name_, uint64_t id_) {
        auto db_it = m_table_map.find(database_name_);
        if (db_it != m_table_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                table_it->second.m_id = id_;
            }
        }
    }

    /**
     * Updates the version of an existing table entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   version_: The new version number.
     */
    void Kernel::updateTableVersion(const std::string &database_name_, const std::string &table_name_, uint64_t version_) {
        auto db_it = m_table_map.find(database_name_);
        if (db_it != m_table_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                table_it->second.m_version = version_;
            }
        }
    }

    /**
     * Deletes a table and all related data.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table to delete.
     */
    void Kernel::deleteTable(const std::string &database_name_, const std::string &table_name_) {
        auto db_it = m_table_map.find(database_name_);
        if (db_it != m_table_map.end()) {
            db_it->second.erase(table_name_);
            uint64_t index = 0;
            for (auto &pair : db_it->second) {
                pair.second.m_index = index++;
            }
        }
        auto row_db_it = m_row_map.find(database_name_);
        if (row_db_it != m_row_map.end()) {
            row_db_it->second.erase(table_name_);
        }
        auto field_db_it = m_field_map.find(database_name_);
        if (field_db_it != m_field_map.end()) {
            field_db_it->second.erase(table_name_);
        }
        m_table_name_max_width = 0;
        for (const auto &db_pair : m_table_map) {
            for (const auto &table_pair : db_pair.second) {
                m_table_name_max_width = std::max(m_table_name_max_width, static_cast<uint32_t>(table_pair.first.size()));
            }
        }
    }

    /**
     * Gets the index of a table.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *
     * Returns:
     *   The index of the table.
     */
    auto Kernel::getTableIndex(const std::string &database_name_, const std::string &table_name_) -> uint64_t {
        return m_table_map[database_name_][table_name_].m_index;
    }

    /**
     * Gets the ID of a table.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *
     * Returns:
     *   The ID of the table.
     */
    auto Kernel::getTableId(const std::string &database_name_, const std::string &table_name_) -> uint64_t {
        return m_table_map[database_name_][table_name_].m_id;
    }

    /**
     * Gets the version of a table.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *
     * Returns:
     *   The version number of the table.
     */
    auto Kernel::getTableVersion(const std::string &database_name_, const std::string &table_name_) -> uint64_t {
        return m_table_map[database_name_][table_name_].m_version;
    }

    /**
     * Gets the maximum width of table names.
     *
     * Returns:
     *   The maximum width of table names.
     */
    auto Kernel::getTableNameMaxWidth() -> uint32_t {
        return m_table_name_max_width;
    }

    /**
     * Adds a new row entry to the tracking map.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   id_: The unique identifier for the row.
     *   version_: The version number of the row.
     */
    void Kernel::addRow(const std::string &database_name_, const std::string &table_name_, uint64_t id_, uint64_t version_) {
        mapper::RowsMap map;
        map.m_index = m_row_map[database_name_][table_name_].size();
        map.m_id = id_;
        map.m_version = version_;
        m_row_map[database_name_][table_name_][id_] = map;
        m_row_id_max_width = std::max(m_row_id_max_width, static_cast<uint32_t>(std::to_string(id_).size()));
    }

    /**
     * Updates the index of an existing row entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The ID of the row.
     *   index_: The new index value.
     */
    void Kernel::updateRowIndex(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t index_) {
        auto db_it = m_row_map.find(database_name_);
        if (db_it != m_row_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                auto row_it = table_it->second.find(row_id_);
                if (row_it != table_it->second.end()) {
                    row_it->second.m_index = index_;
                }
            }
        }
    }

    /**
     * Updates the ID of an existing row entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The current ID of the row.
     *   new_id_: The new ID value.
     */
    void Kernel::updateRowId(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t new_id_) {
        auto db_it = m_row_map.find(database_name_);
        if (db_it != m_row_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                auto row_it = table_it->second.find(row_id_);
                if (row_it != table_it->second.end()) {
                    auto data = row_it->second;
                    data.m_id = new_id_;
                    table_it->second.erase(row_it);
                    table_it->second[new_id_] = data;
                }
            }
        }
    }

    /**
     * Updates the version of an existing row entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The ID of the row.
     *   version_: The new version number.
     */
    void Kernel::updateRowVersion(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_, uint64_t version_) {
        auto db_it = m_row_map.find(database_name_);
        if (db_it != m_row_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                auto row_it = table_it->second.find(row_id_);
                if (row_it != table_it->second.end()) {
                    row_it->second.m_version = version_;
                }
            }
        }
    }

    /**
     * Deletes a row and all related data.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The ID of the row to delete.
     */
    void Kernel::deleteRow(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) {
        auto db_it = m_row_map.find(database_name_);
        if (db_it != m_row_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                table_it->second.erase(row_id_);
                uint64_t index = 0;
                for (auto &pair : table_it->second) {
                    pair.second.m_index = index++;
                }
            }
        }
        m_row_id_max_width = 0;
        for (const auto &db_pair : m_row_map) {
            for (const auto &table_pair : db_pair.second) {
                for (const auto &row_pair : table_pair.second) {
                    m_row_id_max_width = std::max(m_row_id_max_width, static_cast<uint32_t>(std::to_string(row_pair.first).size()));
                }
            }
        }
    }

    /**
     * Gets the index of a row.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The ID of the row.
     *
     * Returns:
     *   The index of the row.
     */
    auto Kernel::getRowIndex(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t {
        return m_row_map[database_name_][table_name_][row_id_].m_index;
    }

    /**
     * Gets the ID of a row.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The ID of the row.
     *
     * Returns:
     *   The ID of the row.
     */
    auto Kernel::getRowId(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t {
        return m_row_map[database_name_][table_name_][row_id_].m_id;
    }

    /**
     * Gets the version of a row.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   row_id_: The ID of the row.
     *
     * Returns:
     *   The version number of the row.
     */
    auto Kernel::getRowVersion(const std::string &database_name_, const std::string &table_name_, uint64_t row_id_) -> uint64_t {
        return m_row_map[database_name_][table_name_][row_id_].m_version;
    }

    /**
     * Gets the maximum width of row IDs.
     *
     * Returns:
     *   The maximum width of row IDs.
     */
    auto Kernel::getRowIdMaxWidth() -> uint32_t {
        return m_row_id_max_width;
    }

    /**
     * Adds a new field entry to the tracking map.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *   id_: The unique identifier for the field.
     *   version_: The version number of the field.
     */
    void Kernel::addField(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t id_, uint64_t version_) {
        mapper::FieldsMap map;
        map.m_index = m_field_map[database_name_][table_name_].size();
        map.m_id = id_;
        map.m_version = version_;
        m_field_map[database_name_][table_name_][field_name_] = map;
        m_field_name_max_width = std::max(m_field_name_max_width, static_cast<uint32_t>(field_name_.size()));
    }

    /**
     * Updates the index of an existing field entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *   index_: The new index value.
     */
    void Kernel::updateFieldIndex(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t index_) {
        auto db_it = m_field_map.find(database_name_);
        if (db_it != m_field_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                auto field_it = table_it->second.find(field_name_);
                if (field_it != table_it->second.end()) {
                    field_it->second.m_index = index_;
                }
            }
        }
    }

    /**
     * Updates the ID of an existing field entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *   id_: The new ID value.
     */
    void Kernel::updateFieldId(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t id_) {
        auto db_it = m_field_map.find(database_name_);
        if (db_it != m_field_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                auto field_it = table_it->second.find(field_name_);
                if (field_it != table_it->second.end()) {
                    field_it->second.m_id = id_;
                }
            }
        }
    }

    /**
     * Updates the version of an existing field entry.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *   version_: The new version number.
     */
    void Kernel::updateFieldVersion(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_, uint64_t version_) {
        auto db_it = m_field_map.find(database_name_);
        if (db_it != m_field_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                auto field_it = table_it->second.find(field_name_);
                if (field_it != table_it->second.end()) {
                    field_it->second.m_version = version_;
                }
            }
        }
    }

    /**
     * Deletes a field and all related data.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field to delete.
     */
    void Kernel::deleteField(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) {
        auto db_it = m_field_map.find(database_name_);
        if (db_it != m_field_map.end()) {
            auto table_it = db_it->second.find(table_name_);
            if (table_it != db_it->second.end()) {
                table_it->second.erase(field_name_);
                uint64_t index = 0;
                for (auto &pair : table_it->second) {
                    pair.second.m_index = index++;
                }
            }
        }
        m_field_name_max_width = 0;
        for (const auto &db_pair : m_field_map) {
            for (const auto &table_pair : db_pair.second) {
                for (const auto &field_pair : table_pair.second) {
                    m_field_name_max_width = std::max(m_field_name_max_width, static_cast<uint32_t>(field_pair.first.size()));
                }
            }
        }
    }

    /**
     * Gets the index of a field.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *
     * Returns:
     *   The index of the field.
     */
    auto Kernel::getFieldIndex(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t {
        return m_field_map[database_name_][table_name_][field_name_].m_index;
    }

    /**
     * Gets the ID of a field.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *
     * Returns:
     *   The ID of the field.
     */
    auto Kernel::getFieldId(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t {
        return m_field_map[database_name_][table_name_][field_name_].m_id;
    }

    /**
     * Gets the version of a field.
     *
     * Args:
     *   database_name_: The name of the database.
     *   table_name_: The name of the table.
     *   field_name_: The name of the field.
     *
     * Returns:
     *   The version number of the field.
     */
    auto Kernel::getFieldVersion(const std::string &database_name_, const std::string &table_name_, const std::string &field_name_) -> uint64_t {
        return m_field_map[database_name_][table_name_][field_name_].m_version;
    }

    /**
     * Gets the maximum width of field names.
     *
     * Returns:
     *   The maximum width of field names.
     */
    auto Kernel::getFieldNameMaxWidth() -> uint32_t {
        return m_field_name_max_width;
    }

} // namespace ruac::kernel::track
