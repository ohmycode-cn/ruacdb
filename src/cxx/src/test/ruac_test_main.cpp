/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_main.hpp
 * src/test/ruac_test_main.cpp
 */

#include "test/ruac_test_type_list_out.hpp"
#include "test/ruac_test_rstd_messages.hpp"
#include "test/ruac_test_logsystem.hpp"
#include "test/ruac_test_colors.hpp"
#include "test/ruac_test_main.hpp"
#include <iostream>

namespace ruac::test {

    void test_main(void) {
        std::cout << "From C++ This This is test main !" << std::endl;
        test_main_type_list_out();
        test_main_logsystem();
        test_main_colors();
        test_main_rstd_messages();
    }

} // namespace ruac::test
