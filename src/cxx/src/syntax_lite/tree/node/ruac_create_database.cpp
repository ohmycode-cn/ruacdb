/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_database.hpp
 * src/syntax_lite/tree/node/ruac_create_database.cpp
 */

#include "syntax_lite/tree/node/ruac_create_database.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "kernel/ruac_controller_table.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac::syntax_lite::tree::node {

    auto CreateDatabase::exist_database(const std::string &name) -> bool {
        auto &controller = ruac::kernel::ControllerTable::instance().get_controller(0);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.getTrackStrategy());
        return track->getKernel().existDatabase(name);
    }

    void CreateDatabase::create_database(const std::string &name, bool in_advance_check) {
        if (in_advance_check && exist_database(name)) {
            std::stringstream ss;
            ss << "Error: Database '" << name << "' already exists";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }
        auto &controller = ruac::kernel::ControllerTable::instance().get_controller(0);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.getTrackStrategy());
        track->getKernel().addDatabase(name, 0, 0);
    }

} // namespace ruac::syntax_lite::tree::node
