/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/ruac_rshell.hpp
 * src/rshell/ruac_rshell.cpp
 */

#include "rshell/ruac_rshell.hpp"
#include <syncstream>
#include <sstream>
#include <iostream>

namespace ruac::rshell::api {

    /**
     * @brief Construct an RShell bound to a kernel state
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Creates a Run instance via std::make_unique and stores
     *          it in m_run. The Run owns the shell exec and cmdlex
     *          pipeline.
     *
     */
    RShell::RShell(kernel::state::Kernel &kstate_) {
        m_run = std::make_unique<ruac::rshell::core::Run>(kstate_);
    }

    /**
     * @brief Store the runtime shell arguments
     *
     * @param args_ - ShellArgs struct with colour/history/bugfix/display flags
     *
     * @details Copies the args into m_args for later use by
     *          run() when configuring the Run prompt.
     *
     */
    void RShell::set_args(const ruac::rshell::lib::args::ShellArgs &args_) {
        m_args = args_;
    }

    /**
     * @brief Start the interactive shell
     *
     * @param color_prompt_ - When true, configure a coloured prompt via
     *                        Run::set_prompt()
     *
     * @details Acquires M_RSHELL_MTX, checks m_run for null (printing
     *          a fatal error and returning if missing), then forwards
     *          the stored ShellArgs to Run, optionally sets a
     *          coloured prompt, and calls Run::run() to enter the
     *          read-eval loop.
     *
     */
    void RShell::run(bool color_prompt_) {

        std::lock_guard<std::mutex> lock(M_RSHELL_MTX);

        if (nullptr == m_run) {
            std::stringstream ss;
            ss << "Fatal: Program error ! Shell filter program lose, please contact the developer !\n";
            ss << "       Position: Module 'ruac::rshell::api'\n";
            ss << "                 |__Class 'RShell'\n";
            ss << "                    |__Func: 'run(...)'\n";
            ss << "       Line: " << __LINE__ << "\n";
            ss << "       File: " << __FILE__ << "\n";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        {
            m_run.get()->set_args(m_args);
            if (color_prompt_) {
                m_run.get()->set_prompt();
            }
        }

        m_run.get()->run();
    }

} // namespace ruac::rshell::api
