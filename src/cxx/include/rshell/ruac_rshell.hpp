/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/ruac_rshell.hpp
 * src/rshell/ruac_rshell.cpp
 *
 * @brief Defines the RShell API facade that initializes and drives the interactive RUAC shell loop.
 */

#pragma once
#ifndef RUAC_RSHELL_HPP
#define RUAC_RSHELL_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "rshell/core/ruac_run.hpp"
#include "rshell/lib/ruac_args.hpp"
#include <memory>
#include <mutex>

namespace ruac::rshell::api {

    class RShell {
      private:
        std::unique_ptr<ruac::rshell::core::Run> m_run;
        ruac::rshell::lib::args::ShellArgs m_args;
        std::mutex M_RSHELL_MTX;

      public:
        explicit RShell(kernel::state::Kernel &kstate_);
        ~RShell() = default;

      public:
        void set_args(const ruac::rshell::lib::args::ShellArgs &args_);
        void run(bool color_prompt_ = false);
    };

} // namespace ruac::rshell::api

#endif // RUAC_RSHELL_HPP
