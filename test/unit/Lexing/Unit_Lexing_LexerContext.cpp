#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Lexing/LexerContext.hpp>
#include <whiskey/Messages/MessageBuffer.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

TEST(Unit_Lexing_LexerContext, Simple) {
  std::string str = "abcdefghi";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);
  std::vector<Token> toks;
  MessageBuffer *msgs = new MessageBuffer();

  LexerContext ctx(loc, toks, *msgs);

  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'a');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'b');
  ASSERT_FALSE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText(""));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'b');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'c');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("a"));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'c');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'd');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("ab"));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'd');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'e');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("abc"));

  ctx.emitToken(Token::Symbol);

  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'd');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'e');
  ASSERT_FALSE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText(""));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'e');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'f');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("d"));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'f');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'g');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("de"));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'g');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'h');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("def"));

  ctx.skipToken();

  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'g');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'h');
  ASSERT_FALSE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText(""));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'h');
  ASSERT_TRUE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 'i');
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("g"));

  ctx.eatChar();
  ASSERT_TRUE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 'i');
  ASSERT_FALSE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 0);
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("gh"));

  ctx.eatChar();
  ASSERT_FALSE(ctx.areMoreChars(0));
  ASSERT_EQ(ctx.getChar(0), 0);
  ASSERT_FALSE(ctx.areMoreChars(1));
  ASSERT_EQ(ctx.getChar(1), 0);
  ASSERT_TRUE(ctx.hasText());
  ASSERT_TRUE(ctx.hasText("ghi"));

  ctx.emitToken(Token::Int);

  ASSERT_EQ(toks.size(), 2);

  ASSERT_TRUE(toks[0].isGood());
  ASSERT_EQ(toks[0].getID(), Token::Symbol);
  ASSERT_EQ(toks[0].getRange().getLength(), 3);
  ASSERT_EQ(toks[0].getRange().getStart().getOffset(), 0);
  ASSERT_TRUE(toks[0].getRange().getText() == "abc");

  ASSERT_TRUE(toks[1].isGood());
  ASSERT_EQ(toks[1].getID(), Token::Int);
  ASSERT_EQ(toks[1].getRange().getLength(), 3);
  ASSERT_EQ(toks[1].getRange().getStart().getOffset(), 6);
  ASSERT_TRUE(toks[1].getRange().getText() == "ghi");

  delete msgs;
  delete src;
}
