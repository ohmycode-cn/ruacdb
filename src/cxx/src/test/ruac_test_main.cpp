/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_main.hpp
 * src/test/ruac_test_main.cpp
 */

#include "test/ruac_test_type_list_out.hpp" // IWYU pragma: keep
#include "test/ruac_test_rstd_messages.hpp" // IWYU pragma: keep
#include "test/ruac_test_logsystem.hpp"     // IWYU pragma: keep
#include "test/ruac_test_colors.hpp"        // IWYU pragma: keep
#include "test/ruac_test_lexer.hpp"         // IWYU pragma: keep
#include "test/ruac_test_main.hpp"          // IWYU pragma: keep
#include <iostream>

namespace ruac::test {

    /**
     * @brief Entry point for the ruac test suite
     *
     * @details Prints a startup banner to std::cout and invokes
     *          test_main_lexer() to run the lexer tests. Several
     *          sibling test entry points are commented out.
     *
     */
    void test_main() {
        std::cout << "From C++ This This is test main !" << std::endl;
        // test_main_type_list_out();
        // test_main_logsystem();
        // test_main_colors();
        // test_main_rstd_messages();
        test_main_lexer();
    }

} // namespace ruac::test
