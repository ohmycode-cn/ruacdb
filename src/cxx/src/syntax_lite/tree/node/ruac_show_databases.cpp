/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_show_databases.hpp
 * src/syntax_lite/tree/node/ruac_show_databases.cpp
 */

#include "syntax_lite/tree/node/ruac_show_databases.hpp"
#include "kernel/ruac_controller_table.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"
#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    ShowDatabases::ShowDatabases(int uid_) : m_uid(uid_) {}

    auto ShowDatabases::exist_database(const std::string &name_) -> bool {
        return util::exist_database(name_, m_uid);
    }

    void ShowDatabases::show_database(const std::string &name_, const bool in_advance_check_) {
        if (in_advance_check_) {
            if (!exist_database(name_)) {
                std::osyncstream(std::cout) << "Error: Database '" << name_ << "' does not exist." << std::endl;
                return;
            }
        }
        auto &controller = ruac::kernel::controller::ControllerTable::instance().get_controller(m_uid);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());
        track->get_kernel().show_database(name_);
    }

    void ShowDatabases::show_all_databases() {
        auto &controller = ruac::kernel::controller::ControllerTable::instance().get_controller(m_uid);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());
        track->get_kernel().show_all_databases();
    }

    void ShowDatabases::execute(const std::string &name_, bool in_advance_check_) {
        std::lock_guard<std::mutex> lock(M_SHOW_DATABASES_MTX);
        if (name_ == "*") {
            show_all_databases();
        } else {
            show_database(name_, in_advance_check_);
        }
    }

} // namespace ruac::syntax_lite::tree::node
