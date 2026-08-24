/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/ruac_tflush.hpp
 * src/rstd/ruac_tflush.cpp
 */

#include "rstd/ruac_tflush.hpp"

#include <ostream>
#include <syncstream>
#include <iostream>

namespace ruac::rstd {

    /**
     * @brief Clears the terminal screen.
     *
     * @details Writes ANSI escape sequences via a synchronized output stream
     *          to clear the screen and move the cursor to the home position.
     */
    void tflush() {
        std::osyncstream(std::cout) << ("\n\033[2J\033[1;1H") << std::flush;
    }

} // namespace ruac::rstd
