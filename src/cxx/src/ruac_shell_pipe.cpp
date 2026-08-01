/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_pipe.hpp
 * src/ruac_shell_pipe.cpp
 */

#include "ruac_shell_pipe.hpp"

namespace ruac {

    ShellPipe &ShellPipe::instance() {
        static ShellPipe instance;
        return instance;
    }

    auto ShellPipe::set_shell_pipe_list(const ShellPipeList &shell_pipe_list_) -> void {
        m_shell_pipe_list = shell_pipe_list_;
    }

    auto ShellPipe::get_shell_pipe_list() -> ShellPipeList & {
        return m_shell_pipe_list;
    }

} // namespace ruac
