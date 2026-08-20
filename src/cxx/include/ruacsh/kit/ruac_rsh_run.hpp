/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/kit/ruac_rsh_run.hpp
 * src/ruacsh/kit/ruac_rsh_run.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RSH_RUN_HPP
#define RUAC_RSH_RUN_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "ruacsh/lib/ruac_ragrs.hpp"
#include "rstd/rshell/filter/ruac_rshfer.hpp"
#include "ruacsh/kit/ruac_rsh_exec.hpp"
#include "ruacsh/lib/ruac_scode.hpp"
#include <mutex>
#include <vector>
#include <memory>

namespace ruac::ruacsh::kit {

    class RshRun {
      private:
        std::unique_ptr<ruac::rstd::rshell::filter::api::Interface> m_rshell_filter;
        std::unique_ptr<ruac::ruacsh::kit::RshExec> m_rsh_exec;
        ruac::ruacsh::lib::ragrs::RshellArgs m_rshell_args;
        std::vector<std::string> m_commands_history;
        ruac::kernel::state::Kernel m_kstate;
        std::mutex M_RSH_RUN_MTX;
        std::string m_prompt;

      private:
        using STAUTS_CODE = ruac::ruacsh::lib::scode::RuacShellStatusCode; // const alias.

      private:
        void print_history();
        void clear_history();
        auto exec(const std::string &line_) -> STAUTS_CODE;

      public:
        explicit RshRun(kernel::state::Kernel &kstate_);
        ~RshRun() = default;

      public:
        void set_ragrs(const ruac::ruacsh::lib::ragrs::RshellArgs &args_);
        void set_prompt();
        void run();
    };

} // namespace ruac::ruacsh::kit

#endif // RUAC_RSH_RUN_HPP
