/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rlib/ruac_tdebug.hpp
 * src/rlib/ruac_tdebug.cpp
 */

#include "rlib/ruac_tdebug.hpp"

#include "rstd/messages/ruac_stddug.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"

namespace ruac::rlib::tdebug {

    auto Info::innerfmt(std::string &&class_, std::string &&func_) -> std::string & {
    };

    /**
     * @brief Get the singleton Info instance
     *
     * @return Info & - Reference to the static singleton instance
     *
     * @details Uses a function-local static to guarantee a single
     *          instance for the lifetime of the program.
     */
    auto Info::get() -> Info & {
        static Info instance;
        return instance;
    }

    auto fmt(const std::string &class_, const std::string &func_) -> std::string &;
    auto fmt(std::string &&class_, std::string &&func_) -> std::string &;

    /**
     * @brief Print a formatted debug message
     *
     * @param msgs_ - The message content to display
     * @param file_ - The source file name where the debug call originated
     * @param line_ - The source line number where the debug call originated
     *
     * @details Delegates to rstd::messages::StdDug to build a formatted
     *          debug string with file and line information, then outputs
     *          it via rstd::messages::StdMsg::print().
     */
    void Info::print(const std::string &msgs_, const std::string &file_, const int line_) {
        {
            auto &msg{ruac::rstd::messages::StdMsg::instance()};
            auto &dug{ruac::rstd::messages::StdDug::instance()};
            msg.print(dug.ostrs(msgs_, file_, line_), true);
        }
    }

} // namespace ruac::rlib::tdebug
