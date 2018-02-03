#include <gtest/gtest.h>

#include <whiskey/Source/Token.hpp>

using namespace whiskey;

TEST(Unit_Source_Token, LessThan) {
  ASSERT_FALSE(Token(1, 1, 0, TokenID::None) < Token(1, 1, 0, TokenID::None));
  ASSERT_TRUE(Token(1, 1, 0, TokenID::None) < Token(1, 2, 0, TokenID::None));
  ASSERT_TRUE(Token(1, 1, 0, TokenID::None) < Token(2, 1, 0, TokenID::None));
  ASSERT_TRUE(Token(1, 1, 0, TokenID::None) < Token(2, 2, 0, TokenID::None));
  ASSERT_FALSE(Token(2, 1, 0, TokenID::None) < Token(1, 1, 0, TokenID::None));
  ASSERT_TRUE(Token(2, 1, 0, TokenID::None) < Token(2, 2, 0, TokenID::None));
}
