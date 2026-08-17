/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_exec.hpp
 * src/ruac_shell_exec.cpp
 *
 * @brief Thread-safe shell command executor with history tracking and built-in command dispatching.
 */

#pragma once
#ifndef RUAC_SHELL_EXEC_HPP
#define RUAC_SHELL_EXEC_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include "syntax_lite/ruac_synlite.hpp"
#include <mutex>
#include <string>

namespace ruac {

    class ShellExec {

      private:
        kernel::state::Kernel &m_kernel_state;
        syntax_lite::SynLite M_SYN_LITE;
        std::mutex M_SHELL_EXEC_MTX;
        static constexpr const char *const M_B_RED{"\033[41m"};
        static constexpr const char *const M_F_YELLOW{"\033[33m"};
        static constexpr const char *const M_B_GREEN{"\033[42m"};
        static constexpr const char *const M_RESET{"\033[0m"};

      private:
        auto end_whiled(const std::string &line_) -> bool;
        void cat_command_history();
        void clr_command_history();
        auto get_current_user() -> std::string;
        auto get_current_uid() -> int;
        auto group_weight(const std::string &group_) const -> int;
        auto uid_permission_guard(const std::string &msg_,
                                  const std::string &guard_group_ = "root",
                                  bool out_msg_ = true) -> bool;

      private:
        auto inner_exec(const std::string &line_) -> int;

      public:
        explicit ShellExec(kernel::state::Kernel &kernel_state);
        ~ShellExec() = default;

      public:
        auto exec(const std::string &lines_) -> int;
    };

} // namespace ruac

#endif // RUAC_SHELL_EXEC_HPP
