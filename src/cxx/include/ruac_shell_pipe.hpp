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
#include <vector>
#ifndef RUAC_SHELL_PIPE_HPP
#define RUAC_SHELL_PIPE_HPP

#include <string>

namespace ruac {

    struct ShellPipeList {
        std::vector<std::string> *m_cmd_history_records_ptr{nullptr};
    };

    class ShellPipe {
      private:
        ShellPipeList m_shell_pipe_list;

      public:
        ShellPipe() = default;
        ~ShellPipe() = default;
        ShellPipe(const ShellPipe &) = delete;
        ShellPipe &operator=(const ShellPipe &) = delete;

      public:
        auto static instance() -> ShellPipe &;
        void set_shell_pipe_list(const ShellPipeList &shell_pipe_list_ = {});
        auto get_shell_pipe_list() -> ShellPipeList &;
    };

} // namespace ruac

#endif // RUAC_SHELL_PIPE_HPP
