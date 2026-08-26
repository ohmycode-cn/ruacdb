/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rshell/core/ruac_exec.hpp
 * src/rshell/core/ruac_exec.cpp
 *
 * @brief Defines the Exec class for executing parsed RUAC commands through SynxLite with thread-safe access.
 */

#pragma once
#ifndef RUAC_EXEC_HPP
#define RUAC_EXEC_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "system/permission/ruac_guardlock.hpp"
#include "rshell/lib/ruac_scode.hpp"
#include "syntax_lite/ruac_synxlite.hpp"

#include <mutex>
#include <string>
#include <vector>

namespace ruac::rshell::core {

    class Exec {
      private:
        using status_code = ruac::rshell::lib::scode::StatusCode;
        ruac::syntax_lite::api::SynxLite m_synlite;
        kernel::state::Kernel &m_kstate;
        std::mutex M_EXEC_MTX;

      public:
        explicit Exec(kernel::state::Kernel &kstate_);
        ~Exec() = default;

      private:
        std::vector<std::string> M_ROOT_LINES;

      private:
        auto get_current_user() -> std::string;
        auto get_current_uid() -> int;
        auto uid_permission_guard(ruac::system::permission::GuardList guard_, const std::string &msg_) -> bool;
        auto dispatch_stdmsg(const std::string &line_) -> bool;
        auto dispatch(const std::string &line_) -> status_code;

      public:
        auto exec(const std::string &line_) -> status_code;
    };

} // namespace ruac::rshell::core

#endif // RUAC_EXEC_HPP
