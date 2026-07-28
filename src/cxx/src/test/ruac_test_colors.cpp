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

        namespace u = ruac::rstd::colors;

        auto test_dark_background(void) -> std::string {

            constexpr const char *const SPACE{"    "};
            std::stringstream ss;

            u::Background *bd = new u::Background(true, true, false);
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

            u::Background *db = new u::Background(true, true, true);
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

    void test_main_colors(void) {
        std::cout << test_dark_background() << std::endl;
    }

} // namespace ruac::test
