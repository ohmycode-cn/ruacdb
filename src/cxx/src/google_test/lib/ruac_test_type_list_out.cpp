/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_type_list_out.hpp
 * src/google_test/lib/ruac_test_type_list_out.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_type_list_out.hpp"

#include "gtest/gtest.h"
#include "rstd/colors/ruac_ansi.hpp"

namespace {

    namespace clr = ruac::rstd::colors::ansi;

    TEST(TypeListOutTest, BasicGlyphsNotEmpty) {
        namespace T = clr::table_item::basic;
        EXPECT_FALSE(std::string(T::G_CROSS).empty());
        EXPECT_FALSE(std::string(T::G_HLINE).empty());
        EXPECT_FALSE(std::string(T::G_VLINE).empty());
    }

    TEST(TypeListOutTest, SingleLineGlyphsNotEmpty) {
        namespace T = clr::table_item::single_line;
        EXPECT_FALSE(std::string(T::G_TL).empty());
        EXPECT_FALSE(std::string(T::G_TR).empty());
        EXPECT_FALSE(std::string(T::G_BL).empty());
        EXPECT_FALSE(std::string(T::G_BR).empty());
        EXPECT_FALSE(std::string(T::G_HLINE).empty());
        EXPECT_FALSE(std::string(T::G_VLINE).empty());
        EXPECT_FALSE(std::string(T::G_CROSS).empty());
    }

    TEST(TypeListOutTest, DoubleLineGlyphsNotEmpty) {
        namespace T = clr::table_item::double_line;
        EXPECT_FALSE(std::string(T::G_TL).empty());
        EXPECT_FALSE(std::string(T::G_TR).empty());
        EXPECT_FALSE(std::string(T::G_BL).empty());
        EXPECT_FALSE(std::string(T::G_BR).empty());
        EXPECT_FALSE(std::string(T::G_HLINE).empty());
        EXPECT_FALSE(std::string(T::G_VLINE).empty());
    }

    TEST(TypeListOutTest, BoldGlyphsNotEmpty) {
        namespace T = clr::table_item::bold;
        EXPECT_FALSE(std::string(T::G_TL).empty());
        EXPECT_FALSE(std::string(T::G_TR).empty());
        EXPECT_FALSE(std::string(T::G_BL).empty());
        EXPECT_FALSE(std::string(T::G_BR).empty());
    }

    TEST(TypeListOutTest, MixedGlyphsNotEmpty) {
        namespace M = clr::table_item::mixed;
        EXPECT_FALSE(std::string(M::G_TL_SL).empty());
        EXPECT_FALSE(std::string(M::G_TR_SL).empty());
        EXPECT_FALSE(std::string(M::G_BL_SL).empty());
        EXPECT_FALSE(std::string(M::G_BR_SL).empty());
        EXPECT_FALSE(std::string(M::G_HLINE_DL).empty());
        EXPECT_FALSE(std::string(M::G_VLINE_SL).empty());
    }

    TEST(TypeListOutTest, BasicDifferentFromSingleLine) {
        namespace B = clr::table_item::basic;
        namespace S = clr::table_item::single_line;
        EXPECT_NE(std::string(B::G_CROSS), std::string(S::G_CROSS));
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_type_list_out_main() -> int {
        kit::SafeMsg::get().println("func: ", "test type list out");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
