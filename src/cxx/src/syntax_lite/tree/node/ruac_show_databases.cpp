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
#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"

#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    /**
     * @brief Construct a ShowDatabases handler
     *
     * @param uid_ - User ID for the execution context
     *
     */
    ShowDatabases::ShowDatabases(int uid_) : m_uid(uid_) {}

    /**
     * @brief Check if a database with the given name exists
     *
     * @param name_ - The database name to check
     *
     * @return bool - true if the database exists
     *
     */
    auto ShowDatabases::exist_database(const std::string &name_) -> bool {
        return util::exist_database(name_, m_uid);
    }

    /**
     * @brief Show a specific database
     *
     * @param name_ - The database name to display
     *
     * @param in_advance_check_ - When true, skip the existence check
     *
     * @details Acquires M_SHOW_DATABASES_MTX. Prints an error if the database does not exist.
     *
     */
    void ShowDatabases::show_database(const std::string &name_, const bool in_advance_check_) {

        std::lock_guard<std::mutex> lock(M_SHOW_DATABASES_MTX);

        if (in_advance_check_ || !exist_database(name_)) {
            std::osyncstream(std::cout) << "Error: Database not exist -> '" << name_ << "'" << std::endl;
            return;
        }

        // TODO: show database
        std::osyncstream(std::cout) << "tmp output debug: " << name_ << std::endl;
    }

    /**
     * @brief Show all databases
     *
     * @details Acquires M_SHOW_DATABASES_MTX. Checks if any databases exist via the track
     *          kernel, printing an error if none are found.
     *
     */
    void ShowDatabases::show_all_databases() {

        std::lock_guard<std::mutex> lock(M_SHOW_DATABASES_MTX);

        auto &ct = ruac::kernel::controller::ControllerTable::instance();
        auto &controller = ct.get_controller(m_uid);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());

        if (track->get_kernel().empty_database()) {
            std::osyncstream(std::cout) << "Error: Not any database." << std::endl;
            return;
        }

        // TODO: show all databases
        std::osyncstream(std::cout) << "tmp output debug: not implemented." << std::endl;
    }

    /**
     * @brief Execute the show databases operation
     *
     * @param name_ - The target name; '*' or 'all' shows all databases
     *
     * @param in_advance_check_ - When true, skip the existence check
     *
     * @details Routes to show_all_databases() when name_ is '*' or 'all', otherwise
     *          delegates to show_database().
     *
     */
    void ShowDatabases::execute(const std::string &name_, bool in_advance_check_) {
        // tmp debug line;
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();

        if ("*" == name_ || "all" == name_) {
            constexpr const char *const dugmsg{"Class: ShowDatabases, Func: show_all_databases"};
            stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));
            show_all_databases();
            return;
        }
        constexpr const char *const dugmsg{"Class: ShowDatabases, Func: show_database"};
        stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));
        show_database(name_, in_advance_check_);
    }

} // namespace ruac::syntax_lite::tree::node
