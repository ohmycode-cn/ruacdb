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
#include "rstd/logsystem/ruac_nowtime.hpp"
#include "rstd/logsystem/ruac_strmap.hpp"
#include "test/ruac_test_logsystem.hpp"
#include <iostream>

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

    void test_format_text(void) {
        logsys::FormatText text;
        auto map{logsys::strmap::get_ansi_map(true, true, false)};
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
        std::cout << str0 << "\n";
        std::cout << str1 << "\n";
        std::cout << str2 << "\n";
        std::cout << str3 << "\n";
        std::cout << str4 << std::endl;
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

} // namespace

namespace ruac::test {

    void test_main_logsystem(void) {
        std::cout << "From C++ This is test main logsystem !" << std::endl;
        std::cout << std::endl;
        test_format_json();
        std::cout << std::endl;
        test_format_text();
        std::cout << std::endl;
        test_format_xml();
    }

} // namespace ruac::test
