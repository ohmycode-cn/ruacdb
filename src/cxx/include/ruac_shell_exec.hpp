/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_exec.hpp
 * src/ruac_shell_exec.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_SHELL_EXEC_HPP
#define RUAC_SHELL_EXEC_HPP

#include <string>
#include <mutex>
#include <vector>

namespace ruac {

    class ShellExec {
      private:
        static constexpr const char *const M_B_RED{"\033[41m"};
        static constexpr const char *const M_F_YELLOW{"\033[33m"};
        static constexpr const char *const M_B_GREEN{"\033[42m"};
        static constexpr const char *const M_RESET{"\033[0m"};

      private:
        std::vector<std::string> m_cmd_history_records_bak;

      private:
        auto end_whiled(const std::string &line_) -> bool;
        void cat_cmd_history();
        void cat_cmd_history_bak();

      private:
        std::mutex M_SHELL_EXEC_MTX;
        auto inner_exec(const std::string &line_) -> int;

      public:
        ShellExec() = default;
        ~ShellExec() = default;

      public:
        auto exec(const std::string &lines_) -> int;
    };

} // namespace ruac

#endif // RUAC_SHELL_EXEC_HPP
