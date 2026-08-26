/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/ruac_google_test_main.hpp
 * src/google_test/ruac_google_test_main.cpp
 */

#include "google_test/ruac_google_test_headers.hpp" // IWYU pragma: keep [[WARN]]: Please remove this comment.
#include "google_test/ruac_google_test_main.hpp"

#include <iostream>
#include <sstream>
#include <syncstream>

namespace ruac::google_test {

    namespace u = ruac::google_test::lib;

    /**
     * @brief Run a single test-suite entry point, chaining pass/fail state
     *
     * @param ret_  - Cumulative result flag (pass-by-reference).
     *                Set to false on failure; when already false the
     *                function short-circuits and skips execution.
     * @param func_ - Pointer to a test-suite main function that returns
     *                0 on success, non-zero on failure.
     * @param file_ - Caller source file path (use __FILE__).
     * @param line_ - Caller source line number (use __LINE__).
     *
     * @return void
     *
     * @details If ret_ is already false a skip message is printed
     *          (thread-safe via std::osyncstream) containing file_ and
     *          line_ for diagnostics, and the function returns immediately.
     *          Otherwise func_() is invoked: a zero return sets ret_ to
     *          true, any non-zero return sets ret_ to false.
     *          This implements an AND-chain: once any suite fails all
     *          subsequent suites are skipped.
     *
     */
    void test_true_run(bool &ret_, int (*func_)(), const std::string &file_, const int line_) {

        if (ret_ == false) {
            {
                std::stringstream ss;
                ss << "test function failed: func is previous failed, file: " << file_ << ", line: " << line_;
                std::osyncstream(std::cout) << ss.str() << std::endl;
            }
            return;
        }

        if (0 == func_()) {
            ret_ = true;
        } else {
            ret_ = false;
        }
    }

    auto google_test_main() -> int {
        bool ret = true;
        test_true_run(ret, u::test_format_row_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_format_col_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_lexer_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_colors_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_logsystem_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_registere_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_rstd_messages_main, __FILE__, __LINE__);
        test_true_run(ret, u::test_type_list_out_main, __FILE__, __LINE__);
        if (ret == false) {
            return 1;
        }
        return 0;
    }

} // namespace ruac::google_test
