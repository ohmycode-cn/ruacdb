/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/core/ruac_run.hpp
 * src/rshell/core/ruac_run.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RUN_HPP
#define RUAC_RUN_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "rshell/core/ruac_exec.hpp"
#include "rshell/lib/ruac_args.hpp"
#include "rshell/lib/ruac_scode.hpp"
#include "rstd/cmdlex/ruac_cmdlex.hpp"

#include <memory>
#include <mutex>
#include <vector>

namespace ruac::rshell::core {

    class Run {
      private:
        std::unique_ptr<ruac::rstd::cmdlex::api::CmdLex> m_cmdlex;
        std::unique_ptr<ruac::rshell::core::Exec> m_exec;
        ruac::rshell::lib::args::ShellArgs m_args;
        std::vector<std::string> m_commands_history;
        ruac::kernel::state::Kernel m_kstate;
        std::mutex M_RUN_MTX;
        std::string m_prompt;

      private:
        using status_code = ruac::rshell::lib::scode::StatusCode;

      private:
        void print_history();
        void clear_history();
        auto exec(const std::string &line_) -> status_code;

      public:
        explicit Run(kernel::state::Kernel &kstate_);
        ~Run() = default;

      public:
        void set_args(const ruac::rshell::lib::args::ShellArgs &args_);
        void set_prompt();
        void run();
    };

} // namespace ruac::rshell::core

#endif // RUAC_RUN_HPP
