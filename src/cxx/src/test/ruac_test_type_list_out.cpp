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

        void test_out_line_basic(void) {
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

        void test_out_line_single(void) {
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

        void test_out_line_double(void) {
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

        void test_out_line_bold(void) {
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

        void test_out_line_mixed(void) {
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
