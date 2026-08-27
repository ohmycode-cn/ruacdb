/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/ruac_google_test_headers.hpp
 * src/google_test/ruac_google_test_headers.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_GOOGLE_TEST_HEADERS_HPP
#define RUAC_GOOGLE_TEST_HEADERS_HPP

/**
 * Current file is aggregation files, include all google test headers.
 * But you must add "IWYU pragma: keep" to each header file disable unused warning.
 */

#include "google_test/lib/ruac_test_colors.hpp"           // IWYU pragma: keep
#include "google_test/lib/ruac_test_format_col.hpp"       // IWYU pragma: keep
#include "google_test/lib/ruac_test_format_row.hpp"       // IWYU pragma: keep
#include "google_test/lib/ruac_test_lexer.hpp"            // IWYU pragma: keep
#include "google_test/lib/ruac_test_logsystem.hpp"        // IWYU pragma: keep
#include "google_test/lib/ruac_test_registere.hpp"        // IWYU pragma: keep
#include "google_test/lib/ruac_test_rstd_messages.hpp"    // IWYU pragma: keep
#include "google_test/lib/ruac_test_type_list_out.hpp"    // IWYU pragma: keep
#include "google_test/lib/ruac_test_rstd_clue_output.hpp" // IWYU pragma: keep

#endif // RUAC_GOOGLE_TEST_HEADERS_HPP
