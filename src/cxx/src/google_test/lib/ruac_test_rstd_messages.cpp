/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_rstd_messages.hpp
 * src/google_test/lib/ruac_test_rstd_messages.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_rstd_messages.hpp"

#include "gtest/gtest.h"
#include "rlib/ruac_tdebug.hpp"

namespace {

    TEST(RstdMessagesTest, SingletonExists) {
        auto &info = ruac::rlib::tdebug::Info::get();
        (void)info;
        SUCCEED();
    }

    TEST(RstdMessagesTest, FmtReturnsNonEmpty) {
        auto &info = ruac::rlib::tdebug::Info::get();
        auto str = info.fmt("TestClass", "test_func", "test message");
        EXPECT_FALSE(str.empty());
    }

    TEST(RstdMessagesTest, FmtContainsClassName) {
        auto &info = ruac::rlib::tdebug::Info::get();
        auto str = info.fmt("MyClass", "my_func", "hello");
        EXPECT_NE(str.find("MyClass"), std::string::npos);
    }

    TEST(RstdMessagesTest, FmtContainsFuncName) {
        auto &info = ruac::rlib::tdebug::Info::get();
        auto str = info.fmt("MyClass", "my_func", "hello");
        EXPECT_NE(str.find("my_func"), std::string::npos);
    }

    TEST(RstdMessagesTest, FmtContainsMessage) {
        auto &info = ruac::rlib::tdebug::Info::get();
        auto str = info.fmt("MyClass", "my_func", "unique_test_msg_12345");
        EXPECT_NE(str.find("unique_test_msg_12345"), std::string::npos);
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_rstd_messages_main() -> int {
        kit::SafeMsg::get().println("func: ", "test rstd messages");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
