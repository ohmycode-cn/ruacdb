/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_show_databases.hpp
 * src/syntax_lite/tree/node/ruac_show_databases.cpp
 */

#include "kernel/ruac_controller_table.hpp"
#include "kernel/track/ruac_track_single.hpp"
#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "syntax_lite/tree//node//kit/ruac_database_exist.hpp"
#include "syntax_lite/tree/node/ruac_show_databases.hpp"
#include <iostream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    ShowDatabases::ShowDatabases(int uid) : m_uid(uid) {}

    auto ShowDatabases::database_exist(const std::string &name_) -> bool {
        return ruac::syntax_lite::tree::node::kit::database_exist(name_, m_uid);
    }

    void ShowDatabases::database_show(const std::string &name_, const bool in_advance_check_) {

        std::lock_guard<std::mutex> lock(M_SHOW_DATABASES_MTX);

        if (in_advance_check_ || !database_exist(name_)) {
            std::osyncstream(std::cout) << "Error: Database not exist -> '" << name_ << "'" << std::endl;
            return;
        }

        // TODO: show database
        std::osyncstream(std::cout) << "tmp output debug: " << name_ << std::endl;
    }

    void ShowDatabases::database_show_all() {

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
     * @brief Entry point for showing databases
     *
     * @param name_ - The database name to show; "all" or "*" selects all
     *                databases
     * @param in_advance_check_ - When true, skip the existence check before
     *                            showing
     *
     * @details If name_ is "all" or "*", delegates to database_show_all()
     *          to list every database; otherwise forwards both arguments
     *          to database_show().
     *
     */
    void ShowDatabases::interface(const std::string &name_, bool in_advance_check_) {
        // tmp debug line;
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();

        if ("*" == name_ || "all" == name_) {
            constexpr const char *const dugmsg{"Class: ShowDatabases, Func: database_show_all"};
            stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));
            database_show_all();
            return;
        }
        constexpr const char *const dugmsg{"Class: ShowDatabases, Func: database_show"};
        stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));
        database_show(name_, in_advance_check_);
    }

} // namespace ruac::syntax_lite::tree::node
