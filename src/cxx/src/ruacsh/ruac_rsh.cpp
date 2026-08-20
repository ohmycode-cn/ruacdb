/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/ruac_rsh.hpp
 * src/ruacsh/ruac_rsh.cpp
 */

#include "ruacsh/ruac_rsh.hpp"
#include <syncstream>
#include <sstream>
#include <iostream>

namespace ruac::ruacsh::api {

    /**
     * @brief Construct an Interface bound to a kernel state
     *
     * @param kstate_ - Reference to the shared Kernel state object
     *
     * @details Creates a RshRun instance via std::make_unique and stores
     *          it in m_rsh_run. The RshRun owns the shell exec and filter
     *          pipeline.
     *
     */
    Interface::Interface(kernel::state::Kernel &kstate_) {
        m_rsh_run = std::make_unique<ruac::ruacsh::kit::RshRun>(kstate_);
    }

    /**
     * @brief Store the runtime shell arguments
     *
     * @param args_ - RshellArgs struct with colour/history/bugfix/display flags
     *
     * @details Copies the args into m_rshell_args for later use by
     *          run_shell() when configuring the RshRun prompt.
     *
     */
    void Interface::set_ragrs(const ruac::ruacsh::lib::ragrs::RshellArgs &args_) {
        m_rshell_args = args_;
    }

    /**
     * @brief Start the interactive shell
     *
     * @param color_prompt_ - When true, configure a coloured prompt via
     *                        RshRun::set_prompt()
     *
     * @details Acquires M_RSH_MTX, checks m_rsh_run for null (printing
     *          a fatal error and returning if missing), then forwards
     *          the stored RshellArgs to RshRun, optionally sets a
     *          coloured prompt, and calls RshRun::run() to enter the
     *          read-eval loop.
     *
     */
    void Interface::run_shell(bool color_prompt_) {

        std::lock_guard<std::mutex> lock(M_RSH_MTX);

        if (nullptr == m_rsh_run) {
            std::stringstream ss;
            ss << "Fatal: Program error ! Shell filter program lose, please contact the developer !\n";
            ss << "       Position: Module 'ruac::ruacsh::api'\n";
            ss << "                 |__Class 'Interface'\n";
            ss << "                    |__Func: 'run_shell(...)'\n";
            ss << "       Line: " << __LINE__ << "\n";
            ss << "       File: " << __FILE__ << "\n";
            std::osyncstream(std::cout) << ss.str() << std::endl;
            return;
        }

        {
            m_rsh_run.get()->set_ragrs(m_rshell_args);
            if (color_prompt_) {
                m_rsh_run.get()->set_prompt();
            }
        }

        m_rsh_run.get()->run();
    }

} // namespace ruac::ruacsh::api
