/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/clue/ruac_clue.hpp
 * src/rstd/clue/ruac_clue.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_CLUE_HPP
#define RUAC_CLUE_HPP

namespace ruac::rstd::clue {

    namespace bg {

        constexpr const char *const G_OK{"[\033[42m OK \033[0m] "}; // highlight success background
        constexpr const char *const G_WR{"[\033[43m WR \033[0m] "}; // highlight warning background
        constexpr const char *const G_NO{"[\033[41m NO \033[0m] "}; // highlight error background
        constexpr const char *const G_FL{"[\033[45m FL \033[0m] "}; // highlight fatal error background

    } // namespace bg

    namespace ht {

        constexpr const char *const G_OK{"[ \033[32mOK\033[0m ] "}; // highlight success
        constexpr const char *const G_WR{"[ \033[33mWR\033[0m ] "}; // highlight warning
        constexpr const char *const G_NO{"[ \033[31mNO\033[0m ] "}; // highlight error
        constexpr const char *const G_FL{"[ \033[41mFL\033[0m ] "}; // highlight fatal error

    } // namespace ht

    constexpr const char *const G_OK{"[ OK ] "}; // success
    constexpr const char *const G_WR{"[ WR ] "}; // warning
    constexpr const char *const G_NO{"[ NO ] "}; // error
    constexpr const char *const G_FL{"[ FL ] "}; // fatal error

} // namespace ruac::rstd::clue

#endif // RUAC_CLUE_HPP
