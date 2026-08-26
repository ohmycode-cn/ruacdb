/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_logsystem.hpp
 * src/google_test/lib/ruac_test_logsystem.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_logsystem.hpp"

#include "gtest/gtest.h"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_logmaps.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"

namespace {

    namespace logsys = ruac::rstd::logsystem;

    TEST(LogsystemTest, FormatJsonDebugNonEmpty) {
        logsys::FormatJson json;
        const auto map{logsys::logmaps::get_ansi_map(true, true, false)};
        const auto time{logsys::logtime::get_time()};
        auto result = json.format(map, time, "DEBUG", 12002, "test msg",
                                  __FILE__, __LINE__);
        EXPECT_FALSE(result.empty());
    }

    TEST(LogsystemTest, FormatJsonAllLevels) {
        logsys::FormatJson json;
        const auto map{logsys::logmaps::get_ansi_map(true, true, false)};
        const auto time{logsys::logtime::get_time()};
        const char *levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
        for (int i = 0; i < 5; ++i) {
            auto result = json.format(map, time, levels[i], 12002 + i, "test",
                                      __FILE__, __LINE__);
            EXPECT_FALSE(result.empty()) << "Level " << levels[i] << " produced empty output";
        }
    }

    TEST(LogsystemTest, FormatTextNonEmpty) {
        logsys::FormatText text;
        const auto map{logsys::logmaps::get_ansi_map(true, false, false)};
        const auto time{logsys::logtime::get_time()};
        auto result = text.format(map, time, "INFO", 12003, "test msg",
                                  __FILE__, __LINE__);
        EXPECT_FALSE(result.empty());
    }

    TEST(LogsystemTest, FormatXmlNonEmpty) {
        logsys::FormatXML xml;
        const auto map{logsys::logmaps::get_ansi_map(true, true, false)};
        const auto time{logsys::logtime::get_time()};
        auto result = xml.format(map, time, "ERROR", 12005, "test msg",
                                 __FILE__, __LINE__);
        EXPECT_FALSE(result.empty());
    }

    TEST(LogsystemTest, DifferentLevelsDifferentOutput) {
        logsys::FormatJson json;
        const auto map{logsys::logmaps::get_ansi_map(true, true, false)};
        const auto time{logsys::logtime::get_time()};
        auto debug = json.format(map, time, "DEBUG", 12002, "msg", __FILE__, __LINE__);
        auto fatal = json.format(map, time, "FATAL", 12006, "msg", __FILE__, __LINE__);
        EXPECT_NE(debug, fatal);
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_logsystem_main() -> int {
        kit::SafeMsg::get().println("func: ", "test logsystem");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
