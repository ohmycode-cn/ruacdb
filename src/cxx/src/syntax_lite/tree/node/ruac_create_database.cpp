/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_database.hpp
 * src/syntax_lite/tree/node/ruac_create_database.cpp
 */

#include "syntax_lite/tree/node/kit/ruac_database_exist.hpp"
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
     * @param name_ - The database name to look up
     *
     * @return bool - true if the database exists, false otherwise
     *
     * @details Delegates the lookup to the kit helper
     *          kit::database_exist(), passing uid 0 to target the default
     *          controller.
     *
     */
    auto CreateDatabase::database_exist(const std::string &name_) -> bool {
        return ruac::syntax_lite::tree::node::kit::database_exist(name_, 0);
    }

    /**
     * @brief Create a database, optionally guarded by an existence check
     *
     * @param name_ - The database name to create
     * @param in_advance_check_ - When true, abort if the database already exists
     *
     * @details Prints a debug trace via StdMsg/StdDug on entry. If
     *          in_advance_check is true and exist_database(name) reports the
     *          database already exists, an error message is written to stdout
     *          and the function returns without creating anything. Otherwise
     *          it fetches controller 0, extracts the Single track strategy
     *          and calls add_database(name, 0, 0) on the underlying kernel.
     *
     */
    void CreateDatabase::database_create(const std::string &name_, bool in_advance_check) {

        // tmp debug line;
        rstd::messages::StdMsg::instance()
            .print(rstd::messages::StdDug::instance()
                       .ostrs(
                           "Class: CreateDatabase",
                           __FILE__,
                           __LINE__));

        if (in_advance_check || database_exist(name_)) {
            std::stringstream ss;
            ss << "Error: Database '" << name_ << "' already exists";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }
        auto &controller = ruac::kernel::controller::ControllerTable::instance().get_controller(0);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());
        track->get_kernel().add_database(name_, 0, 0);
    }

    /**
     * @brief Entry point for database creation
     *
     * @param name_ - The database name to create
     *
     * @details Forwards the name to database_create() with the default
     *          in_advance_check argument so that an existence check is
     *          performed before the actual creation.
     *
     */
    void CreateDatabase::interface(const std::string &name_, bool in_advance_check_) {
        database_create(name_, in_advance_check_);
    }

} // namespace ruac::syntax_lite::tree::node
