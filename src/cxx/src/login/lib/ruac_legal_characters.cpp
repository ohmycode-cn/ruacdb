/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/login/lib/ruac_legal_characters.hpp
 * src/login/lib/ruac_legal_characters.cpp
 */

#include "login/lib/ruac_legal_characters.hpp"

#include <array>
#include <cstdint>

namespace ruac::login::lib {

    namespace {

        /**
         * @brief Build a compile-time lookup table of legal ASCII characters.
         *
         * @return std::array<uint8_t, 128> - Table where 1 indicates an
         *         allowed character and 0 indicates disallowed.
         *
         * @details Marks A-Z, a-z, 0-9, and the eight symbols
         *          @!%^&|?~ as legal (value 1); all other positions
         *          remain zero-initialized (illegal). Because the
         *          function is constexpr, the table is constructed at
         *          compile time and stored in the read-only segment.
         *
         */
        constexpr auto build_ascii_table() -> std::array<uint8_t, 128> {

            std::array<uint8_t, 128> t{};

            // A-Z: 0x41 ~ 0x5A
            for (unsigned c = 'A'; c <= 'Z'; ++c) {
                t[c] = 1;
            }
            // a-z: 0x61 ~ 0x7A
            for (unsigned c = 'a'; c <= 'z'; ++c) {
                t[c] = 1;
            }
            // 0-9: 0x30 ~ 0x39
            for (unsigned c = '0'; c <= '9'; ++c) {
                t[c] = 1;
            }
            // @!%^&|?~
            t['@'] = 1;  // 0x40
            t['!'] = 1;  // 0x21
            t['%'] = 1;  // 0x25
            t['^'] = 1;  // 0x5E
            t['&'] = 1;  // 0x26
            t['|'] = 1;  // 0x7C
            t['?'] = 1;  // 0x3F
            t['~'] = 1;  // 0x7E
            t['_'] = 1;  // 0x5F
            t['-'] = 1;  // 0x2D
            t['+'] = 1;  // 0x2B
            t['*'] = 1;  // 0x2A
            t['/'] = 1;  // 0x2F
            t['`'] = 1;  // 0x60
            t['\\'] = 1; // 0x5C
            t['"'] = 1;  // 0x22
            t['\''] = 1; // 0x27
            t[' '] = 1;  // 0x20

            return t;
        }

        constexpr auto ASCII_OK = build_ascii_table();

        /**
         * @brief Check whether a single character is in the legal set.
         *
         * @param c - ASCII character to validate.
         *
         * @return bool - true if c is a legal character; false otherwise.
         *
         * @details Performs a bounds check (c < 128) before indexing the
         *          compile-time ASCII_OK table to avoid out-of-range access.
         *
         */
        inline auto is_valid(char c) -> bool {
            if (static_cast<unsigned>(c) < 128 && ASCII_OK[static_cast<unsigned>(c)]) {
                return true;
            } else {
                return false;
            }
        }

    } // namespace

    /**
     * @brief Validate that every character in a string is legal.
     *
     * @param str_ - The string to inspect.
     *
     * @return bool - true if all characters pass the legal check;
     *                false if any character is invalid.
     *
     */
    auto legal_char(std::string &str_) -> bool {
        for (const char &i : str_) {
            if (!is_valid(i)) {
                return false;
            }
        }
        return true;
    }

} // namespace ruac::login::lib
