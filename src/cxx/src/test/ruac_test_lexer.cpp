/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/test/ruac_test_lexer.hpp
 * src/test/ruac_test_lexer.cpp
 */

#include "rstd/ruac_lowercase_characters.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"
#include "test/ruac_test_lexer.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ruac::test {

    namespace {

        /**
         * @brief Exercise the Lexer with three sample SQL lines
         *
         * @details Feeds three sample SQL statements ("SELECT * FROM user;",
         *          "SHOW DATABASES;", "USE DATABASE test;") into a
         *          ruac::syntax_lite::tree::Lexer. Each line is first
         *          lowercased via ruac::rstd::lowercase_characters::tolower
         *          and then parsed with parse_line. For every produced
         *          token the type id (cast to int) and value are streamed
         *          to std::cout, prefixed by the originating line id.
         *
         */
        void test_read_token() {

            std::vector<std::string> lines{
                "SELECT * FROM user;",
                "SHOW DATABASES;",
                "USE DATABASE test;"};

            ruac::syntax_lite::tree::Lexer lexer;

            for (std::size_t line_id{0}; line_id < lines.size(); ++line_id) {
                ruac::rstd::lowercase_characters::tolower(lines[line_id]);
                lexer.tokenize(lines[line_id]);
                std::stringstream ss;
                ss << "Line ID: " << line_id << " -> [\n";
                for (const auto &token : lexer.tokens()) {
                    ss << "    Token Type ID: " << static_cast<int>(token.type) << "\n"
                       << "    Token Value  : " << token.value << "\n";
                }
                ss << "]\n";
                std::cout << ss.str() << std::endl;
            }
        }

    } // namespace

    /**
     * @brief Drive the lexer test cases
     *
     * @details Delegates to test_read_token() to run the SQL token
     *          parsing scenarios.
     *
     */
    [[maybe_unused]] void test_main_lexer() {
        test_read_token();
    }

} // namespace ruac::test
