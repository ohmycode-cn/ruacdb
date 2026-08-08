#include "src/ruac_window.hpp"
#include <print>

/**
 * @brief Program entry point for the ruacdb terminal lite application
 *
 * @return int - process exit status
 *
 * @details Prints a startup banner via std::print, constructs a
 *          ruac::terminal_lite::Window instance and launches the GUI
 *          event loop by calling Window::run(0, nullptr).
 *
 */
int main() {
    std::print("This is ruacdb terminal lite");
    ruac::terminal_lite::Window window;
    window.run(0, nullptr);
}