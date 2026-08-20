/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/kit/ruac_rsh_run.hpp
 * src/ruacsh/kit/ruac_rsh_run.cpp
 */

#include "rstd/convert/ruac_lowercase.hpp"
#include "rstd/convert/ruac_rmspace.hpp"
#include "rstd/colors/ruac_color26.hpp"
#include "ruacsh/kit/ruac_rsh_run.hpp"
#include "rstd/rshell/filter/ruac_rshfer.hpp"
#include "ruacsh/lib/ruac_guard.hpp"
#include "welcome/ruac_guidance.hpp"
#include <syncstream>
#include <iostream>
#include <string>
#include <vector>

namespace ruac::ruacsh::kit {

    /**
     * @brief Construct an RshRun with exec, filter, and prompt
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Stores the kernel reference, creates a rshell filter
     *          Interface and a RshExec via std::make_unique, and sets
     *          the default prompt to "ruac-db> ".
     *
     */
    RshRun::RshRun(kernel::state::Kernel &kstate_) {

        m_kstate = kstate_;
        m_rshell_filter = std::make_unique<ruac::rstd::rshell::filter::api::Interface>();
        m_rsh_exec = std::make_unique<RshExec>(kstate_);
        m_prompt = "ruac-db> ";
    }

    /**
     * @brief Print the command history to stdout
     *
     * @details Checks manager-group permission; if the user lacks
     *          permission, the guard prints an error and the function
     *          returns. If the history is empty, prints a warning.
     *          Otherwise builds a formatted list with a header and
     *          flushes via std::osyncstream.
     *
     */
    void RshRun::print_history() {
        auto ret = ruac::ruacsh::lib::guard::uid_permission_guard(
            m_kstate.get_current_user_id(),
            "Error: Current user is not enable print history permission !",
            "manager");

        if (ret) {
            return;
        }

        if (m_commands_history.empty()) {
            {
                std::stringstream ss;
                ss << "Warn : History not any records !";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
            return;
        }

        {
            std::stringstream ss;
            ss << "\n";
            ss << "RUACDB LINE HISTORY\n";
            for (const auto &item : m_commands_history) {
                ss << item << "\n";
            }
            std::osyncstream(std::cout) << ss.str() << std::flush;
        }
    }

    /**
     * @brief Clear the command history
     *
     * @details Checks manager-group permission; if the user lacks
     *          permission, the guard prints an error and the function
     *          returns. If the history is empty, prints a warning.
     *          Otherwise clears m_commands_history and prints a
     *          confirmation message.
     *
     */
    void RshRun::clear_history() {

        auto ret = ruac::ruacsh::lib::guard::uid_permission_guard(
            m_kstate.get_current_user_id(),
            "Error: Current user is not enable clear history permission !",
            "manager");

        if (ret) {
            return;
        }

        if (m_commands_history.empty()) {
            {
                std::stringstream ss;
                ss << "Warn : History not any records !";
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
            return;
        }

        {
            m_commands_history.clear();
            std::osyncstream(std::cout) << "Done : History already clear." << std::endl;
        }
    }

    /**
     * @brief Dispatch a command line, handling history commands locally
     *
     * @param line_ - A pre-processed command line
     *
     * @return STAUTS_CODE - The status code from RshExec::exec()
     *
     * @details Intercepts "print history" and "clear history" commands
     *          locally, then delegates all commands (including the
     *          intercepted ones) to m_rsh_exec->exec() for further
     *          processing.
     *
     */
    auto RshRun::exec(const std::string &line_) -> STAUTS_CODE {
        if (line_ == "print history") {
            print_history();
        } else if (line_ == "clear history") {
            clear_history();
        }
        return m_rsh_exec->exec(line_);
    }

    /**
     * @brief Store the runtime shell arguments
     *
     * @param args_ - RshellArgs struct with colour/history/bugfix flags
     *
     * @details Copies the args into m_rshell_args for use by set_prompt().
     *
     */
    void RshRun::set_ragrs(
        const ruac::ruacsh::lib::ragrs::RshellArgs &args_) {
        m_rshell_args = args_;
    }

    /**
     * @brief Configure the shell prompt based on runtime args
     *
     * @details If m_rshell_args.m_enable_ht is false, sets the prompt
     *          to the plain "ruac-db> ". Otherwise constructs a Color26
     *          instance with ce/ht/bf flags and builds a coloured
     *          prompt: red "ruac-db" + green ">".
     *
     */
    void RshRun::set_prompt() {

        auto &agrs = m_rshell_args;

        if (!agrs.m_enable_ht) {
            m_prompt = "ruac-db> ";
            return;
        }

        {
            ruac::rstd::colors::Color26 color(
                agrs.m_enable_ce,
                agrs.m_enable_ht,
                agrs.m_enable_bf);
            m_prompt = color.r("ruac-db") + color.g(">") + " ";
        }
    }

    /**
     * @brief Run the interactive shell read-eval loop
     *
     * @details Prints a welcome banner via guidance::BaseInfo, then
     *          checks m_rsh_exec for null (aborts with a fatal error
     *          if missing). Enters a REPL loop: prints the prompt,
     *          reads a line from stdin, skips empty lines, preprocesses
     *          via rmspace + lowercase, splits into semicolon-separated
     *          commands via m_rshell_filter->rshfer(), applies rmspace
     *          again per line, and dispatches each via exec(). Breaks
     *          when exec() returns NORMAL_EXIT or ABNORMAL_EXIT.
     *
     */
    void RshRun::run() {

        {
            ruac::welcome::guidance::BaseInfoColorParamList color_param_list{
                .m_enable_ce = true,
                .m_enable_ht = false,
                .m_enable_bf = false,
                .m_enable_dp = false,
            };
            ruac::welcome::guidance::BaseInfo bash_info;
            bash_info.init(color_param_list);
            bash_info.show();
        }

        if (nullptr == m_rsh_exec) {
            std::stringstream ss;
            ss << "Fatal: Program error ! Shell exec program lose, please contact the developer !\n";
            ss << "       Position: Module 'ruac::ruacsh::kit'\n";
            ss << "                 |__Class 'RshRun'\n";
            ss << "                    |__Func: 'run()'\n";
            ss << "       Line: " << __LINE__ << "\n";
            ss << "       File: " << __FILE__ << "\n";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        while (true) {

            std::osyncstream(std::cout) << m_prompt;
            std::string lines;
            std::getline(std::cin, lines);

            if (lines.empty()) {
                continue;
            }

            {
                ruac::rstd::convert::rmspace::remove_string_spaces(lines);
                ruac::rstd::convert::lowercase::to_lower_string(lines);
            }

            std::vector<std::string> line_list;
            if (!m_rshell_filter->rshfer(lines, line_list)) {
                continue;
            }

            auto ret{STAUTS_CODE::CONTINUE};
            for (auto &line : line_list) {
                {
                    ruac::rstd::convert::rmspace::remove_string_spaces(line);
                }
                ret = exec(line);
                if (ret == STAUTS_CODE::ABNORMAL_EXIT || ret == STAUTS_CODE::NORMAL_EXIT) {
                    return;
                }
            }
        }
    }

} // namespace ruac::ruacsh::kit
