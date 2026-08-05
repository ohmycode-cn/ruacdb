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

#include <string>
#include <mutex>

namespace ruac {

    class ShellExec {
      private:
        static constexpr const char *const M_B_RED{"\033[41m"};
        static constexpr const char *const M_F_YELLOW{"\033[33m"};
        static constexpr const char *const M_B_GREEN{"\033[42m"};
        static constexpr const char *const M_RESET{"\033[0m"};
        std::mutex M_SHELL_EXEC_MTX;

      private:
        auto end_whiled(const std::string &line_) -> bool;
        void cat_command_history();
        void clr_command_history();

      private:
        auto inner_exec(const std::string &line_) -> int;

      public:
        ShellExec() = default;
        ~ShellExec() = default;

      public:
        auto exec(const std::string &lines_) -> int;
    };

} // namespace ruac

#endif // RUAC_SHELL_EXEC_HPP
