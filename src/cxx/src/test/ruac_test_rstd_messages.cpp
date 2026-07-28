/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_rstd_messages.hpp
 * src/test/ruac_test_rstd_messages.cpp
 */

#include "test/ruac_test_rstd_messages.hpp"
#include "rstd/messages/ruac_stdmsg.hpp"

namespace ruac::test {
    namespace {

        namespace {
            namespace t = ruac::rstd::messages;
        } // namespace

        void base_output(void) {
            t::StdMsg::instance().print("This is rstd messages base output");
        }

    } // namespace

    void test_main_rstd_messages(void) {
        base_output();
    }

} // namespace ruac::test
