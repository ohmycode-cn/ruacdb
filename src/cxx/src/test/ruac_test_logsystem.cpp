/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_logsystem.hpp
 * src/test/ruac_test_logsystem.cpp
 */

#include "rstd/logsystem/ruac_format_json.hpp"
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

} // namespace

namespace ruac::test {

    void test_main_logsystem(void) {
        std::cout << "From C++ This is test main logsystem !" << std::endl;
        test_format_json();
    }

} // namespace ruac::test
