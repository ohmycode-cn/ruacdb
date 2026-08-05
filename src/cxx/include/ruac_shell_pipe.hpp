/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_pipe.hpp
 * src/ruac_shell_pipe.cpp
 *
 * @brief Singleton pipe mechanism for sharing command history across shell components.
 */

#pragma once
#ifndef RUAC_SHELL_PIPE_HPP
#define RUAC_SHELL_PIPE_HPP

#include <string>
#include <vector>

namespace ruac {

    struct ShellPipeContext {
        std::vector<std::string> *m_ptr_history_commands_count{nullptr};
    };

    class ShellPipe {
      private:
        ShellPipeContext m_context;

      public:
        ShellPipe() = default;
        ~ShellPipe() = default;
        ShellPipe(const ShellPipe &) = delete;
        ShellPipe &operator=(const ShellPipe &) = delete;

      public:
        auto static instance() -> ShellPipe &;
        void set_context(const ShellPipeContext &context_ = {});
        auto get_context() -> ShellPipeContext &;
    };

} // namespace ruac

#endif // RUAC_SHELL_PIPE_HPP
