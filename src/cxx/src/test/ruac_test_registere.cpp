/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_registere.hpp
 * src/test/ruac_test_registere.cpp
 */

#include "test/ruac_test_registere.hpp"
#include "login/ruac_registered_user.hpp"

namespace ruac::test {

    namespace {

        void test_register() {
            ruac::login::RegisteredUser ru;
            ru.registere();
        }

    } // namespace

    void test_main_register() {
        test_register();
    }

} // namespace ruac::test
