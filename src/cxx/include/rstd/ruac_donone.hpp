/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/ruac_donone.hpp
 * src/rstd/ruac_donone.cpp
 *
 * @brief Provides null utility functions for default initialization and fallback scenarios.
 */

#pragma once
#ifndef RUAC_DONEONE_HPP
#define RUAC_DONEONE_HPP

#include <string>

namespace ruac::rstd {

    namespace donone {

        auto null_string() -> std::string;

        void notdo();

    } // namespace donone

} // namespace ruac::rstd

#endif // RUAC_DONEONE_HPP
