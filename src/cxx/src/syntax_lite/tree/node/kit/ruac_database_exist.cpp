/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/kit/ruac_database_exist.hpp
 * src/syntax_lite/tree/node/kit/ruac_database_exist.cpp
 */

#include "syntax_lite/tree/node/kit/ruac_database_exist.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "kernel/ruac_controller_table.hpp"

namespace ruac::syntax_lite::tree::node::kit {

    /**
     * @brief Check whether a database with the given name already exists
     *
     * @param name_ - The database name to look up
     * @param uid_ - The user ID to use for the query
     *
     * @return bool - true if the database exists, false otherwise
     *
     * @details Fetches controller uid_ from ControllerTable, extracts the
     *          Single track strategy from its variant, and forwards the
     *          query to the underlying kernel's exist_database().
     *
     */
    auto database_exist(const std::string &name_, const int uid_) -> bool {
        auto &controller = ruac::kernel::controller::ControllerTable::instance().get_controller(uid_);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());
        return track->get_kernel().exist_database(name_);
    }

} // namespace ruac::syntax_lite::tree::node::kit
