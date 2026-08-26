/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_colors.hpp
 * src/google_test/lib/ruac_test_colors.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_colors.hpp"

#include "gtest/gtest.h"
#include "rstd/colors/ruac_background.hpp"

namespace {

    namespace u = ruac::rstd::colors;

    TEST(ColorsTest, BrightBackgroundNonEmpty) {
        u::Background bd(true, true, false);
        constexpr const char *const SPACE{"    "};
        EXPECT_FALSE(bd.d(SPACE).empty());
        EXPECT_FALSE(bd.r(SPACE).empty());
        EXPECT_FALSE(bd.g(SPACE).empty());
        EXPECT_FALSE(bd.y(SPACE).empty());
        EXPECT_FALSE(bd.b(SPACE).empty());
        EXPECT_FALSE(bd.m(SPACE).empty());
        EXPECT_FALSE(bd.c(SPACE).empty());
        EXPECT_FALSE(bd.w(SPACE).empty());
    }

    TEST(ColorsTest, DarkBackgroundNonEmpty) {
        u::Background bd(true, true, true);
        constexpr const char *const SPACE{"    "};
        EXPECT_FALSE(bd.d(SPACE).empty());
        EXPECT_FALSE(bd.r(SPACE).empty());
        EXPECT_FALSE(bd.g(SPACE).empty());
        EXPECT_FALSE(bd.y(SPACE).empty());
        EXPECT_FALSE(bd.b(SPACE).empty());
        EXPECT_FALSE(bd.m(SPACE).empty());
        EXPECT_FALSE(bd.c(SPACE).empty());
        EXPECT_FALSE(bd.w(SPACE).empty());
    }

    TEST(ColorsTest, BrightVsDarkDifferentOutput) {
        u::Background bright(true, true, false);
        u::Background dark(true, true, true);
        constexpr const char *const SPACE{"    "};
        EXPECT_NE(bright.r(SPACE), dark.r(SPACE));
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_colors_main() -> int {
        kit::SafeMsg::get().println("func: ", "test colors");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
