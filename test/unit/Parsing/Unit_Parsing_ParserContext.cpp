#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Parsing/ParserContext.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserContext, More) {
  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext c0(toks, 0);
  ASSERT_TRUE(c0.more());

  ParserContext c1(toks, 1);
  ASSERT_FALSE(c1.more());

  ParserContext c2(toks, 2);
  ASSERT_FALSE(c2.more());
}

TEST(Unit_Parsing_ParserContext, Get) {
  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext c0(toks, 0);
  ASSERT_EQ(c0.get().getID(), TokenID::Symbol);

  ParserContext c1(toks, 1);
  ASSERT_EQ(c1.get().getID(), TokenID::None);
}

TEST(Unit_Parsing_ParserContext, Eat) {
  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext c0(toks, 0);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Symbol);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
}

TEST(Unit_Parsing_ParserContext, Inject) {
  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext c0(toks, 0);
  c0.inject(TokenID::Add);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Add);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Symbol);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
  c0.inject(TokenID::Add);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Add);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
}

TEST(Unit_Parsing_ParserContext, Last) {
  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext c0(toks, 0);
  c0.inject(TokenID::Add);
  ASSERT_EQ(c0.last().getID(), TokenID::None);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Add);
  ASSERT_EQ(c0.last().getID(), TokenID::Add);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Symbol);
  ASSERT_EQ(c0.last().getID(), TokenID::Symbol);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_EQ(c0.last().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_EQ(c0.last().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
  c0.inject(TokenID::Add);
  ASSERT_TRUE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::Add);
  ASSERT_EQ(c0.last().getID(), TokenID::Add);
  ASSERT_FALSE(c0.more());
  ASSERT_EQ(c0.eat().getID(), TokenID::None);
  ASSERT_EQ(c0.last().getID(), TokenID::None);
  ASSERT_FALSE(c0.more());
}
