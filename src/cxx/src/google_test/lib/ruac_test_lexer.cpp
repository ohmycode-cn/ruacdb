/**
 * Style Guide: RUAC-CCXX-STYLE-GUIDE.md
 * File Rule: The code should wrap around 100 columns and force wrap around 120 columns
 * Author: ohmycode-cn(ohcode@163.com)
 * include/google_test/lib/ruac_test_lexer.hpp
 * src/google_test/lib/ruac_test_lexer.cpp
 */

#include "google_test/kit/ruac_safemsg.hpp"
#include "google_test/lib/ruac_test_lexer.hpp"

#include "gtest/gtest.h"
#include "rstd/convert/ruac_lowercase.hpp"
#include "syntax_lite/tree/ruac_lexer.hpp"

namespace {

    using ruac::syntax_lite::tree::Lexer;
    using ruac::syntax_lite::tree::token_type::TokenType;

    TEST(LexerTest, SelectStatement) {
        Lexer lexer;
        std::string line{"SELECT * FROM user;"};
        ruac::rstd::convert::lowercase::to_lower_string(line);
        lexer.tokenize(line);
        auto tokens = lexer.tokens();
        ASSERT_FALSE(tokens.empty());
        EXPECT_EQ(tokens.front().type, TokenType::KEYWORD_ATTRIBUTE);
    }

    TEST(LexerTest, ShowDatabases) {
        Lexer lexer;
        std::string line{"SHOW DATABASES;"};
        ruac::rstd::convert::lowercase::to_lower_string(line);
        lexer.tokenize(line);
        auto tokens = lexer.tokens();
        ASSERT_GE(tokens.size(), 2u);
        EXPECT_EQ(tokens[0].type, TokenType::KEYWORD_ATTRIBUTE);
        // Lexer splits on whitespace only; semicolon is part of the last token
        EXPECT_EQ(tokens[1].value, "databases;");
    }

    TEST(LexerTest, UseDatabase) {
        Lexer lexer;
        std::string line{"USE DATABASE test;"};
        ruac::rstd::convert::lowercase::to_lower_string(line);
        lexer.tokenize(line);
        auto tokens = lexer.tokens();
        ASSERT_GE(tokens.size(), 2u);
        EXPECT_EQ(tokens[0].type, TokenType::KEYWORD_ATTRIBUTE);
        EXPECT_EQ(tokens[1].type, TokenType::KEYWORD_OBJECT);
    }

    TEST(LexerTest, EmptyInput) {
        Lexer lexer;
        lexer.tokenize("");
        auto tokens = lexer.tokens();
        EXPECT_TRUE(tokens.empty());
    }

    TEST(LexerTest, WhitespaceOnly) {
        Lexer lexer;
        lexer.tokenize("   ");
        auto tokens = lexer.tokens();
        EXPECT_TRUE(tokens.empty());
    }

    TEST(LexerTest, SingleIdentifier) {
        Lexer lexer;
        lexer.tokenize("test_name");
        auto tokens = lexer.tokens();
        ASSERT_EQ(tokens.size(), 1u);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[0].value, "test_name");
    }

} // anonymous namespace

namespace ruac::google_test::lib {

    auto test_lexer_main() -> int {
        kit::SafeMsg::get().println("func: ", "test lexer");
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

} // namespace ruac::google_test::lib
