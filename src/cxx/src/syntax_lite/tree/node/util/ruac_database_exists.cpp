/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/util/ruac_database_exists.hpp
 * src/syntax_lite/tree/node/util/ruac_database_exists.cpp
 */

#include "kernel/ruac_controller_pipes.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"

namespace ruac::syntax_lite::tree::node::util {

    /**
     * @brief Check whether a database with the given name already exists
     *
     * @param name_ - The database name to look up
     * @param uid_ - The user ID to use for the query
     *
     * @return bool - true if the database exists, false otherwise
     *
     * @details Fetches controller uid_ from ControllerPipes, extracts the
     *          Single track strategy from its variant, and forwards the
     *          query to the underlying kernel's exist_database().
     *
     */
    auto exist_database(const std::string &name_, const int uid_) -> bool {
        auto &track = ruac::kernel::controller::ControllerPipes::get().track(uid_);
        return track.get_kernel().exist_database(name_);
    }

} // namespace ruac::syntax_lite::tree::node::util
