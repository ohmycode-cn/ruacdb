/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_rstd_messages.hpp
 * src/test/ruac_test_rstd_messages.cpp
 */

#include "rlib/ruac_tdebug.hpp"
#include "test/ruac_test_rstd_messages.hpp"

namespace ruac::test {
    namespace {

        /**
         * @brief Emit a sample message through the Info singleton
         *
         * @details Calls ruac::rlib::tdebug::Info::get().print
         *          with a fixed test string to verify the standard
         *          message output path.
         *
         */
        void base_output() {
            auto &u = ruac::rlib::tdebug::Info::get();
            std::string msg{"This is rstd gen base output"};
            auto str = u.fmt("Test", "base_output", std::move(msg));
            u.print(str, __FILE__, __LINE__);
        }

    } // namespace

    /**
     * @brief Drive the rstd gen test case
     *
     * @details Delegates to base_output() to exercise the Info
     *          singleton print path.
     *
     */
    void test_main_rstd_messages() {
        base_output();
    }

} // namespace ruac::test
