/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_interaction.hpp
 * src/ruac_shell_interaction.cpp
 *
 * @brief Interactive REPL shell for the RUAC database system with command-line parsing and execution.
 */

#pragma once
#ifndef RUAC_SHELL_INTERACTION_HPP
#define RUAC_SHELL_INTERACTION_HPP

#include "kernel/state/ruac_state_kernel.hpp"
#include <mutex>
#include <string>
#include <vector>

namespace ruac {

    struct ShellInteractionConfig {
        bool m_enable_ce{true};  // MODE: Enable console compatible : true is "\033",           false is "\x1b"
        bool m_enable_ht{false}; // MODE: Enable highlight          : true is highlight string, false if text string
        bool m_enable_bf{false}; // MODE: Enable bold font          : true is bold,             false is normal
        bool m_enable_dp{false}; // MODE: Enable background         : true is dark,             false is tint
    };

    class ShellInteraction {
      private:
        kernel::state::Kernel &m_kernel_state;
        std::vector<std::string> m_history_commands_count;
        ShellInteractionConfig m_config{};
        std::mutex M_INTERACTION_MTX;

      private:
        void print_welcome_guidance();
        void print_message();
        void set_prompt(bool enable_ht_ = true);
        void to_lower(std::string &str_);
        std::string m_prompt{"ruac-db> "};

      public:
        explicit ShellInteraction(kernel::state::Kernel &kernel_state_);
        ~ShellInteraction() = default;

      public:
        void init(const ShellInteractionConfig &config_ = {});
        auto run() -> bool;
    };

} // namespace ruac

#endif // RUAC_SHELL_INTERACTION_HPP
