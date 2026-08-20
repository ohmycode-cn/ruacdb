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
#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    CreateDatabase::CreateDatabase(int uid_) : m_uid(uid_) {}

    auto CreateDatabase::exist_database(const std::string &name_) -> bool {
        return util::exist_database(name_, m_uid);
    }

    void CreateDatabase::create_database(const std::string &name_, bool in_advance_check_) {

        // tmp debug line;
        auto &stdmsg = rstd::messages::StdMsg::instance();
        auto &stdbug = rstd::messages::StdDug::instance();
        constexpr const char *const dugmsg{"Class: CreateDatabase, Func: create_database"};
        stdmsg.print(stdbug.ostrs(dugmsg, __FILE__, __LINE__));

        std::lock_guard<std::mutex> lock(M_CREATE_DATABASE_MTX);

        if (in_advance_check_ || exist_database(name_)) {
            std::stringstream ss;
            ss << "Error: Database '" << name_ << "' already exists";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        auto &controller = ruac::kernel::controller::ControllerTable::instance().get_controller(m_uid);
        auto *track = std::get<ruac::kernel::track::Single *>(controller.get_track_strategy());
        track->get_kernel().add_database(name_, 0, 0);
    }

    void CreateDatabase::execute(const std::string &name_, bool in_advance_check_) {
        create_database(name_, in_advance_check_);
    }

} // namespace ruac::syntax_lite::tree::node
