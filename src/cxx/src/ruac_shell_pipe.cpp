/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/ruac_shell_pipe.hpp
 * src/ruac_shell_pipe.cpp
 */

#include "ruac_shell_pipe.hpp"

namespace ruac {

    /**
     * @brief Get the singleton instance of ShellPipe
     *
     * @return ShellPipe& - Reference to the singleton instance
     *
     * @details Implements the singleton pattern using a static local variable.
     *          Returns a reference to the single ShellPipe instance, ensuring
     *          only one instance exists throughout the application.
     *
     */
    ShellPipe &ShellPipe::instance() {
        static ShellPipe instance;
        return instance;
    }

    /**
     * @brief Set the shell pipe list
     *
     * @param shell_pipe_list_ - ShellPipeList to store (const ref)
     *
     * @details Copies the provided ShellPipeList into m_shell_pipe_list for
     *          later retrieval via get_shell_pipe_list().
     *
     */
    auto ShellPipe::set_shell_pipe_list(const ShellPipeList &shell_pipe_list_) -> void {
        m_shell_pipe_list = shell_pipe_list_;
    }

    /**
     * @brief Get the shell pipe list
     *
     * @return ShellPipeList& - Reference to the internal shell pipe list
     *
     * @details Returns a reference (not a copy) to m_shell_pipe_list, allowing
     *          callers to read and modify the shared pipe list directly.
     *
     */
    auto ShellPipe::get_shell_pipe_list() -> ShellPipeList & {
        return m_shell_pipe_list;
    }

} // namespace ruac
