/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_database.hpp
 * src/syntax_lite/tree/node/ruac_create_database.cpp
 */

#include "syntax_lite/tree/node/ruac_create_database.hpp"
#include "kernel/ruac_controller_table.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"
#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    CreateDatabase::CreateDatabase(int uid_) : m_uid(uid_) {}

    auto CreateDatabase::exist_database(const std::string &name_) -> bool {
        return util::exist_database(name_, m_uid);
    }

    void CreateDatabase::create_database(const std::string &name_, bool in_advance_check_) {
        if (in_advance_check_) {
            if (exist_database(name_)) {
                std::osyncstream(std::cout) << "Error: Database '" << name_ << "' already exists." << std::endl;
                return;
            }
        }
        auto &controller = ruac::kernel::controller::ControllerTable::instance().get_controller(m_uid);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());
        track->get_kernel().create_database(name_);
        std::osyncstream(std::cout) << "Done: Database '" << name_ << "' created." << std::endl;
    }

    void CreateDatabase::execute(const std::string &name_, bool in_advance_check_) {
        std::lock_guard<std::mutex> lock(M_CREATE_DATABASE_MTX);
        create_database(name_, in_advance_check_);
    }

} // namespace ruac::syntax_lite::tree::node
