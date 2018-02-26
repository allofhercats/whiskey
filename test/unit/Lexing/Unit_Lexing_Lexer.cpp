#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <vector>

#include <whiskey/Lexing/LexerContext.hpp>
#include <whiskey/Lexing/Lexer.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Source/Source.hpp>
#include <whiskey/Source/Token.hpp>

using namespace whiskey;

TEST(Unit_Lexing_Lexer, Empty) {
  std::stringstream ss("");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, Whitespace) {
  std::stringstream ss(" \n\r\t");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, UnexpectedChar) {
  std::stringstream ss("`");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentLineEmpty) {
  std::stringstream ss("#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentLine) {
  std::stringstream ss("#asdf");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentLineMultiple) {
  std::stringstream ss("#asdf\n#asdf\n#asdf");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentLineNested) {
  std::stringstream ss("####");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockEmpty) {
  std::stringstream ss("#{}#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlock) {
  std::stringstream ss("#{asdf}#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockNested_0) {
  std::stringstream ss("#{#{asdf}#}#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockNested_1) {
  std::stringstream ss("#{#{#{}##{}#}##{#{}##{}#}##{#{#{}##{}#}#}#}#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockNested_2) {
  std::stringstream ss("#{#}#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockMismatched_0) {
  std::stringstream ss("#{asdf}");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockMismatched_1) {
  std::stringstream ss("#{asdf");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, CommentBlockMismatched_2) {
  std::stringstream ss("#{#{asdf}#");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, Symbol_1) {
  std::stringstream ss("x");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "x");
}

TEST(Unit_Lexing_Lexer, Symbol_2) {
  std::stringstream ss("asdf");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "asdf");
}

TEST(Unit_Lexing_Lexer, Symbol_3) {
  std::stringstream ss("x12309871");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "x12309871");
}

TEST(Unit_Lexing_Lexer, Symbol_4) {
  std::stringstream ss("_12309871");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "_12309871");
}

TEST(Unit_Lexing_Lexer, Symbol_5) {
  std::stringstream ss("x''''''");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "x''''''");
}

TEST(Unit_Lexing_Lexer, Symbol_6) {
  std::stringstream ss("asdf''''''");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "asdf''''''");
}

TEST(Unit_Lexing_Lexer, Symbol_7) {
  std::stringstream ss("x12309871''''''");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "x12309871''''''");
}

TEST(Unit_Lexing_Lexer, Symbol_8) {
  std::stringstream ss("_12309871''''''");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "_12309871''''''");
}

TEST(Unit_Lexing_Lexer, KWNot) {
  std::stringstream ss("not");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Symbol);
  ASSERT_STREQ(toks[0].getText().c_str(), "not");
}

TEST(Unit_Lexing_Lexer, Int_0) {
  std::stringstream ss("0");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Int);
  ASSERT_STREQ(toks[0].getText().c_str(), "0");
}

TEST(Unit_Lexing_Lexer, Int_1) {
  std::stringstream ss("5018238971");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Int);
  ASSERT_STREQ(toks[0].getText().c_str(), "5018238971");
}

TEST(Unit_Lexing_Lexer, Int_2) {
  std::stringstream ss("5asdfkjsdf");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Int);
  ASSERT_STREQ(toks[0].getText().c_str(), "5asdfkjsdf");
}

TEST(Unit_Lexing_Lexer, Real_0) {
  std::stringstream ss("0.0");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Real);
  ASSERT_STREQ(toks[0].getText().c_str(), "0.0");
}

TEST(Unit_Lexing_Lexer, Real_1) {
  std::stringstream ss("5018238971.0");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Real);
  ASSERT_STREQ(toks[0].getText().c_str(), "5018238971.0");
}

TEST(Unit_Lexing_Lexer, Real_2) {
  std::stringstream ss("5asdfkjsdf.0");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Real);
  ASSERT_STREQ(toks[0].getText().c_str(), "5asdfkjsdf.0");
}

TEST(Unit_Lexing_Lexer, Real_3) {
  std::stringstream ss("5asdfkjsdf.0faljkhasdkfjhsadkfh");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Real);
  ASSERT_STREQ(toks[0].getText().c_str(),
               "5asdfkjsdf.0faljkhasdkfjhsadkfh");
}

TEST(Unit_Lexing_Lexer, Real_4) {
  std::stringstream ss(".0");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Real);
  ASSERT_STREQ(toks[0].getText().c_str(), ".0");
}

TEST(Unit_Lexing_Lexer, Real_5) {
  std::stringstream ss(".0faljkhasdkfjhsadkfh");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Real);
  ASSERT_STREQ(toks[0].getText().c_str(), ".0faljkhasdkfjhsadkfh");
}

TEST(Unit_Lexing_Lexer, Char_0) {
  std::stringstream ss("'a'");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Char);
  ASSERT_STREQ(toks[0].getText().c_str(), "'a'");
}

TEST(Unit_Lexing_Lexer, Char_1) {
  std::stringstream ss("''");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Char);
  ASSERT_STREQ(toks[0].getText().c_str(), "''");
}

TEST(Unit_Lexing_Lexer, Char_2) {
  std::stringstream ss("'\\\\'");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Char);
  ASSERT_STREQ(toks[0].getText().c_str(), "'\\\\'");
}

TEST(Unit_Lexing_Lexer, Char_3) {
  std::stringstream ss("'\\''");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Char);
  ASSERT_STREQ(toks[0].getText().c_str(), "'\\''");
}

TEST(Unit_Lexing_Lexer, Char_4) {
  std::stringstream ss("'a");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, Char_5) {
  std::stringstream ss("'\\'");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, Char_6) {
  std::stringstream ss("'\"'");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Char);
  ASSERT_STREQ(toks[0].getText().c_str(), "'\"'");
}

TEST(Unit_Lexing_Lexer, String_0) {
  std::stringstream ss("\"a\"");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::String);
  ASSERT_STREQ(toks[0].getText().c_str(), "\"a\"");
}

TEST(Unit_Lexing_Lexer, String_1) {
  std::stringstream ss("\"\"");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::String);
  ASSERT_STREQ(toks[0].getText().c_str(), "\"\"");
}

TEST(Unit_Lexing_Lexer, String_2) {
  std::stringstream ss("\"\\\\\"");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::String);
  ASSERT_STREQ(toks[0].getText().c_str(), "\"\\\\\"");
}

TEST(Unit_Lexing_Lexer, String_3) {
  std::stringstream ss("\"\\\"\"");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::String);
  ASSERT_STREQ(toks[0].getText().c_str(), "\"\\\"\"");
}

TEST(Unit_Lexing_Lexer, String_4) {
  std::stringstream ss("\"a");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, String_5) {
  std::stringstream ss("\"\\\"");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, String_6) {
  std::stringstream ss("\"'\"");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::String);
  ASSERT_STREQ(toks[0].getText().c_str(), "\"'\"");
}

TEST(Unit_Lexing_Lexer, LParen) {
  std::stringstream ss("(");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::LParen);
}

TEST(Unit_Lexing_Lexer, RParen) {
  std::stringstream ss(")");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::RParen);
}

TEST(Unit_Lexing_Lexer, LBracket) {
  std::stringstream ss("[");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::LBracket);
}

TEST(Unit_Lexing_Lexer, RBracket) {
  std::stringstream ss("]");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::RBracket);
}

TEST(Unit_Lexing_Lexer, LBrace) {
  std::stringstream ss("{");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::LBrace);
}

TEST(Unit_Lexing_Lexer, RBrace) {
  std::stringstream ss("}");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::RBrace);
}

TEST(Unit_Lexing_Lexer, Comma) {
  std::stringstream ss(",");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Comma);
}

TEST(Unit_Lexing_Lexer, Semicolon) {
  std::stringstream ss(";");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Semicolon);
}

TEST(Unit_Lexing_Lexer, Period) {
  std::stringstream ss(".");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Period);
}

TEST(Unit_Lexing_Lexer, Add) {
  std::stringstream ss("+");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Add);
}

TEST(Unit_Lexing_Lexer, Inc) {
  std::stringstream ss("++");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Inc);
}

TEST(Unit_Lexing_Lexer, AddAssign) {
  std::stringstream ss("+=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::AddAssign);
}

TEST(Unit_Lexing_Lexer, Sub) {
  std::stringstream ss("-");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Sub);
}

TEST(Unit_Lexing_Lexer, Dec) {
  std::stringstream ss("--");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Dec);
}

TEST(Unit_Lexing_Lexer, SubAssign) {
  std::stringstream ss("-=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::SubAssign);
}

TEST(Unit_Lexing_Lexer, Mul) {
  std::stringstream ss("*");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Mul);
}

TEST(Unit_Lexing_Lexer, Exp) {
  std::stringstream ss("**");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Exp);
}

TEST(Unit_Lexing_Lexer, ExpAssign) {
  std::stringstream ss("**=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::ExpAssign);
}

TEST(Unit_Lexing_Lexer, MulAssign) {
  std::stringstream ss("*=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::MulAssign);
}

TEST(Unit_Lexing_Lexer, Div) {
  std::stringstream ss("/");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Div);
}

TEST(Unit_Lexing_Lexer, DivInt) {
  std::stringstream ss("//");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::DivInt);
}

TEST(Unit_Lexing_Lexer, DivIntAssign) {
  std::stringstream ss("//=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::DivIntAssign);
}

TEST(Unit_Lexing_Lexer, DivReal) {
  std::stringstream ss("/.");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::DivReal);
}

TEST(Unit_Lexing_Lexer, DivRealAssign) {
  std::stringstream ss("/.=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::DivRealAssign);
}

TEST(Unit_Lexing_Lexer, DivAssign) {
  std::stringstream ss("/=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::DivAssign);
}

TEST(Unit_Lexing_Lexer, Mod) {
  std::stringstream ss("%");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Mod);
}

TEST(Unit_Lexing_Lexer, ModAssign) {
  std::stringstream ss("%=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::ModAssign);
}

TEST(Unit_Lexing_Lexer, BitNot) {
  std::stringstream ss("~");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitNot);
}

TEST(Unit_Lexing_Lexer, BitAnd) {
  std::stringstream ss("&");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitAnd);
}

TEST(Unit_Lexing_Lexer, BitAndAssign) {
  std::stringstream ss("&=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitAndAssign);
}

TEST(Unit_Lexing_Lexer, BitOr) {
  std::stringstream ss("|");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitOr);
}

TEST(Unit_Lexing_Lexer, BitOrAssign) {
  std::stringstream ss("|=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitOrAssign);
}

TEST(Unit_Lexing_Lexer, BitXor) {
  std::stringstream ss("^");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitXor);
}

TEST(Unit_Lexing_Lexer, BitXorAssign) {
  std::stringstream ss("^=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitXorAssign);
}

TEST(Unit_Lexing_Lexer, LT) {
  std::stringstream ss("<");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::LT);
}

TEST(Unit_Lexing_Lexer, BitShL) {
  std::stringstream ss("<<");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitShL);
}

TEST(Unit_Lexing_Lexer, LE) {
  std::stringstream ss("<=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::LE);
}

TEST(Unit_Lexing_Lexer, LArrow) {
  std::stringstream ss("<-");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::LArrow);
}

TEST(Unit_Lexing_Lexer, BitShLAssign) {
  std::stringstream ss("<<=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitShLAssign);
}

TEST(Unit_Lexing_Lexer, GT) {
  std::stringstream ss(">");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::GT);
}

TEST(Unit_Lexing_Lexer, BitShR) {
  std::stringstream ss(">>");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitShR);
}

TEST(Unit_Lexing_Lexer, GE) {
  std::stringstream ss(">=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::GE);
}

TEST(Unit_Lexing_Lexer, BitShRAssign) {
  std::stringstream ss(">>=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BitShRAssign);
}

TEST(Unit_Lexing_Lexer, ExclamationPointAlone) {
  std::stringstream ss("!");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(toks.size(), 0);
}

TEST(Unit_Lexing_Lexer, NE) {
  std::stringstream ss("!=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::NE);
}

TEST(Unit_Lexing_Lexer, Assign) {
  std::stringstream ss("=");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::Assign);
}

TEST(Unit_Lexing_Lexer, EQ) {
  std::stringstream ss("==");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::EQ);
}

TEST(Unit_Lexing_Lexer, BoolImplies) {
  std::stringstream ss("=>");
  Source src(ss);

  std::vector<Token> toks;
  MessageContext msgs;

  LexerContext ctx(src, toks);
  Lexer lexer;

  lexer.lex(ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);
  ASSERT_EQ(toks.size(), 1);

  ASSERT_EQ(toks[0].getID(), TokenID::BoolImplies);
}
