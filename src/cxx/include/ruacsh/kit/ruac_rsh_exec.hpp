/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruacsh/kit/ruac_rsh_exec.hpp
 * src/ruacsh/kit/ruac_rsh_exec.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_RSH_EXEC_HPP
#define RUAC_RSH_EXEC_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "syntax_lite/ruac_synlite.hpp"
#include "ruacsh/lib/ruac_scode.hpp"
#include <string>
#include <mutex>

namespace ruac::ruacsh::kit {

    class RshExec {
      private:
        using STAUTS_CODE = ruac::ruacsh::lib::scode::RuacShellStatusCode;
        ruac::syntax_lite::SynLite m_synlite;
        kernel::state::Kernel &m_kstate;
        std::mutex M_RSH_EXEC_MTX;

      public:
        explicit RshExec(kernel::state::Kernel &kstate_);
        ~RshExec() = default;

      private:
        auto get_current_user() -> std::string;
        auto get_current_uid() -> int;
        auto uid_permission_guard(const std::string &msg_, const std::string &guard_group_ = "root",
                                  bool out_msg_ = true) -> bool;
        auto query(const std::string &line_) -> STAUTS_CODE;

      public:
        auto exec(const std::string &line_) -> STAUTS_CODE;
    };

} // namespace ruac::ruacsh::kit

#endif // RUAC_RSH_EXEC_HPP
