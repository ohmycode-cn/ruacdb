#include "src/ruac_window.hpp"
#include <print>

int main() {
    std::print("This is ruacdb terminal lite");
    ruac::terminal_lite::Window window;
    window.run(0, nullptr);
}