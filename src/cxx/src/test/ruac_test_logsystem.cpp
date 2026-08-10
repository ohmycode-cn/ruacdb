/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_logsystem.hpp
 * src/test/ruac_test_logsystem.cpp
 */

#include "rstd/logsystem/ruac_api_log_runtime.hpp"
#include "rstd/logsystem/ruac_format_json.hpp"
#include "rstd/logsystem/ruac_format_text.hpp"
#include "rstd/logsystem/ruac_format_xml.hpp"
#include "rstd/logsystem/ruac_output_file.hpp"
#include "rstd/logsystem/ruac_allocator.hpp"
#include "rstd/logsystem/ruac_message.hpp"
#include "rstd/logsystem/ruac_logtime.hpp"
#include "rstd/logsystem/ruac_logmaps.hpp"
#include "rstd/logsystem/ruac_debugt.hpp"
#include "rstd/logsystem/ruac_loader.hpp"
#include "test/ruac_test_logsystem.hpp"
#include <iostream>
#include <sstream>

namespace {

    namespace logsys = ruac::rstd::logsystem;

    /**
     * @brief Render five log levels through the JSON formatter
     *
     * @details Constructs a logsys::FormatJson formatter and obtains an
     *          ANSI map plus the current time. Formats a fixed message
     *          at the DEBUG, INFO, WARNING, ERROR and FATAL levels
     *          (with codes 12002-12006), capturing the source file and
     *          line, and streams each formatted record to std::cout.
     *
     */
    [[maybe_unused]] void test_format_json() {
        logsys::FormatJson josn;
        const auto map{logsys::logmaps::get_ansi_map(true, true, false)};
        const auto time{logsys::logtime::get_time()};
        constexpr auto message{"This is format json message !"};
        const auto str0 = josn.format(map, time, "DEBUG", 12002, message,
                                      __FILE__, __LINE__);
        const auto str1 = josn.format(map, time, "INFO", 12003, message,
                                      __FILE__, __LINE__);
        const auto str2 = josn.format(map, time, "WARNING", 12004, message,
                                      __FILE__, __LINE__);
        const auto str3 = josn.format(map, time, "ERROR", 12005, message,
                                      __FILE__, __LINE__);
        const auto str4 = josn.format(map, time, "FATAL", 12006, message,
                                      __FILE__, __LINE__);
        std::cout << str0 << "\n";
        std::cout << str1 << "\n";
        std::cout << str2 << "\n";
        std::cout << str3 << "\n";
        std::cout << str4 << std::endl;
    }

    /**
     * @brief Render five log levels through the plain text formatter
     *
     * @return std::string - newline-joined formatted log records
     *
     * @details Constructs a logsys::FormatText formatter and obtains an
     *          ANSI map (without background colours) plus the current
     *          time. Formats a fixed message at the DEBUG, INFO,
     *          WARNING, ERROR and FATAL levels (codes 12002-12006) with
     *          the originating file and line, accumulates them into a
     *          stringstream, and returns the joined string.
     *
     */
    [[maybe_unused]] auto test_format_text() -> std::string {
        logsys::FormatText text;
        std::stringstream ss;
        auto map{logsys::logmaps::get_ansi_map(true, false, false)};
        auto time{logsys::logtime::get_time()};
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

    /**
     * @brief Render five log levels through the XML formatter
     *
     * @details Constructs a logsys::FormatXML formatter and obtains an
     *          ANSI map plus the current time. Formats a fixed message
     *          at the DEBUG, INFO, WARNING, ERROR and FATAL levels
     *          (codes 12002-12006), capturing the source file and line,
     *          and streams each formatted record to std::cout.
     *
     */
    [[maybe_unused]] void test_format_xml() {
        logsys::FormatXML xml;
        const auto map{logsys::logmaps::get_ansi_map(true, true, false)};
        const auto time{logsys::logtime::get_time()};
        constexpr auto message{"This is format XML message !"};
        const auto str0 = xml.format(map, time, "DEBUG", 12002, message,
                                     __FILE__, __LINE__);
        const auto str1 = xml.format(map, time, "INFO", 12003, message,
                                     __FILE__, __LINE__);
        const auto str2 = xml.format(map, time, "WARNING", 12004, message,
                                     __FILE__, __LINE__);
        const auto str3 = xml.format(map, time, "ERROR", 12005, message,
                                     __FILE__, __LINE__);
        const auto str4 = xml.format(map, time, "FATAL", 12006, message,
                                     __FILE__, __LINE__);
        std::cout << str0 << "\n";
        std::cout << str1 << "\n";
        std::cout << str2 << "\n";
        std::cout << str3 << "\n";
        std::cout << str4 << std::endl;
    }

    /**
     * @brief Exercise OutputFile error handling against a missing path
     *
     * @param message_ - text payload to attempt writing
     *
     * @details Enables colour output on the DebugT singleton, initialises
     *          the Message singleton, and constructs a logsys::OutputFile
     *          targeting a non-existent directory (/home/repox/Engdev/
     *          ruacdb/tmp/unexist) to verify the failure path when
     *          attempting to output message_.
     *
     */
    [[maybe_unused]] void test_output_file(const std::string &message_) {
        logsys::DebugTParamList params;
        params.m_enable_color = true;
        logsys::DebugT::instance().set_param_mode(params);

        constexpr auto FILE_PATH_NOT_EXIST{"/home/repox/Engdev/ruacdb/tmp/unexist"};
        [[maybe_unused]] constexpr auto FILE_PATH{"/home/repox/Engdev/ruacdb/tmp/test"};
        constexpr auto FILE_NAME{"ruacdb.test.log.txt"};
        constexpr bool ENABLE_THREAD_SEPARATION_MODE{true};
        logsys::Message::instance().init({true, true, true});
        logsys::OutputFile file(FILE_PATH_NOT_EXIST,
                                FILE_NAME,
                                ENABLE_THREAD_SEPARATION_MODE);
        file.output(message_);
    }

    /**
     * @brief Load the log configuration file and dump its map
     *
     * @details Constructs a logsys::Loader bound to
     *          /home/repox/Engdev/ruacdb/document/config/ruacdb.log.conf,
     *          retrieves the parsed configuration map via getmap(), and
     *          prints it through loader.outmap().
     *
     */
    [[maybe_unused]] void test_loader() {
        logsys::Loader loader({"/home/repox/Engdev/ruacdb/document/config",
                               "ruacdb.log.conf"});
        auto map = loader.getmap();
        loader.outmap(map);
    }

    /**
     * @brief Construct a log Allocator and print its loader message
     *
     * @details Constructs a logsys::Allocator bound to
     *          /home/repox/Engdev/ruacdb/document/config/ruacdb.log.conf
     *          and invokes out_loader_msg() to emit the loader
     *          diagnostic message.
     *
     */
    [[maybe_unused]] void test_allocator() {
        logsys::Allocator allocator({"/home/repox/Engdev/ruacdb/document/config",
                                     "ruacdb.log.conf"});
        allocator.out_loader_msg();
    }

    /**
     * @brief Initialise the LogRuntime singleton and emit five log levels
     *
     * @details Initialises logsys::api::LogRuntime with the configuration
     *          file at /home/repox/Engdev/ruacdb/document/config/
     *          ruacdb.log.conf, applies a settings object, and emits a
     *          single message through each of the RUAC_RUNTIME_DEBUG,
     *          RUAC_RUNTIME_INFO, RUAC_RUNTIME_WARNING, RUAC_RUNTIME_ERROR
     *          and RUAC_RUNTIME_FATAL macros.
     *
     */
    void test_log_runtime() {
        logsys::api::LogRuntime::instance().init({"/home/repox/Engdev/ruacdb/document/config",
                                                  "ruacdb.log.conf"});
        logsys::api::LogRuntime::instance().setting({true});
        std::string message{"This is test log runtime message: +++++++> "};

        // DEBUG TO FATAL

        RUAC_RUNTIME_DEBUG(message + "DEBUG");
        RUAC_RUNTIME_INFO(message + "INFO");
        RUAC_RUNTIME_WARNING(message + "WARNING");
        RUAC_RUNTIME_ERROR(message + "ERROR");
        RUAC_RUNTIME_FATAL(message + "FATAL");
    }

} // namespace

namespace ruac::test {

    /**
     * @brief Entry point for the log system test suite
     *
     * @details Prints a startup banner to std::cout and invokes
     *          test_log_runtime() to exercise the runtime logging
     *          path. Several sibling format/output/loader/allocator
     *          invocations are commented out.
     *
     */
    void test_main_logsystem() {
        std::cout << "From C++ This is test main logsystem !" << std::endl;
        // std::cout << std::endl;
        // test_format_json();
        // std::cout << std::endl;
        // std::cout << test_format_text() << std::endl;
        // std::cout << std::endl;
        // test_format_xml();
        // test_output_file(test_format_text());
        // test_loader();
        // test_allocator();
        test_log_runtime();
    }

} // namespace ruac::test
