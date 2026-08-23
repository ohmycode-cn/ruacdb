/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_format_row.hpp
 * src/google_test/lib/ruac_test_format_row.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_format_row.hpp"

#include "gtest/gtest.h"
#include "syntax_lite/tree/node/fmt/ruac_format_row.hpp"
namespace {

    using ruac::syntax_lite::tree::node::fmt::FormatRow;
    using ruac::syntax_lite::tree::node::fmt::FormatRowArgs;

    // Default args: colsize=0 → should fail
    TEST(FormatRowTest, ZeroColSizeReturnsFalse) {
        FormatRow fr;
        bool ret = true;
        FormatRowArgs args{.m_row_szie = 0};
        auto result = fr.frow(args, ret);
        EXPECT_FALSE(ret);
        EXPECT_TRUE(result.empty());
    }

    // Normal: corner + rowline * (row_szie + 2) + corner
    TEST(FormatRowTest, DefaultCornerAndColine) {
        FormatRow fr;
        bool ret = false;
        FormatRowArgs args{.m_row_szie = 5};
        auto result = fr.frow(args, ret);
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "+-------+\n");
    }

    // Custom corner and coline
    TEST(FormatRowTest, CustomCornerAndColine) {
        FormatRow fr;
        bool ret = false;
        FormatRowArgs args{
            .m_corners = '*',
            .m_rowline = '=',
            .m_row_szie = 3,
        };
        auto result = fr.frow(args, ret);
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "*=====*\n");
    }

    // Newline appended
    TEST(FormatRowTest, NewlineEnabled) {
        FormatRow fr;
        bool ret = false;
        FormatRowArgs args{
            .m_newline = true,
            .m_row_szie = 4,
        };
        auto result = fr.frow(args, ret);
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "+------+\n");
    }

    // Newline disabled (explicit)
    TEST(FormatRowTest, NewlineDisabled) {
        FormatRow fr;
        bool ret = false;
        FormatRowArgs args{
            .m_newline = false,
            .m_row_szie = 4,
        };
        auto result = fr.frow(args, ret);
        EXPECT_TRUE(ret);
        // No trailing '\n'
        EXPECT_EQ(result.back(), '+');
    }

    // Single column width
    TEST(FormatRowTest, SingleColumnWidth) {
        FormatRow fr;
        bool ret = false;
        FormatRowArgs args{.m_row_szie = 1};
        auto result = fr.frow(args, ret);
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "+---+\n");
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_format_row_main() -> int {
        kit::SafeMsg::get().println("func: ", "test format row");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
