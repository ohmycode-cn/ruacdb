/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/ruac_google_test_main.hpp
 * src/google_test/ruac_google_test_main.cpp
 */

#include "google_test/ruac_google_test_headers.hpp"
#include "google_test/ruac_google_test_main.hpp"

namespace ruac::google_test {

    namespace u = ruac::google_test::lib;

    auto google_test_main() -> int {
        return u::test_format_row_main();
    }

} // namespace ruac::google_test
