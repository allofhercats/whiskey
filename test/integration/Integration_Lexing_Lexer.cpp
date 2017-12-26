#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Integration_Lexing_Lexer, Empty) {
	Source src;
	src.loadString("", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, Whitespace) {
	Source src;
	src.loadString(" \n\r\t", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, UnexpectedChar) {
	Source src;
	src.loadString("`", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentLineEmpty) {
	Source src;
	src.loadString("#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentLine) {
	Source src;
	src.loadString("#asdf", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentLineMultiple) {
	Source src;
	src.loadString("#asdf\n#asdf\n#asdf", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentLineNested) {
	Source src;
	src.loadString("####", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockEmpty) {
	Source src;
	src.loadString("#{}#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlock) {
	Source src;
	src.loadString("#{asdf}#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockNested_0) {
	Source src;
	src.loadString("#{#{asdf}#}#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockNested_1) {
	Source src;
	src.loadString("#{#{#{}##{}#}##{#{}##{}#}##{#{#{}##{}#}#}#}#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockNested_2) {
	Source src;
	src.loadString("#{#}#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockMismatched_0) {
	Source src;
	src.loadString("#{asdf}", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockMismatched_1) {
	Source src;
	src.loadString("#{asdf", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, CommentBlockMismatched_2) {
	Source src;
	src.loadString("#{#{asdf}#", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, Symbol_1) {
	Source src;
	src.loadString("x", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "x");
}

TEST(Integration_Lexing_Lexer, Symbol_2) {
	Source src;
	src.loadString("asdf", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "asdf");
}

TEST(Integration_Lexing_Lexer, Symbol_3) {
	Source src;
	src.loadString("x12309871", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "x12309871");
}

TEST(Integration_Lexing_Lexer, Symbol_4) {
	Source src;
	src.loadString("_12309871", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "_12309871");
}

TEST(Integration_Lexing_Lexer, Symbol_5) {
	Source src;
	src.loadString("x''''''", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "x''''''");
}

TEST(Integration_Lexing_Lexer, Symbol_6) {
	Source src;
	src.loadString("asdf''''''", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "asdf''''''");
}

TEST(Integration_Lexing_Lexer, Symbol_7) {
	Source src;
	src.loadString("x12309871''''''", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "x12309871''''''");
}

TEST(Integration_Lexing_Lexer, Symbol_8) {
	Source src;
	src.loadString("_12309871''''''", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Symbol);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "_12309871''''''");
}

TEST(Integration_Lexing_Lexer, KWNot) {
	Source src;
	src.loadString("not", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::KWNot);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "not");
}

TEST(Integration_Lexing_Lexer, Int_0) {
	Source src;
	src.loadString("0", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Int);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "0");
}

TEST(Integration_Lexing_Lexer, Int_1) {
	Source src;
	src.loadString("5018238971", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Int);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "5018238971");
}

TEST(Integration_Lexing_Lexer, Int_2) {
	Source src;
	src.loadString("5asdfkjsdf", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Int);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "5asdfkjsdf");
}

TEST(Integration_Lexing_Lexer, Float_0) {
	Source src;
	src.loadString("0.0", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Float);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "0.0");
}

TEST(Integration_Lexing_Lexer, Float_1) {
	Source src;
	src.loadString("5018238971.0", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Float);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "5018238971.0");
}

TEST(Integration_Lexing_Lexer, Float_2) {
	Source src;
	src.loadString("5asdfkjsdf.0", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Float);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "5asdfkjsdf.0");
}

TEST(Integration_Lexing_Lexer, Float_3) {
	Source src;
	src.loadString("5asdfkjsdf.0faljkhasdkfjhsadkfh", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Float);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "5asdfkjsdf.0faljkhasdkfjhsadkfh");
}

TEST(Integration_Lexing_Lexer, Float_4) {
	Source src;
	src.loadString(".0", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Float);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ".0");
}

TEST(Integration_Lexing_Lexer, Float_5) {
	Source src;
	src.loadString(".0faljkhasdkfjhsadkfh", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Float);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ".0faljkhasdkfjhsadkfh");
}

TEST(Integration_Lexing_Lexer, Char_0) {
	Source src;
	src.loadString("'a'", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Char);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "'a'");
}

TEST(Integration_Lexing_Lexer, Char_1) {
	Source src;
	src.loadString("''", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Char);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "''");
}

TEST(Integration_Lexing_Lexer, Char_2) {
	Source src;
	src.loadString("'\\\\'", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Char);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "'\\\\'");
}

TEST(Integration_Lexing_Lexer, Char_3) {
	Source src;
	src.loadString("'\\''", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Char);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "'\\''");
}

TEST(Integration_Lexing_Lexer, Char_4) {
	Source src;
	src.loadString("'a", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, Char_5) {
	Source src;
	src.loadString("'\\'", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, Char_6) {
	Source src;
	src.loadString("'\"'", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Char);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "'\"'");
}

TEST(Integration_Lexing_Lexer, String_0) {
	Source src;
	src.loadString("\"a\"", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::String);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "\"a\"");
}

TEST(Integration_Lexing_Lexer, String_1) {
	Source src;
	src.loadString("\"\"", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::String);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "\"\"");
}

TEST(Integration_Lexing_Lexer, String_2) {
	Source src;
	src.loadString("\"\\\\\"", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	msgs.print(std::cout);

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::String);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "\"\\\\\"");
}

TEST(Integration_Lexing_Lexer, String_3) {
	Source src;
	src.loadString("\"\\\"\"", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::String);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "\"\\\"\"");
}

TEST(Integration_Lexing_Lexer, String_4) {
	Source src;
	src.loadString("\"a", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, String_5) {
	Source src;
	src.loadString("\"\\\"", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, String_6) {
	Source src;
	src.loadString("\"'\"", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::String);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "\"'\"");
}

TEST(Integration_Lexing_Lexer, LParen) {
	Source src;
	src.loadString("(", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::LParen);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "(");
}

TEST(Integration_Lexing_Lexer, RParen) {
	Source src;
	src.loadString(")", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::RParen);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ")");
}

TEST(Integration_Lexing_Lexer, LBracket) {
	Source src;
	src.loadString("[", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::LBracket);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "[");
}

TEST(Integration_Lexing_Lexer, RBracket) {
	Source src;
	src.loadString("]", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::RBracket);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "]");
}

TEST(Integration_Lexing_Lexer, LBrace) {
	Source src;
	src.loadString("{", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::LBrace);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "{");
}

TEST(Integration_Lexing_Lexer, RBrace) {
	Source src;
	src.loadString("}", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::RBrace);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "}");
}

TEST(Integration_Lexing_Lexer, Comma) {
	Source src;
	src.loadString(",", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Comma);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ",");
}

TEST(Integration_Lexing_Lexer, Semicolon) {
	Source src;
	src.loadString(";", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Semicolon);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ";");
}

TEST(Integration_Lexing_Lexer, Period) {
	Source src;
	src.loadString(".", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Period);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ".");
}

TEST(Integration_Lexing_Lexer, Add) {
	Source src;
	src.loadString("+", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Add);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "+");
}

TEST(Integration_Lexing_Lexer, Inc) {
	Source src;
	src.loadString("++", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Inc);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "++");
}

TEST(Integration_Lexing_Lexer, AddAssign) {
	Source src;
	src.loadString("+=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::AddAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "+=");
}

TEST(Integration_Lexing_Lexer, Sub) {
	Source src;
	src.loadString("-", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Sub);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "-");
}

TEST(Integration_Lexing_Lexer, Dec) {
	Source src;
	src.loadString("--", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Dec);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "--");
}

TEST(Integration_Lexing_Lexer, SubAssign) {
	Source src;
	src.loadString("-=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::SubAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "-=");
}

TEST(Integration_Lexing_Lexer, Mul) {
	Source src;
	src.loadString("*", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Mul);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "*");
}

TEST(Integration_Lexing_Lexer, Exp) {
	Source src;
	src.loadString("**", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Exp);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "**");
}

TEST(Integration_Lexing_Lexer, ExpAssign) {
	Source src;
	src.loadString("**=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::ExpAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "**=");
}

TEST(Integration_Lexing_Lexer, MulAssign) {
	Source src;
	src.loadString("*=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::MulAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "*=");
}

TEST(Integration_Lexing_Lexer, Div) {
	Source src;
	src.loadString("/", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Div);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "/");
}

TEST(Integration_Lexing_Lexer, DivInt) {
	Source src;
	src.loadString("//", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::DivInt);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "//");
}

TEST(Integration_Lexing_Lexer, DivIntAssign) {
	Source src;
	src.loadString("//=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::DivIntAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "//=");
}

TEST(Integration_Lexing_Lexer, DivReal) {
	Source src;
	src.loadString("/.", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::DivReal);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "/.");
}

TEST(Integration_Lexing_Lexer, DivRealAssign) {
	Source src;
	src.loadString("/.=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::DivRealAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "/.=");
}

TEST(Integration_Lexing_Lexer, DivAssign) {
	Source src;
	src.loadString("/=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::DivAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "/=");
}

TEST(Integration_Lexing_Lexer, Mod) {
	Source src;
	src.loadString("%", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Mod);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "%");
}

TEST(Integration_Lexing_Lexer, ModAssign) {
	Source src;
	src.loadString("%=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::ModAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "%=");
}

TEST(Integration_Lexing_Lexer, BitNot) {
	Source src;
	src.loadString("~", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitNot);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "~");
}

TEST(Integration_Lexing_Lexer, BitAnd) {
	Source src;
	src.loadString("&", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitAnd);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "&");
}

TEST(Integration_Lexing_Lexer, BitAndAssign) {
	Source src;
	src.loadString("&=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitAndAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "&=");
}

TEST(Integration_Lexing_Lexer, BitOr) {
	Source src;
	src.loadString("|", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitOr);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "|");
}

TEST(Integration_Lexing_Lexer, BitOrAssign) {
	Source src;
	src.loadString("|=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitOrAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "|=");
}

TEST(Integration_Lexing_Lexer, BitXor) {
	Source src;
	src.loadString("^", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitXor);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "^");
}

TEST(Integration_Lexing_Lexer, BitXorAssign) {
	Source src;
	src.loadString("^=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitXorAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "^=");
}

TEST(Integration_Lexing_Lexer, LT) {
	Source src;
	src.loadString("<", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::LT);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "<");
}

TEST(Integration_Lexing_Lexer, BitShL) {
	Source src;
	src.loadString("<<", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitShL);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "<<");
}

TEST(Integration_Lexing_Lexer, LE) {
	Source src;
	src.loadString("<=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::LE);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "<=");
}

TEST(Integration_Lexing_Lexer, LArrow) {
	Source src;
	src.loadString("<-", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::LArrow);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "<-");
}

TEST(Integration_Lexing_Lexer, BitShLAssign) {
	Source src;
	src.loadString("<<=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitShLAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "<<=");
}

TEST(Integration_Lexing_Lexer, GT) {
	Source src;
	src.loadString(">", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::GT);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ">");
}

TEST(Integration_Lexing_Lexer, BitShR) {
	Source src;
	src.loadString(">>", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitShR);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ">>");
}

TEST(Integration_Lexing_Lexer, GE) {
	Source src;
	src.loadString(">=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::GE);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ">=");
}

TEST(Integration_Lexing_Lexer, BitShRAssign) {
	Source src;
	src.loadString(">>=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BitShRAssign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), ">>=");
}

TEST(Integration_Lexing_Lexer, ExclamationPointAlone) {
	Source src;
	src.loadString("!", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 1);
	ASSERT_EQ(toks.size(), 0);
}

TEST(Integration_Lexing_Lexer, NE) {
	Source src;
	src.loadString("!=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::NE);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "!=");
}

TEST(Integration_Lexing_Lexer, Assign) {
	Source src;
	src.loadString("=", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::Assign);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "=");
}

TEST(Integration_Lexing_Lexer, EQ) {
	Source src;
	src.loadString("==", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::EQ);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "==");
}

TEST(Integration_Lexing_Lexer, BoolImplies) {
	Source src;
	src.loadString("=>", true);

	std::vector<Token> toks;
	MessageBuffer msgs;

	Lexer lexer(Location(src), toks, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);
	ASSERT_EQ(toks.size(), 1);

	ASSERT_EQ(toks[0].getID(), Token::BoolImplies);
	ASSERT_STREQ(toks[0].getRange().getText().c_str(), "=>");
}
