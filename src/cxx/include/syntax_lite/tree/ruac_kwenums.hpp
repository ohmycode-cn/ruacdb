/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/syntax_lite/tree/ruac_kwenums.hpp
 * src/syntax_lite/tree/ruac_kwenums.cpp
 *
 * @brief Defines the TokenType enumeration for token classification.
 */

#pragma once
#ifndef RUAC_KWENUMS_HPP
#define RUAC_KWENUMS_HPP

namespace ruac::syntax_lite::tree {

    namespace kwenums {

        /**
         * @brief Enumeration of token type classifications.
         *
         * Defines the possible categories for tokens parsed from RUAC syntax input,
         * including identifiers, object keywords, attribute keywords, symbol keywords,
         * and datatype keywords.
         */
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
