/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_table.hpp
 * src/syntax_lite/tree/node/ruac_create_table.cpp
 */

#include "kernel/ruac_controller_pipes.hpp"
#include "syntax_lite/tree/node/ruac_create_table.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"
#include "syntax_lite/tree/node/util/ruac_exists_table.hpp"

#include "syntax_lite/tree/node/util/ruac_string_to_rtype.hpp"
#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    /**
     * @brief Construct a CreateTable handler
     *
     * @param uid_ - User ID for the execution context
     *
     */
    CreateTable::CreateTable(int uid_) : m_uid(uid_) {}

    auto CreateTable::exist_database(const std::string &dbname_) -> bool {
        auto &u = ruac::syntax_lite::tree::node::util::exist_database;
        return u(dbname_, m_uid);
    }

    auto CreateTable::exist_table(const TableItem &item_) -> bool {
        auto &u = ruac::syntax_lite::tree::node::util::exist_table;
        return u(item_.dbname, item_.tbname, m_uid);
    }

    void CreateTable::create_table(const TableItem &item_) {

        std::lock_guard<std::mutex> lock(M_CREATE_TABLE_MTX);

        if (!exist_database(item_.dbname)) {
            std::osyncstream(std::cout) << "Error: Database does not exist '" << item_.dbname << "'" << std::endl;
            return;
        }

        if (exist_table(item_)) {
            if (item_.if_not_exists) {
                std::osyncstream(std::cout) << "Error: Table already exists '" << item_.tbname << "'" << std::endl;
            }
            return;
        }

        if (item_.ftypes.size() != item_.fnames.size()) {
            std::osyncstream(std::cout) << "Error: Field types and names do not match" << std::endl;
            return;
        }

        auto &u = ruac::kernel::controller::ControllerPipes::get();
        auto &o = u.object(m_uid);
        auto &t = u.track(m_uid);

        auto rtypes = ruac::syntax_lite::tree::node::util::string_to_rtype(item_.ftypes);
        auto fnames = item_.fnames;

        t.get_kernel().add_table(item_.dbname, item_.tbname, 0, 0);
        for (auto &db : o.getdbs()) {
            if (db.name == item_.dbname) {
                db.table.push_back({item_.tbname, {}, {}, 0, 0});
                auto &tb = db.table.back();
                for (size_t i = 0; i < fnames.size(); ++i) {
                    t.get_kernel().add_field(
                        item_.dbname,
                        item_.tbname,
                        fnames[i],
                        0, 0);
                    tb.fields.push_back({fnames[i], rtypes[i], 0, 0});
                }
                break;
            }
        }
    }

    void CreateTable::execute(const TableItem &item_) {
        exist_table(item_);
    }

} // namespace ruac::syntax_lite::tree::node
