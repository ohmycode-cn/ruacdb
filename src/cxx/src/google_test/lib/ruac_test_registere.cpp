/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_registere.hpp
 * src/google_test/lib/ruac_test_registere.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_registere.hpp"

#include "gtest/gtest.h"
#include "system/user/ruac_group.hpp"
#include "system/user/ruac_id.hpp"
#include "system/user/ruac_name.hpp"

namespace {

    using ruac::system::user::UserId;
    using ruac::system::user::UserGroup;
    using ruac::system::user::UserName;

    TEST(RegistereTest, DefaultUsersExist) {
        EXPECT_NE(UserId::instance().get_user_id("syst"), -1);
        EXPECT_NE(UserId::instance().get_user_id("root"), -1);
        EXPECT_NE(UserId::instance().get_user_id("live"), -1);
    }

    TEST(RegistereTest, DefaultUserIds) {
        EXPECT_EQ(UserId::instance().get_user_id("syst"), 0);
        EXPECT_EQ(UserId::instance().get_user_id("root"), 1);
        EXPECT_EQ(UserId::instance().get_user_id("live"), 2);
    }

    TEST(RegistereTest, NonexistentUserReturnsNegative) {
        EXPECT_EQ(UserId::instance().get_user_id("nonexistent_user_xyz"), -1);
    }

    TEST(RegistereTest, DefaultGroups) {
        EXPECT_EQ(UserGroup::instance().get_group("syst"), "syst");
        EXPECT_EQ(UserGroup::instance().get_group("root"), "root");
        EXPECT_EQ(UserGroup::instance().get_group("live"), "visitor");
    }

    TEST(RegistereTest, NonexistentGroupReturnsEmpty) {
        EXPECT_EQ(UserGroup::instance().get_group("nonexistent_user_xyz"), "");
    }

    TEST(RegistereTest, GetUserNameById) {
        EXPECT_EQ(UserId::instance().get_user_name(0), "syst");
        EXPECT_EQ(UserId::instance().get_user_name(1), "root");
        EXPECT_EQ(UserId::instance().get_user_name(2), "live");
    }

    TEST(RegistereTest, NonexistentIdReturnsEmpty) {
        EXPECT_EQ(UserId::instance().get_user_name(9999), "");
    }

    TEST(RegistereTest, UsersMapNotEmpty) {
        auto map = UserId::instance().get_users_map();
        EXPECT_FALSE(map.empty());
        EXPECT_GE(map.size(), 3u);
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_registere_main() -> int {
        kit::SafeMsg::get().println("func: ", "test registere");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
