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
     * @brief Set the shell pipe context
     *
     * @param context_ - ShellPipeContext to store (const ref)
     *
     * @details Copies the provided ShellPipeContext into m_context for
     *          later retrieval via get_context().
     *
     */
    auto ShellPipe::set_context(const ShellPipeContext &context_) -> void {
        m_context = context_;
    }

    /**
     * @brief Get the shell pipe context
     *
     * @return ShellPipeContext& - Reference to the internal shell pipe context
     *
     * @details Returns a reference (not a copy) to m_context, allowing
     *          callers to read and modify the shared pipe context directly.
     *
     */
    auto ShellPipe::get_context() -> ShellPipeContext & {
        return m_context;
    }

} // namespace ruac
