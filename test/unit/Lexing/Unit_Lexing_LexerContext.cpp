#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Lexing/LexerContext.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

TEST(Unit_Lexing_LexerContext, Simple) {
  std::string str = "abcdefghi";
  std::stringstream ss(str);
  Source source(ss);
  std::vector<Token> toks;
  MessageContext msg;

  LexerContext ctx(source, toks);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'a');

  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'b');

  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'c');

  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'd');

  ctx.emit(TokenID::Symbol);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'd');

  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'e');

  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'f');

  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'g');

  ctx.skip();

  ctx.buffer('g');
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'g');

  ctx.buffer('h');
  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'h');

  ctx.buffer('i');
  ctx.eat();
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.get(), 'i');

  ctx.eat();
  ASSERT_FALSE(ctx.more());
  ASSERT_EQ(ctx.get(), 0);

  ctx.emit(TokenID::Int);

  ASSERT_EQ(toks.size(), 2);

  ASSERT_TRUE(toks[0].isGood());
  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_EQ(toks[0].getLength(), 3);
  ASSERT_STREQ(toks[0].getText().c_str(), "");

  ASSERT_TRUE(toks[1].isGood());
  ASSERT_EQ(toks[1].getID(), TokenID::Int);
  ASSERT_EQ(toks[1].getLength(), 3);
  ASSERT_STREQ(toks[1].getText().c_str(), "ghi");
}
