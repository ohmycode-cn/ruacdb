/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/core/ruac_run.hpp
 * src/rshell/core/ruac_run.cpp
 */

#include "permission_guard/ruac_guardlock.hpp"
#include "rlib/ruac_tdebug.hpp"
#include "rshell/core/ruac_run.hpp"
#include "rstd/cmdlex/ruac_cmdlex.hpp"
#include "rstd/colors/ruac_color26.hpp"
#include "rstd/convert/ruac_lowercase.hpp"
#include "rstd/convert/ruac_rmspace.hpp"
#include "rstd/ruac_tflush.hpp"
#include "welcome/ruac_guidance.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <syncstream>
#include <vector>

#if defined(__linux__) || defined(__gnu_linux__)
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <io.h>
#else
#error "Unsupported platform: only Windows and Linux are supported"
#endif

namespace ruac::rshell::core {

    /**
     * @brief Construct a Run with exec, cmdlex, and prompt
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Stores the kernel reference, creates a CmdLex
     *          and a Exec via std::make_unique, and sets
     *          the default prompt to "ruac-db> ".
     *
     */
    Run::Run(kernel::state::Kernel &kstate_) {

        m_kstate = kstate_;
        m_cmdlex = std::make_unique<ruac::rstd::cmdlex::api::CmdLex>();
        m_exec = std::make_unique<Exec>(kstate_);
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
    void Run::print_history() {

        auto &u = ruac::permission_guard::GuardLock::get();
        auto r = ruac::permission_guard::GuardList::ROOT;
        if (!u.judgment_lock(m_kstate.get_current_user_id(), r)) {
            u.print_message("Error: ", "Current user is not enable print history permission");
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
    void Run::clear_history() {

        auto &u = ruac::permission_guard::GuardLock::get();
        auto r = ruac::permission_guard::GuardList::MANAGER;
        if (!u.judgment_lock(m_kstate.get_current_user_id(), r)) {
            u.print_message("Error: ", "Current user is not enable clear history permission !");
            return;
        }

        if (m_commands_history.empty()) {
            std::osyncstream(std::cout) << "Warn : History not any records !" << std::endl;
            return;
        }

        {
            m_commands_history.clear();
            std::osyncstream(std::cout) << "Done : History already clear." << std::endl;
        }
    }

    /**
     * @brief Clear the terminal screen
     *
     * @details Delegates to ruac::rstd::tflush() which writes ANSI
     *          escape sequences via a synchronized output stream to
     *          clear the screen and reset the cursor position.
     */
    void Run::clear_screen() {
        ruac::rstd::tflush();
    }

    /**
     * @brief Dispatch a command line, handling history commands locally
     *
     * @param line_ - A pre-processed command line
     *
     * @return status_code - The status code from Exec::exec()
     *
     * @details Intercepts "print history" and "clear history" commands
     *          locally, then delegates all commands to m_exec->exec()
     *          for further processing.
     *
     */
    auto Run::exec(const std::string &line_) -> status_code {
        {
            auto &gl = ruac::permission_guard::GuardLock::get();
            auto rg = ruac::permission_guard::GuardList::SYSTEM;
            if (!gl.judgment_lock(m_kstate.get_current_user_id(), rg)) {
                namespace u = ruac::rlib::tdebug;
                std::string line = line_;
                auto fmt = u::Info::get().fmt("Run", "exec(...)", std::move(line));
                u::Info::get().print(std::move(fmt), __FILE__, __LINE__);
            }
        }

        if (line_ == "print history") {
            print_history();
        } else if (line_ == "clear history") {
            clear_history();
        } else if (line_ == "clear screen") {
            clear_screen();
        }
        return m_exec->exec(line_);
    }

    /**
     * @brief Store the runtime shell arguments
     *
     * @param args_ - ShellArgs struct with colour/history/bugfix flags
     *
     */
    void Run::set_args(const ruac::rshell::lib::args::ShellArgs &args_) {
        m_args = args_;
    }

    /**
     * @brief Configure the shell prompt based on runtime args
     *
     * @details If m_args.m_enable_ht is false, sets the prompt
     *          to the plain "ruac-db> ". Otherwise constructs a Color26
     *          instance with ce/ht/bf flags and builds a coloured
     *          prompt: red "ruac-db" + green ">".
     *
     */
    void Run::set_prompt() {

        auto &agrs = m_args;

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
     *          checks m_exec for null (aborts with a fatal error
     *          if missing). Enters a REPL loop: prints the prompt,
     *          reads a line from stdin, skips empty lines, preprocesses
     *          via rmspace + lowercase, splits into semicolon-separated
     *          commands via m_cmdlex->lex(), applies rmspace
     *          again per line, and dispatches each via exec(). Breaks
     *          when exec() returns NORMAL_EXIT or ABNORMAL_EXIT.
     *
     */
    void Run::run() {

        {
            ruac::welcome::guidance::BaseInfoColorParamList color_param_list{
                .m_enable_ce = true,
                .m_enable_ht = false,
                .m_enable_bf = false,
                .m_enable_dp = false,
            };
            ruac::welcome::guidance::BaseInfo bash_info;
            bash_info.init(color_param_list);
#if defined(__linux__) || defined(__gnu_linux__)
            if (isatty(fileno(stdin))) {
                bash_info.show();
#elif defined(_WIN32) || defined(_WIN64)
            if (_isatty(_fileno(stdin))) {
                bash_info.show();
#else
#error "Unsupported platform: only Windows and Linux are supported"
#endif
            }
        }

        if (nullptr == m_exec) {
            std::stringstream ss;
            ss << "Fatal: Program error ! Shell exec program lose, please contact the developer !\n";
            ss << "       Position: Module 'ruac::rshell::core'\n";
            ss << "                 |__Class 'Run'\n";
            ss << "                    |__Func: 'run()'\n";
            ss << "       Line: " << __LINE__ << "\n";
            ss << "       File: " << __FILE__ << "\n";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        while (true) {

            std::osyncstream(std::cout) << m_prompt;
            std::string lines;
            if (!std::getline(std::cin, lines)) {
                break;
            }

            if (lines.empty()) {
                continue;
            }

            {
                ruac::rstd::convert::rmspace::remove_string_spaces(lines);
                ruac::rstd::convert::lowercase::to_lower_string(lines);
            }

            std::vector<std::string> line_list;
            if (!m_cmdlex->lex(lines, line_list)) {
                continue;
            }

            auto ret{status_code::CONTINUE};
            for (auto &line : line_list) {
                {
                    ruac::rstd::convert::rmspace::remove_string_spaces(line);
                }
                ret = exec(line);
                if (ret == status_code::ABNORMAL_EXIT || ret == status_code::NORMAL_EXIT) {
                    return;
                }
            }
        }
    }

} // namespace ruac::rshell::core
