/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/welcome/ruac_logo.hpp
 * src/welcome/ruac_logo.cpp
 */

#include "welcome/ruac_logo.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <syncstream>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace ruac::welcome::logo {

    /**
     * @brief Return the ASCII art lines for the ruacdb logo
     *
     * @details Constructs a static vector of nine strings forming the ASCII
     *          art banner for ruacdb. The first and last lines are delimiter
     *          markers ("[*]"), and the seven inner lines render the
     *          stylised "ruacdb" wordmark in figlet/ANSI-art style using
     *          only plain characters. The vector is returned by value so
     *          callers can iterate or measure it without sharing state.
     *
     */
    auto out_logo_lines() -> std::vector<std::string> {
        std::vector<std::string> lines{
            "[*]",
            " | ooooooooo.   ooooo     ooo       .o.         .oooooo.   oooooooooo.   oooooooooo.  ",
            " | `888   `Y88. `888'     `8'      .888.       d8P'  `Y8b  `888'   `Y8b  `888'   `Y8b ",
            " |  888   .d88'  888       8      .8' 88.     888           888      888  888     888 ",
            " |  888ooo88P'   888       8     .8' `888.    888           888      888  888oooo888' ",
            " |  888`88b.     888       8    .88ooo8888.   888           888      888  888    `88b ",
            " |  888  `88b.   `88.    .8'   .8'     `888.  `88b    ooo   888     d88'  888    .88P ",
            " | o888o  o888o    `YbodP'    o88o     o8888o  `Y8bood8P'  o888bood8P'   o888bood8P'  ",
            "[*]",
        };
        return lines;
    }

    /**
     * @brief Compute the maximum line width across a vector of strings
     *
     * @details Iterates over every element of `lines_`, casts each line's
     *          `.size()` to `int`, and keeps the running maximum in the
     *          output parameter `line_`. The caller must initialise
     *          `line_` (typically to 0) before the call; the function
     *          only ever increases it, never resets it.
     *
     */
    void get_wmax_line(int &line_, const std::vector<std::string> &lines_) {
        for (const auto &line : lines_) {
            line_ = std::max(line_, static_cast<int>(line.size()));
        }
    }

    /**
     * @brief Query the current terminal width in columns
     *
     * @details On Windows, calls GetConsoleScreenBufferInfo to read the
     *          visible console window width. On POSIX systems, uses
     *          ioctl(TIOCGWINSZ) to retrieve the terminal's column count
     *          from the kernel. Returns 0 if the query fails or the
     *          platform is unsupported, allowing callers to treat a zero
     *          return as "unknown width".
     *
     */
    auto get_terminal_width() -> int {
#if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
#else
        struct winsize ws{};
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0) {
            return ws.ws_col;
        }
#endif
        return 0;
    }

    /**
     * @brief Print the ruacdb ASCII logo to stdout if the terminal is wide
     *        enough
     *
     * @details Queries the terminal width via get_terminal_width() and
     *          compares it to the widest line produced by out_logo_lines().
     *          When the terminal is wide enough the logo is assembled into
     *          a std::stringstream and flushed atomically through
     *          std::osyncstream so concurrent writers cannot interleave
     *          mid-logo. When the terminal is too narrow a warning message
     *          is printed instead, and the logo is suppressed entirely.
     *
     */
    void print_logo() {
        int wmax_term = get_terminal_width();
        int wmax_line{0};
        get_wmax_line(wmax_line, out_logo_lines());
        if (wmax_line <= wmax_term) {
            std::stringstream ss;
            for (const auto &line : out_logo_lines()) {
                ss << line << "\n";
            }
            std::osyncstream(std::cout) << ss.str() << std::flush;
            return;
        }

        // else branch: terminal width is too narrow
        {
            char msg[] = "[Warn  :(]: Terminal width is too narrow, can not display ruacdb logo";
            std::osyncstream(std::cout) << msg << std::endl;
        }
    }

} // namespace ruac::welcome::logo
