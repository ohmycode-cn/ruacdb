/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_format_col.hpp
 * src/google_test/lib/ruac_test_format_col.cpp
 */
#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_format_col.hpp"

#include "gtest/gtest.h"
#include "syntax_lite/tree/node/fmt/ruac_format_col.hpp"

namespace {

    using ruac::syntax_lite::tree::node::fmt::FormatCol;
    using ruac::syntax_lite::tree::node::fmt::FormatColArgs;

    // col_max_size=0 → guard triggers, returns empty string
    TEST(FormatColTest, ZeroColMaxSize) {
        FormatCol fc;
        bool ret = true;
        FormatColArgs args{.m_col_max_size = 0};
        auto result = fc.fcol(args, ret, "");
        EXPECT_FALSE(ret);
        EXPECT_TRUE(result.empty());
    }

    // Normal: produces padded content with default '|' boundaries
    TEST(FormatColTest, DefaultCharsColSize10) {
        FormatCol fc;
        bool ret = false;
        FormatColArgs args{.m_col_max_size = 10};
        auto result = fc.fcol(args, ret, "Hello");
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "| Hello      |\n");
    }

    // Custom left and right boundary chars
    TEST(FormatColTest, CustomBoundaryChars) {
        FormatCol fc;
        bool ret = false;
        FormatColArgs args{
            .m_right_char = ']',
            .m_left_char = '[',
            .m_col_max_size = 5,
        };
        auto result = fc.fcol(args, ret, "Test");
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "[ Test  ]\n");
    }

    // Newline enabled
    TEST(FormatColTest, NewlineEnabled) {
        FormatCol fc;
        bool ret = false;
        FormatColArgs args{
            .m_newline = true,
            .m_col_max_size = 6,
        };
        auto result = fc.fcol(args, ret, "AB");
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "| AB     |\n");
    }

    // Newline disabled (explicit)
    TEST(FormatColTest, NewlineDisabled) {
        FormatCol fc;
        bool ret = false;
        FormatColArgs args{
            .m_newline = false,
            .m_col_max_size = 6,
        };
        auto result = fc.fcol(args, ret, "AB");
        EXPECT_EQ(result.back(), '|');
    }

    // Single column width
    TEST(FormatColTest, SingleColMaxSize) {
        FormatCol fc;
        bool ret = false;
        FormatColArgs args{.m_col_max_size = 1};
        auto result = fc.fcol(args, ret, "");
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "|   |\n");
    }

    // Boundary chars with same left/right
    TEST(FormatColTest, SameLeftRightChar) {
        FormatCol fc;
        bool ret = false;
        FormatColArgs args{
            .m_right_char = '#',
            .m_left_char = '#',
            .m_col_max_size = 4,
        };
        auto result = fc.fcol(args, ret, "Hi");
        EXPECT_TRUE(ret);
        EXPECT_EQ(result, "# Hi   #\n");
    }

    // Member-based fcol via fset_member_args
    TEST(FormatColTest, MemberFcolDefault) {
        FormatCol fc;
        fc.fset_member_args(FormatColArgs{.m_col_max_size = 8});
        auto result = fc.fcol("Test");
        EXPECT_EQ(result, "| Test     |\n");
    }

    // Member-based fcol with custom args and newline
    TEST(FormatColTest, MemberFcolCustomNewline) {
        FormatCol fc;
        FormatColArgs args{
            .m_right_char = '>',
            .m_left_char = '<',
            .m_newline = true,
            .m_col_max_size = 6,
        };
        fc.fset_member_args(args);
        auto result = fc.fcol("XY");
        EXPECT_EQ(result, "< XY     >\n");
    }

    // Member-based fcol: update args mid-stream
    TEST(FormatColTest, MemberFcolUpdateArgs) {
        FormatCol fc;

        fc.fset_member_args(FormatColArgs{.m_col_max_size = 4});
        auto r1 = fc.fcol("A");

        fc.fset_member_args(FormatColArgs{
            .m_right_char = ']',
            .m_left_char = '[',
            .m_col_max_size = 8,
        });
        auto r2 = fc.fcol("B");

        EXPECT_EQ(r1, "| A    |\n");
        EXPECT_EQ(r2, "[ B        ]\n");
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_format_col_main() -> int {
        kit::SafeMsg::get().println("func: ", "test format col");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
