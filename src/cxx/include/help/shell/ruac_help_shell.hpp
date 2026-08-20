/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/help/shell/ruac_help_shell.hpp
 * src/help/shell/ruac_help_shell.cpp
 *
 * @brief Defines the HelpShell class for interactive shell command help with query support.
 */

#pragma once
#ifndef RUAC_HELP_SHELL_HPP
#define RUAC_HELP_SHELL_HPP

#include "rstd/cmdlex/ruac_cmdlex.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <string_view>

namespace ruac::help::shell {

    class HelpShell {
      private:
        std::mutex M_HELP_SHELL_MTX;
        std::string m_prompt;
        std::unique_ptr<ruac::rstd::cmdlex::api::CmdLex> m_cmdlex;

      private:
        [[nodiscard]] inline auto is_exit_command(std::string_view input_) noexcept -> bool;
        auto dispatch(const std::string &line_) -> int;

      public:
        HelpShell();
        ~HelpShell() = default;

      public:
        void run();
    };

} // namespace ruac::help::shell

#endif // RUAC_HELP_SHELL_HPP
