/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_rstd_clue_output.hpp
 * src/google_test/lib/ruac_test_rstd_clue_output.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_rstd_clue_output.hpp"

#include "gtest/gtest.h"
#include "rstd/clue/ruac_clue.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <syncstream>

namespace {

    namespace cl = ruac::rstd::clue;

    // --- plain (no highlight, no background) ---

    TEST(ClueOutputPlainTest, GOkNonEmpty) {
        EXPECT_FALSE(std::string(cl::G_OK).empty());
    }

    TEST(ClueOutputPlainTest, GWrNonEmpty) {
        EXPECT_FALSE(std::string(cl::G_WR).empty());
    }

    TEST(ClueOutputPlainTest, GNoNonEmpty) {
        EXPECT_FALSE(std::string(cl::G_NO).empty());
    }

    TEST(ClueOutputPlainTest, GFlNonEmpty) {
        EXPECT_FALSE(std::string(cl::G_FL).empty());
    }

    TEST(ClueOutputPlainTest, GOkContainsLabel) {
        EXPECT_NE(std::string(cl::G_OK).find("OK"), std::string::npos);
    }

    TEST(ClueOutputPlainTest, GWrContainsLabel) {
        EXPECT_NE(std::string(cl::G_WR).find("WR"), std::string::npos);
    }

    TEST(ClueOutputPlainTest, GNoContainsLabel) {
        EXPECT_NE(std::string(cl::G_NO).find("NO"), std::string::npos);
    }

    TEST(ClueOutputPlainTest, GFlContainsLabel) {
        EXPECT_NE(std::string(cl::G_FL).find("FL"), std::string::npos);
    }

    TEST(ClueOutputPlainTest, NoAnsiEscape) {
        EXPECT_EQ(std::string(cl::G_OK).find('\033'), std::string::npos);
        EXPECT_EQ(std::string(cl::G_WR).find('\033'), std::string::npos);
        EXPECT_EQ(std::string(cl::G_NO).find('\033'), std::string::npos);
        EXPECT_EQ(std::string(cl::G_FL).find('\033'), std::string::npos);
    }

    // --- highlight (ht) ---

    TEST(ClueOutputHighlightTest, GOkNonEmpty) {
        EXPECT_FALSE(std::string(cl::ht::G_OK).empty());
    }

    TEST(ClueOutputHighlightTest, GWrNonEmpty) {
        EXPECT_FALSE(std::string(cl::ht::G_WR).empty());
    }

    TEST(ClueOutputHighlightTest, GNoNonEmpty) {
        EXPECT_FALSE(std::string(cl::ht::G_NO).empty());
    }

    TEST(ClueOutputHighlightTest, GFlNonEmpty) {
        EXPECT_FALSE(std::string(cl::ht::G_FL).empty());
    }

    TEST(ClueOutputHighlightTest, GOkContainsLabel) {
        EXPECT_NE(std::string(cl::ht::G_OK).find("OK"), std::string::npos);
    }

    TEST(ClueOutputHighlightTest, GWrContainsLabel) {
        EXPECT_NE(std::string(cl::ht::G_WR).find("WR"), std::string::npos);
    }

    TEST(ClueOutputHighlightTest, GNoContainsLabel) {
        EXPECT_NE(std::string(cl::ht::G_NO).find("NO"), std::string::npos);
    }

    TEST(ClueOutputHighlightTest, GFlContainsLabel) {
        EXPECT_NE(std::string(cl::ht::G_FL).find("FL"), std::string::npos);
    }

    TEST(ClueOutputHighlightTest, ContainsAnsiEscape) {
        EXPECT_NE(std::string(cl::ht::G_OK).find('\033'), std::string::npos);
        EXPECT_NE(std::string(cl::ht::G_WR).find('\033'), std::string::npos);
        EXPECT_NE(std::string(cl::ht::G_NO).find('\033'), std::string::npos);
        EXPECT_NE(std::string(cl::ht::G_FL).find('\033'), std::string::npos);
    }

    // --- background (bg) ---

    TEST(ClueOutputBackgroundTest, GOkNonEmpty) {
        EXPECT_FALSE(std::string(cl::bg::G_OK).empty());
    }

    TEST(ClueOutputBackgroundTest, GWrNonEmpty) {
        EXPECT_FALSE(std::string(cl::bg::G_WR).empty());
    }

    TEST(ClueOutputBackgroundTest, GNoNonEmpty) {
        EXPECT_FALSE(std::string(cl::bg::G_NO).empty());
    }

    TEST(ClueOutputBackgroundTest, GFlNonEmpty) {
        EXPECT_FALSE(std::string(cl::bg::G_FL).empty());
    }

    TEST(ClueOutputBackgroundTest, GOkContainsLabel) {
        EXPECT_NE(std::string(cl::bg::G_OK).find("OK"), std::string::npos);
    }

    TEST(ClueOutputBackgroundTest, GWrContainsLabel) {
        EXPECT_NE(std::string(cl::bg::G_WR).find("WR"), std::string::npos);
    }

    TEST(ClueOutputBackgroundTest, GNoContainsLabel) {
        EXPECT_NE(std::string(cl::bg::G_NO).find("NO"), std::string::npos);
    }

    TEST(ClueOutputBackgroundTest, GFlContainsLabel) {
        EXPECT_NE(std::string(cl::bg::G_FL).find("FL"), std::string::npos);
    }

    TEST(ClueOutputBackgroundTest, ContainsAnsiEscape) {
        EXPECT_NE(std::string(cl::bg::G_OK).find('\033'), std::string::npos);
        EXPECT_NE(std::string(cl::bg::G_WR).find('\033'), std::string::npos);
        EXPECT_NE(std::string(cl::bg::G_NO).find('\033'), std::string::npos);
        EXPECT_NE(std::string(cl::bg::G_FL).find('\033'), std::string::npos);
    }

    // --- cross-namespace uniqueness ---

    TEST(ClueOutputUniquenessTest, HighlightVsPlainDifferent) {
        EXPECT_NE(std::string(cl::ht::G_OK), std::string(cl::G_OK));
        EXPECT_NE(std::string(cl::ht::G_WR), std::string(cl::G_WR));
        EXPECT_NE(std::string(cl::ht::G_NO), std::string(cl::G_NO));
        EXPECT_NE(std::string(cl::ht::G_FL), std::string(cl::G_FL));
    }

    TEST(ClueOutputUniquenessTest, BackgroundVsPlainDifferent) {
        EXPECT_NE(std::string(cl::bg::G_OK), std::string(cl::G_OK));
        EXPECT_NE(std::string(cl::bg::G_WR), std::string(cl::G_WR));
        EXPECT_NE(std::string(cl::bg::G_NO), std::string(cl::G_NO));
        EXPECT_NE(std::string(cl::bg::G_FL), std::string(cl::G_FL));
    }

    TEST(ClueOutputUniquenessTest, HighlightVsBackgroundDifferent) {
        EXPECT_NE(std::string(cl::ht::G_OK), std::string(cl::bg::G_OK));
        EXPECT_NE(std::string(cl::ht::G_WR), std::string(cl::bg::G_WR));
        EXPECT_NE(std::string(cl::ht::G_NO), std::string(cl::bg::G_NO));
        EXPECT_NE(std::string(cl::ht::G_FL), std::string(cl::bg::G_FL));
    }

    // --- severity-level uniqueness within each namespace ---

    TEST(ClueOutputUniquenessTest, PlainAllDifferent) {
        EXPECT_NE(std::string(cl::G_OK), std::string(cl::G_WR));
        EXPECT_NE(std::string(cl::G_OK), std::string(cl::G_NO));
        EXPECT_NE(std::string(cl::G_OK), std::string(cl::G_FL));
        EXPECT_NE(std::string(cl::G_WR), std::string(cl::G_NO));
        EXPECT_NE(std::string(cl::G_WR), std::string(cl::G_FL));
        EXPECT_NE(std::string(cl::G_NO), std::string(cl::G_FL));
    }

    TEST(ClueOutputUniquenessTest, HighlightAllDifferent) {
        EXPECT_NE(std::string(cl::ht::G_OK), std::string(cl::ht::G_WR));
        EXPECT_NE(std::string(cl::ht::G_OK), std::string(cl::ht::G_NO));
        EXPECT_NE(std::string(cl::ht::G_OK), std::string(cl::ht::G_FL));
        EXPECT_NE(std::string(cl::ht::G_WR), std::string(cl::ht::G_NO));
        EXPECT_NE(std::string(cl::ht::G_WR), std::string(cl::ht::G_FL));
        EXPECT_NE(std::string(cl::ht::G_NO), std::string(cl::ht::G_FL));
    }

    TEST(ClueOutputUniquenessTest, BackgroundAllDifferent) {
        EXPECT_NE(std::string(cl::bg::G_OK), std::string(cl::bg::G_WR));
        EXPECT_NE(std::string(cl::bg::G_OK), std::string(cl::bg::G_NO));
        EXPECT_NE(std::string(cl::bg::G_OK), std::string(cl::bg::G_FL));
        EXPECT_NE(std::string(cl::bg::G_WR), std::string(cl::bg::G_NO));
        EXPECT_NE(std::string(cl::bg::G_WR), std::string(cl::bg::G_FL));
        EXPECT_NE(std::string(cl::bg::G_NO), std::string(cl::bg::G_FL));
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    static auto splice(const std::string &hdr_, const std::string &msg_) -> std::string {
        std::stringstream ss;
        ss << hdr_ << msg_;
        return ss.str();
    };

    static void test_clue_output(const std::string &out_) {
        std::osyncstream(std::cout) << out_ << std::endl;
    }

    auto test_rstd_clue_output_main() -> int {
        kit::SafeMsg::get().println("func: ", "test rstd clue output");

        // visual output examples
        test_clue_output(splice(ruac::rstd::clue::ht::G_OK, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::ht::G_WR, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::ht::G_NO, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::ht::G_FL, "This is clue test output"));

        // not highlight
        test_clue_output(splice(ruac::rstd::clue::G_OK, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::G_WR, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::G_NO, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::G_FL, "This is clue test output"));

        // background
        test_clue_output(splice(ruac::rstd::clue::bg::G_OK, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::bg::G_WR, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::bg::G_NO, "This is clue test output"));
        test_clue_output(splice(ruac::rstd::clue::bg::G_FL, "This is clue test output"));

        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
