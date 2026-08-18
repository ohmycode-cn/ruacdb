/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/hshell/ruac_help_shell.hpp
 * src/help/hshell/ruac_help_shell.cpp
 *
 * @brief Defines the HelpShell class for interactive shell command help with query support.
 */

#pragma once
#ifndef RUAC_HELP_SHELL_HPP
#define RUAC_HELP_SHELL_HPP

#include <string_view>
#include <string>
#include <mutex>

namespace ruac::help::hshell {

    class HelpShell {
      private:
        std::mutex M_HELP_SHELL_MTX;
        std::string m_prompt;

      private:
        [[nodiscard]] inline auto is_exit_command_safe(std::string_view input_) noexcept -> bool;
        auto query(const std::string &line_) -> int;

      public:
        HelpShell();
        ~HelpShell() = default;

      public:
        void runhsh();
    };

} // namespace ruac::help::hshell

#endif // RUAC_HELP_SHELL_HPP
