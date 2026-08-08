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

        /**
         * @brief Emit a sample message through the StdMsg singleton
         *
         * @details Calls ruac::rstd::messages::StdMsg::instance().print
         *          with a fixed test string to verify the standard
         *          message output path.
         *
         */
        void base_output() {
            t::StdMsg::instance().print("This is rstd messages base output");
        }

    } // namespace

    /**
     * @brief Drive the rstd messages test case
     *
     * @details Delegates to base_output() to exercise the StdMsg
     *          singleton print path.
     *
     */
    void test_main_rstd_messages() {
        base_output();
    }

} // namespace ruac::test
