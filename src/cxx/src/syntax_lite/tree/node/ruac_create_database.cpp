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
#include "rstd/messages/ruac_stdmsg.hpp"
#include "rstd/messages/ruac_stddug.hpp"
#include <syncstream>
#include <iostream>
#include <sstream>

namespace ruac::syntax_lite::tree::node {

    /**
     * @brief Check whether a database with the given name already exists
     *
     * @param name - The database name to look up
     *
     * @return bool - true if the database exists, false otherwise
     *
     * @details Fetches controller 0 from ControllerTable, extracts the
     *          Single track strategy from its variant, and forwards the
     *          query to the underlying kernel's existDatabase().
     *
     */
    auto CreateDatabase::exist_database(const std::string &name) -> bool {
        auto &controller = ruac::kernel::ControllerTable::instance().get_controller(0);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.getTrackStrategy());
        return track->getKernel().existDatabase(name);
    }

    /**
     * @brief Create a database, optionally guarded by an existence check
     *
     * @param name - The database name to create
     * @param in_advance_check - When true, abort if the database already exists
     *
     * @details Prints a debug trace via StdMsg/StdDug on entry. If
     *          in_advance_check is true and exist_database(name) reports the
     *          database already exists, an error message is written to stdout
     *          and the function returns without creating anything. Otherwise
     *          it fetches controller 0, extracts the Single track strategy
     *          and calls addDatabase(name, 0, 0) on the underlying kernel.
     *
     */
    void CreateDatabase::create_database(const std::string &name, bool in_advance_check) {

        // tmp debug line;
        rstd::messages::StdMsg::instance()
            .print(rstd::messages::StdDug::instance()
                       .ostrs(
                           "Class: CreateDatabase",
                           __FILE__,
                           __LINE__));

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
