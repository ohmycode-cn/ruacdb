/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_kwenums.hpp
 * src/syntax_lite/tree/ruac_kwenums.cpp
 * Description of header file function declaration
 *
 */

#pragma once
#ifndef RUAC_KWENUMS_HPP
#define RUAC_KWENUMS_HPP

namespace ruac::syntax_lite::tree {

    namespace kwenums {

        enum class TokenType {
            IDENTIFIER = 0,
            KEYWORD_OBJECT,
            KEYWORD_ATTRIBUTE,
            KEYWORD_SYMBOL,
            KEYWORD_DATATYPE
        };

    } // namespace kwenums

} // namespace ruac::syntax_lite::tree

#endif // RUAC_KWENUMS_HPP
