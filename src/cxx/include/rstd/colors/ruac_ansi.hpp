/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/colors/ruac_ansi.hpp
 * src/rstd/colors/ruac_ansi.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_ANSI_HPP
#define RUAC_ANSI_HPP

namespace ruac::rstd::colors {

    namespace ansi {

        namespace htf {

            constexpr const char *const G_OLD_NASI{"\033"}; // "\033", htf::G_OLD_NASI, classic ESC escape sequence
            constexpr const char *const G_NEW_NASI{"\x1b"}; // "\x1b", htf::G_NEW_NASI, hex ESC escape sequence
            constexpr const char *const G_NOR_FONT{"[0;"};  // "[0;", htf::G_NOR_FONT, normal font weight prefix
            constexpr const char *const G_BLD_FONT{"[1;"};  // "[1;", htf::G_BLD_FONT, bold font weight prefix
            constexpr const char *const G_CHAR_M{"m"};      // "m", htf::G_CHAR_M, ANSI sequence terminator

        } // namespace htf

        namespace table_item {

            namespace basic {
                constexpr const char *const G_HLINE{"-"}; // "-", basic::G_HLINE, horizontal line
                constexpr const char *const G_VLINE{"|"}; // "|", basic::G_VLINE, vertical line
                constexpr const char *const G_CROSS{"+"}; // "+", basic::G_CROSS, cross intersection
                constexpr const char *const G_SPACE{" "}; // " ", basic::G_SPACE, space filler
            } // namespace basic

            namespace single_line {
                constexpr const char *const G_TL{"┌"};    // "┌", single_line::G_TL, top-left corner
                constexpr const char *const G_TR{"┐"};    // "┐", single_line::G_TR, top-right corner
                constexpr const char *const G_BL{"└"};    // "└", single_line::G_BL, bottom-left corner
                constexpr const char *const G_BR{"┘"};    // "┘", single_line::G_BR, bottom-right corner
                constexpr const char *const G_HLINE{"─"}; // "─", single_line::G_HLINE, horizontal line
                constexpr const char *const G_VLINE{"│"}; // "│", single_line::G_VLINE, vertical line
                constexpr const char *const G_CROSS{"┼"}; // "┼", single_line::G_CROSS, cross intersection
                constexpr const char *const G_LM{"├"};    // "├", single_line::G_LM, left-middle junction
                constexpr const char *const G_RM{"┤"};    // "┤", single_line::G_RM, right-middle junction
                constexpr const char *const G_TM{"┬"};    // "┬", single_line::G_TM, top-middle junction
                constexpr const char *const G_BM{"┴"};    // "┴", single_line::G_BM, bottom-middle junction
            } // namespace single_line

            namespace double_line {
                constexpr const char *const G_TL{"╔"};        // "╔", double_line::G_TL, top-left corner
                constexpr const char *const G_TR{"╗"};        // "╗", double_line::G_TR, top-right corner
                constexpr const char *const G_BL{"╚"};        // "╚", double_line::G_BL, bottom-left corner
                constexpr const char *const G_BR{"╝"};        // "╝", double_line::G_BR, bottom-right corner
                constexpr const char *const G_HLINE{"═"};     // "═", double_line::G_HLINE, horizontal line
                constexpr const char *const G_VLINE{"║"};     // "║", double_line::G_VLINE, vertical line
                constexpr const char *const G_CROSS{"╬"};     // "╬", double_line::G_CROSS, cross intersection
                constexpr const char *const G_LM{"╠"};        // "╠", double_line::G_LM, left-middle junction
                constexpr const char *const G_RM{"╣"};        // "╣", double_line::G_RM, right-middle junction
                constexpr const char *const G_TM{"╦"};        // "╦", double_line::G_TM, top-middle junction
                constexpr const char *const G_BM{"╩"};        // "╩", double_line::G_BM, bottom-middle junction
                constexpr const char *const G_SHD_CROSS{"╪"}; // "╪", double_line::G_SHD_CROSS, single-h double-v cross
            } // namespace double_line

            namespace mixed {
                constexpr const char *const G_TL_SL{"╒"};    // "╒", mixed::G_TL_SL, single-h double-v top-left corner
                constexpr const char *const G_TR_SL{"╕"};    // "╕", mixed::G_TR_SL, single-h double-v top-right corner
                constexpr const char *const G_BL_SL{"╘"};    // "╘", mixed::G_BL_SL, single-h double-v bottom-left corner
                constexpr const char *const G_BR_SL{"╛"};    // "╛", mixed::G_BR_SL, single-h double-v bottom-right corner
                constexpr const char *const G_TL_DL{"╓"};    // "╓", mixed::G_TL_DL, double-h single-v top-left corner
                constexpr const char *const G_TR_DL{"╖"};    // "╖", mixed::G_TR_DL, double-h single-v top-right corner
                constexpr const char *const G_BL_DL{"╙"};    // "╙", mixed::G_BL_DL, double-h single-v bottom-left corner
                constexpr const char *const G_BR_DL{"╜"};    // "╜", mixed::G_BR_DL, double-h single-v bottom-right corner
                constexpr const char *const G_LM_DL{"╞"};    // "╞", mixed::G_LM_DL, double-h single-v left-middle junction
                constexpr const char *const G_RM_DL{"╡"};    // "╡", mixed::G_RM_DL, double-h single-v right-middle junction
                constexpr const char *const G_LM_SD{"╟"};    // "╟", mixed::G_LM_SD, single-h double-v left-middle junction
                constexpr const char *const G_RM_SD{"╢"};    // "╢", mixed::G_RM_SD, single-h double-v right-middle junction
                constexpr const char *const G_TM_DL{"╤"};    // "╤", mixed::G_TM_DL, double-h single-v top-middle junction
                constexpr const char *const G_BM_DL{"╧"};    // "╧", mixed::G_BM_DL, double-h single-v bottom-middle junction
                constexpr const char *const G_TM_SD{"╥"};    // "╥", mixed::G_TM_SD, single-h double-v top-middle junction
                constexpr const char *const G_BM_SD{"╨"};    // "╨", mixed::G_BM_SD, single-h double-v bottom-middle junction
                constexpr const char *const G_CROSS_SD{"╪"}; // "╪", mixed::G_CROSS_SD, single-v double-h cross intersection
                constexpr const char *const G_CROSS_DS{"╫"}; // "╫", mixed::G_CROSS_DS, double-v single-h cross intersection
                constexpr const char *const G_HLINE_SL{"─"}; // "─", mixed::G_HLINE_SL, single horizontal line
                constexpr const char *const G_HLINE_DL{"═"}; // "═", mixed::G_HLINE_DL, double horizontal line
                constexpr const char *const G_VLINE_SL{"│"}; // "│", mixed::G_VLINE_SL, single vertical line
                constexpr const char *const G_VLINE_DL{"║"}; // "║", mixed::G_VLINE_DL, double vertical line
            } // namespace mixed

            namespace bold {
                constexpr const char *const G_TL{"┏"};    // "┏", bold::G_TL, top-left corner
                constexpr const char *const G_TR{"┓"};    // "┓", bold::G_TR, top-right corner
                constexpr const char *const G_BL{"┗"};    // "┗", bold::G_BL, bottom-left corner
                constexpr const char *const G_BR{"┛"};    // "┛", bold::G_BR, bottom-right corner
                constexpr const char *const G_HLINE{"━"}; // "━", bold::G_HLINE, horizontal line
                constexpr const char *const G_VLINE{"┃"}; // "┃", bold::G_VLINE, vertical line
                constexpr const char *const G_CROSS{"╋"}; // "╋", bold::G_CROSS, cross intersection
                constexpr const char *const G_LM{"┣"};    // "┣", bold::G_LM, left-middle junction
                constexpr const char *const G_RM{"┫"};    // "┫", bold::G_RM, right-middle junction
                constexpr const char *const G_TM{"┳"};    // "┳", bold::G_TM, top-middle junction
                constexpr const char *const G_BM{"┻"};    // "┻", bold::G_BM, bottom-middle junction
            } // namespace bold

        } // namespace table_item

    } // namespace ansi

} // namespace ruac::rstd::colors

#endif // RUAC_ANSI_HPP
