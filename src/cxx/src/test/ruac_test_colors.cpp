/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_colors.hpp
 * src/test/ruac_test_colors.cpp
 */

#include "rstd/colors/ruac_background.hpp"
#include "test/ruac_test_colors.hpp"
#include <sstream>
#include <iostream>

namespace ruac::test {

    namespace {
        namespace {
            namespace u = ruac::rstd::colors;
        } // namespace

        /**
         * @brief Render an 8-colour palette under bright and dark backgrounds
         *
         * @return std::string - concatenated ANSI-coloured space blocks
         *
         * @details Creates two ruac::rstd::colors::Background instances:
         *          one in bright mode and one in dark mode. For each
         *          instance, streams the eight colour variants
         *          (d, r, g, y, b, m, c, w) of a four-space block into a
         *          stringstream, separating the bright and dark rows
         *          with a newline, and returns the assembled string.
         *
         */
        auto test_dark_background() -> std::string {

            constexpr const char *const SPACE{"    "};
            std::stringstream ss;

            auto bd = new u::Background(true, true, false);
            ss << bd->d(SPACE);
            ss << bd->r(SPACE);
            ss << bd->g(SPACE);
            ss << bd->y(SPACE);
            ss << bd->b(SPACE);
            ss << bd->m(SPACE);
            ss << bd->c(SPACE);
            ss << bd->w(SPACE);
            delete bd;
            bd = nullptr;

            auto db = new u::Background(true, true, true);
            ss << "\n";
            ss << db->d(SPACE);
            ss << db->r(SPACE);
            ss << db->g(SPACE);
            ss << db->y(SPACE);
            ss << db->b(SPACE);
            ss << db->m(SPACE);
            ss << db->c(SPACE);
            ss << db->w(SPACE);
            delete db;
            db = nullptr;

            return ss.str();
        }

    } // namespace

    /**
     * @brief Drive the colour palette test case
     *
     * @details Invokes test_dark_background() and writes the
     *          resulting ANSI-coloured string to std::cout.
     *
     */
    [[maybe_unused]] void test_main_colors() {
        std::cout << test_dark_background() << std::endl;
    }

} // namespace ruac::test
