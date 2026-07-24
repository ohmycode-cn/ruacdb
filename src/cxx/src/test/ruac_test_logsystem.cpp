/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_logsystem.hpp
 * src/test/ruac_test_logsystem.cpp
 */

#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_nowtime.hpp"
#include "rstd/logsystem/ruac_strmap.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include "test/ruac_test_logsystem.hpp"
#include <iostream>
#include <sstream>

namespace {

    namespace logsys = ruac::rstd::logsystem;

    void test_format_json(void) {
        logsys::FormatJson josn;
        auto map{logsys::strmap::get_ansi_map(true, true, false)};
        auto time{logsys::nowtime::get_time()};
        auto message{"This is format json message !"};
        auto str0 = josn.format(map, time, "DEBUG", 12002, message,
                                __FILE__, __LINE__);
        auto str1 = josn.format(map, time, "INFO", 12003, message,
                                __FILE__, __LINE__);
        auto str2 = josn.format(map, time, "WARNING", 12004, message,
                                __FILE__, __LINE__);
        auto str3 = josn.format(map, time, "ERROR", 12005, message,
                                __FILE__, __LINE__);
        auto str4 = josn.format(map, time, "FATAL", 12006, message,
                                __FILE__, __LINE__);
        std::cout << str0 << "\n";
        std::cout << str1 << "\n";
        std::cout << str2 << "\n";
        std::cout << str3 << "\n";
        std::cout << str4 << std::endl;
    }

    auto test_format_text(void) -> std::string {
        logsys::FormatText text;
        std::stringstream ss;
        auto map{logsys::strmap::get_ansi_map(true, false, false)};
        auto time{logsys::nowtime::get_time()};
        auto message{"This is format text message !"};
        auto str0 = text.format(map, time, "DEBUG", 12002, message,
                                __FILE__, __LINE__);
        auto str1 = text.format(map, time, "INFO", 12003, message,
                                __FILE__, __LINE__);
        auto str2 = text.format(map, time, "WARNING", 12004, message,
                                __FILE__, __LINE__);
        auto str3 = text.format(map, time, "ERROR", 12005, message,
                                __FILE__, __LINE__);
        auto str4 = text.format(map, time, "FATAL", 12006, message,
                                __FILE__, __LINE__);
        ss << str0 << "\n";
        ss << str1 << "\n";
        ss << str2 << "\n";
        ss << str3 << "\n";
        ss << str4;

        return ss.str();
    }

    void test_format_xml(void) {
        logsys::FormatXML xml;
        auto map{logsys::strmap::get_ansi_map(true, true, false)};
        auto time{logsys::nowtime::get_time()};
        auto message{"This is format XML message !"};
        auto str0 = xml.format(map, time, "DEBUG", 12002, message,
                               __FILE__, __LINE__);
        auto str1 = xml.format(map, time, "INFO", 12003, message,
                               __FILE__, __LINE__);
        auto str2 = xml.format(map, time, "WARNING", 12004, message,
                               __FILE__, __LINE__);
        auto str3 = xml.format(map, time, "ERROR", 12005, message,
                               __FILE__, __LINE__);
        auto str4 = xml.format(map, time, "FATAL", 12006, message,
                               __FILE__, __LINE__);
        std::cout << str0 << "\n";
        std::cout << str1 << "\n";
        std::cout << str2 << "\n";
        std::cout << str3 << "\n";
        std::cout << str4 << std::endl;
    }

    void test_output_file(const std::string &message_) {
        logsys::DebugTParamList params;
        params.m_enable_color = true;
        logsys::DebugT::instance().set_param_mode(params);

        const char *const FILE_PATH_NOT_EXIST{"/home/repox/Engdev/ruacdb/tmp/unexist"};
        const char *const FILE_PATH{"/home/repox/Engdev/ruacdb/tmp/test"};
        const char *const FILE_NAME{"ruacdb.test.log.txt"};
        const bool ENABLE_THREAD_SEPARATION_MODE{true};
        logsys::Message::instance().init({true, true, true});
        logsys::OutputFile file(FILE_PATH_NOT_EXIST,
                                FILE_NAME,
                                ENABLE_THREAD_SEPARATION_MODE);
        file.output(message_);
    }

} // namespace

namespace ruac::test {

    void test_main_logsystem(void) {
        std::cout << "From C++ This is test main logsystem !" << std::endl;
        std::cout << std::endl;
        test_format_json();
        std::cout << std::endl;
        std::cout << test_format_text() << std::endl;
        std::cout << std::endl;
        test_format_xml();
        test_output_file(test_format_text());
    }

} // namespace ruac::test
