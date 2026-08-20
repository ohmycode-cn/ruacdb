/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/ruac_rsh.hpp
 * src/ruacsh/ruac_rsh.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RSH_HPP
#define RUAC_RSH_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "ruacsh/kit/ruac_rsh_run.hpp"
#include "ruacsh/lib/ruac_ragrs.hpp"
#include <memory>
#include <mutex>

namespace ruac::ruacsh::api {

    class Interface {
      private:
        std::unique_ptr<ruac::ruacsh::kit::RshRun> m_rsh_run;
        ruac::ruacsh::lib::ragrs::RshellArgs m_rshell_args;
        std::mutex M_RSH_MTX;

      public:
        explicit Interface(kernel::state::Kernel &kstate_);
        ~Interface() = default;

      public:
        void set_ragrs(const ruac::ruacsh::lib::ragrs::RshellArgs &args_);
        void run_shell(bool color_prompt_ = false);
    };

} // namespace ruac::ruacsh::api

#endif // RUAC_RSH_HPP
