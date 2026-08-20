/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/rstd/convert/ruac_rmspace.hpp
 * src/rstd/convert/ruac_rmspace.cpp
 *
 * @brief Declares the remove_string_spaces() utility function for in-place whitespace removal from strings.
 */

#pragma once
#ifndef RUAC_RMSPACE_HPP
#define RUAC_RMSPACE_HPP

#include <string>

namespace ruac::rstd::convert {

    namespace rmspace {

        void remove_string_spaces(std::string &str_);

    } // namespace rmspace

} // namespace ruac::rstd::convert

#endif // RUAC_RMSPACE_HPP
