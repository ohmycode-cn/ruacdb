/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/node/ruac_create_database.hpp
 * src/syntax_lite/tree/node/ruac_create_database.cpp
 */

#include "syntax_lite/tree/node/ruac_create_database.hpp"
#include "kernel/ruac_controller_pipes.hpp"
#include "rlib/ruac_tdebug.hpp"
#include "syntax_lite/tree/node/util/ruac_database_exists.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::syntax_lite::tree::node {

    /**
     * @brief Construct a CreateDatabase handler
     *
     * @param uid_ - User ID for the execution context
     *
     */
    CreateDatabase::CreateDatabase(int uid_) : m_uid(uid_) {}

    /**
     * @brief Check if a database with the given name exists
     *
     * @param name_ - The database name to check
     *
     * @return bool - true if the database exists
     *
     */
    auto CreateDatabase::exist_database(const std::string &name_) -> bool {
        return util::exist_database(name_, m_uid);
    }

    /**
     * @brief Create a new database
     *
     * @param name_ - The database name to create
     *
     * @param in_advance_check_ - When true, skip the existence check
     *
     * @details Acquires M_CREATE_DATABASE_MTX. If in_advance_check_ is false and the
     *          database already exists, prints an error and returns. Otherwise fetches
     *          the controller's track strategy and adds the database to the kernel.
     *
     */
    void CreateDatabase::create_database(const std::string &name_, bool in_advance_check_) {

        {
            auto &u = ruac::rlib::tdebug::Info::get();
            std::string msg{"create_database"};
            auto str = u.fmt("CreateDatabase", "create_database(...)", std::move(msg));
            u.print(str, __FILE__, __LINE__);
        }

        std::lock_guard<std::mutex> lock(M_CREATE_DATABASE_MTX);

        if (name_.empty()) {
            std::stringstream ss;
            ss << "Error: Prohibit passing in empty database names !";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        if (exist_database(name_)) {
            if (in_advance_check_) {
                return;
            }
            std::stringstream ss;
            ss << "Error: Database '" << name_ << "' already exists";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        auto &t = ruac::kernel::controller::ControllerPipes::get().track(m_uid);
        auto &o = ruac::kernel::controller::ControllerPipes::get().object(m_uid);
        t.get_kernel().add_database(name_, 0, 0);
        o.getdbs().push_back({name_, {}, 0, 0});
    }

    /**
     * @brief Execute the create database operation
     *
     * @param name_ - The database name to create
     *
     * @param in_advance_check_ - When true, skip the existence check
     *
     * @details Delegates to create_database().
     *
     */
    void CreateDatabase::execute(const std::string &name_, bool in_advance_check_) {
        create_database(name_, in_advance_check_);
    }

    /**
     * @brief Execute the create database operation for multiple database names
     *
     * @param names_ - The database names to create
     *
     * @param in_advance_check_ - When true, skip the existence check
     *
     * @details Delegates to create_database() for each name in names_.
     *
     */
    void CreateDatabase::execute(const std::vector<std::string> &names_, bool in_advance_check_) {
        for (const auto &name : names_) {
            create_database(name, in_advance_check_);
        }
    }

} // namespace ruac::syntax_lite::tree::node
