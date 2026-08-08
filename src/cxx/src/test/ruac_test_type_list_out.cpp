/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_type_list_out.hpp
 * src/test/ruac_test_type_list_out.cpp
 */

#include "test/ruac_test_type_list_out.hpp"
#include "rstd/colors/ruac_ansi.hpp"
#include <iostream>

namespace ruac::test {

    namespace {

        namespace clr = ruac::rstd::colors::ansi;

        /**
         * @brief Render a 3x2 ASCII table using basic table_item glyphs
         *
         * @details Streams a 3-column, 2-row ASCII table to std::cout
         *          using ruac::rstd::colors::ansi::table_item::basic
         *          cross and line characters. Column headers are
         *          "Col1", "Col2", "Col3" and data rows are "A B C"
         *          and "D E F".
         *
         */
        void test_out_line_basic() {
            namespace T = clr::table_item::basic;
            std::cout << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << "\n";
            std::cout << T::G_VLINE << " Col1 " << T::G_VLINE << " Col2 "
                      << T::G_VLINE << " Col3 " << T::G_VLINE << "\n";
            std::cout << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << "\n";
            std::cout << T::G_VLINE << " A    " << T::G_VLINE << " B    "
                      << T::G_VLINE << " C    " << T::G_VLINE << "\n";
            std::cout << T::G_VLINE << " D    " << T::G_VLINE << " E    "
                      << T::G_VLINE << " F    " << T::G_VLINE << "\n";
            std::cout << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << std::endl;
        }

        /**
         * @brief Render a 3x2 ASCII table using single_line glyphs
         *
         * @details Streams a 3-column, 2-row ASCII table to std::cout
         *          using ruac::rstd::colors::ansi::table_item::single_line
         *          corner, tee and line characters, producing a thin
         *          single-line bordered table.
         *
         */
        void test_out_line_single() {
            namespace T = clr::table_item::single_line;
            std::cout << T::G_TL << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TR << "\n";
            std::cout << T::G_VLINE << " Col1 " << T::G_VLINE << " Col2 "
                      << T::G_VLINE << " Col3 " << T::G_VLINE << "\n";
            std::cout << T::G_LM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_RM << "\n";
            std::cout << T::G_VLINE << " A    " << T::G_VLINE << " B    "
                      << T::G_VLINE << " C    " << T::G_VLINE << "\n";
            std::cout << T::G_VLINE << " D    " << T::G_VLINE << " E    "
                      << T::G_VLINE << " F    " << T::G_VLINE << "\n";
            std::cout << T::G_BL << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BR << std::endl;
        }

        /**
         * @brief Render a 3x2 ASCII table using double_line glyphs
         *
         * @details Streams a 3-column, 2-row ASCII table to std::cout
         *          using ruac::rstd::colors::ansi::table_item::double_line
         *          corner, tee and line characters, producing a
         *          double-line bordered table.
         *
         */
        void test_out_line_double() {
            namespace T = clr::table_item::double_line;
            std::cout << T::G_TL << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TR << "\n";
            std::cout << T::G_VLINE << " Col1 " << T::G_VLINE << " Col2 "
                      << T::G_VLINE << " Col3 " << T::G_VLINE << "\n";
            std::cout << T::G_LM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_RM << "\n";
            std::cout << T::G_VLINE << " A    " << T::G_VLINE << " B    "
                      << T::G_VLINE << " C    " << T::G_VLINE << "\n";
            std::cout << T::G_VLINE << " D    " << T::G_VLINE << " E    "
                      << T::G_VLINE << " F    " << T::G_VLINE << "\n";
            std::cout << T::G_BL << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BR << std::endl;
        }

        /**
         * @brief Render a 3x2 ASCII table using bold glyphs
         *
         * @details Streams a 3-column, 2-row ASCII table to std::cout
         *          using ruac::rstd::colors::ansi::table_item::bold
         *          corner, tee and line characters, producing a
         *          heavy/bold bordered table.
         *
         */
        void test_out_line_bold() {
            namespace T = clr::table_item::bold;
            std::cout << T::G_TL << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_TR << "\n";
            std::cout << T::G_VLINE << " Col1 " << T::G_VLINE << " Col2 "
                      << T::G_VLINE << " Col3 " << T::G_VLINE << "\n";
            std::cout << T::G_LM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_CROSS << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_RM << "\n";
            std::cout << T::G_VLINE << " A    " << T::G_VLINE << " B    "
                      << T::G_VLINE << " C    " << T::G_VLINE << "\n";
            std::cout << T::G_VLINE << " D    " << T::G_VLINE << " E    "
                      << T::G_VLINE << " F    " << T::G_VLINE << "\n";
            std::cout << T::G_BL << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BM << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_HLINE << T::G_HLINE << T::G_HLINE
                      << T::G_BR << std::endl;
        }

        /**
         * @brief Render a 3x2 ASCII table using mixed glyphs
         *
         * @details Streams a 3-column, 2-row ASCII table to std::cout
         *          using ruac::rstd::colors::ansi::table_item::mixed
         *          glyphs, combining double-line horizontal segments
         *          with single-line vertical segments.
         *
         */
        void test_out_line_mixed() {
            namespace M = clr::table_item::mixed;
            std::cout << M::G_TL_SL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_TM_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_TM_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_TR_SL << "\n";
            std::cout << M::G_VLINE_SL << " Col1 " << M::G_VLINE_SL
                      << " Col2 " << M::G_VLINE_SL << " Col3 "
                      << M::G_VLINE_SL << "\n";
            std::cout << M::G_LM_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_CROSS_SD << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_CROSS_SD << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_RM_DL << "\n";
            std::cout << M::G_VLINE_SL << " A    " << M::G_VLINE_SL
                      << " B    " << M::G_VLINE_SL << " C    "
                      << M::G_VLINE_SL << "\n";
            std::cout << M::G_VLINE_SL << " D    " << M::G_VLINE_SL
                      << " E    " << M::G_VLINE_SL << " F    "
                      << M::G_VLINE_SL << "\n";
            std::cout << M::G_BL_SL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_BM_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_BM_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL << M::G_HLINE_DL << M::G_HLINE_DL
                      << M::G_HLINE_DL
                      << M::G_BR_SL << std::endl;
        }

    }; // namespace

    /**
     * @brief Run every ASCII table rendering test case
     *
     * @details Sequentially invokes test_out_line_basic(),
     *          test_out_line_single(), test_out_line_double(),
     *          test_out_line_bold() and test_out_line_mixed(),
     *          printing a labelled separator header before each one.
     *
     */
    void test_main_type_list_out() {
        std::cout << "=== basic ===" << std::endl;
        test_out_line_basic();
        std::cout << "\n=== single_line ===" << std::endl;
        test_out_line_single();
        std::cout << "\n=== double_line ===" << std::endl;
        test_out_line_double();
        std::cout << "\n=== bold ===" << std::endl;
        test_out_line_bold();
        std::cout << "\n=== mixed (double-h single-v) ===" << std::endl;
        test_out_line_mixed();
    }

} // namespace ruac::test
