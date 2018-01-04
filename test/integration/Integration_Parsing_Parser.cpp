#include <gtest/gtest.h>

#include <whiskey/Source/Source.hpp>
#include <whiskey/Source/Token.hpp>
#include <whiskey/Parsing/Parser.hpp>
#include <whiskey/Lexing/Lexer.hpp>
#include <whiskey/Messages/MessageBuffer.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Field.hpp>
#include <whiskey/Core/PrintLiterals.hpp>
#include <whiskey/Printing/DebugPrinter.hpp>

using namespace whiskey;

void testHelper(ParserContext::Rule rule,
                const char *text,
                std::initializer_list<Token::ID> tokenIDs,
                Node *node,
                bool success) {
  ASSERT_TRUE(rule);
  ASSERT_NE(text, nullptr);
  ASSERT_NE(text[0], 0);
  ASSERT_GT(tokenIDs.size(), 0);
  ASSERT_GE(strlen(text), tokenIDs.size());

  if (success) {
    ASSERT_NE(node, nullptr);
  }

  Source src;
  src.loadCString(text, 0, true);

  ASSERT_EQ(src.getLength(), strlen(text));

  Location loc(src);

  std::vector<Token> tokens;
  MessageBuffer msgs;

  Lexer lexer(loc, tokens, msgs);
  lexer.lex();

  ASSERT_EQ(msgs.getNMessages(), 0);

  std::vector<Token>::iterator tokenIter = tokens.begin();
  std::initializer_list<Token::ID>::iterator tokenIDIter = tokenIDs.begin();
  int index = 0;
  while (tokenIter != tokens.end() && tokenIDIter != tokenIDs.end()) {
    if (tokenIter->getID() != *tokenIDIter) {
      std::cout << "Tokens do not match: ";
      printLiteralString(std::cout, text);
      std::cout << "\n";
      std::cout << "  Expected[" << index << "] ";
      Token::printTokenIDDebug(std::cout, *tokenIDIter);
      std::cout << "\n";
      std::cout << "  Actual[" << index << "] ";
      tokenIter->printDebug(std::cout);
      std::cout << "\n";
      FAIL() << "Tokens do not match.";
    }

    tokenIter++;
    tokenIDIter++;
    index++;
  }

  if (tokens.size() != tokenIDs.size()) {
    tokenIter = tokens.begin();
    tokenIDIter = tokenIDs.begin();
    index = 0;

    std::cout << "Tokens do not match: ";
    printLiteralString(std::cout, text);
    std::cout << "\n\n";

    std::cout << "Expected (" << tokenIDs.size() << "):\n";
    while (tokenIDIter != tokenIDs.end()) {
      std::cout << "  ";
      Token::printTokenIDDebug(std::cout, *tokenIDIter);
      std::cout << "\n";
      tokenIDIter++;
    }

    std::cout << "\nActual (" << tokens.size() << "):\n";
    while (tokenIter != tokens.end()) {
      std::cout << "  ";
      tokenIter->printDebug(std::cout);
      std::cout << "\n";
      tokenIter++;
    }
    std::cout << "\n";

    FAIL() << "Tokens do not match";
  }

  ParserContext ctx(tokens, msgs);

  ParserResult res = rule(ctx);

  if (success) {
    if (!res.isGood()) {
      msgs.print(std::cout);
    }

    if (ctx.areMoreTokens()) {
      std::cout << "Not all tokens were parsed.\n\n";
      std::cout << "Remaining:\n";
      while (ctx.areMoreTokens()) {
        std::cout << "  ";
        ctx.getToken().printDebug(std::cout);
        ctx.eatToken();
        std::cout << "\n";
      }
      std::cout << "\n";
      FAIL() << "Not all tokens were parsed.";
    }

    ASSERT_TRUE(res.isGood());

    if ((node == nullptr) == (res.getNode() == nullptr) &&
        (node == nullptr || node->compare(res.getNode()))) {
      SUCCEED();
    } else {
      std::cout << "ASTs do not match.\n";

      DebugPrinter dp(2);

      std::cout << "\nExpected:";
      dp.printNewline(std::cout, 1);
      dp.print(std::cout, node, 1);

      std::cout << "\n\nActual:";
      dp.printNewline(std::cout, 1);
      dp.print(std::cout, res.getNode(), 1);
      std::cout << "\n\n";

      FAIL() << "ASTs do not match.";
    }
  } else if (!ctx.areMoreTokens()) {
    if (res.isGood()) {
      DebugPrinter dp(2);

      std::cout << "Unexpected:";
      dp.printNewline(std::cout, 1);
      dp.print(std::cout, res.getNode(), 1);
      std::cout << "\n\n";
    }

    ASSERT_FALSE(res.isGood());
  }
}

TEST(Integration_Parsing_Parser, ParseTypeSymbol_0) {
  testHelper(Parser::parseTypeSymbol,
             "x",
             {Token::Symbol},
             Node::createTypeSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeSymbol_1) {
  testHelper(Parser::parseTypeSymbol, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_0) {
  testHelper(Parser::parseTypeAccessUnary,
             ".x",
             {Token::Period, Token::Symbol},
             Node::createTypeAccessUnary(
                 Node::createTypeSymbol(Field::createString8("x"))),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_1) {
  testHelper(Parser::parseTypeAccessUnary,
             "..x",
             {Token::Period, Token::Period, Token::Symbol},
             Node::createTypeAccessUnary(Node::createTypeAccessUnary(
                 Node::createTypeSymbol(Field::createString8("x")))),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_2) {
  testHelper(Parser::parseTypeAccessUnary,
             "x",
             {Token::Symbol},
             Node::createTypeSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_3) {
  testHelper(
      Parser::parseTypeAccessUnary, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_0) {
  testHelper(Parser::parseTypeAccess,
             "x.y",
             {Token::Symbol, Token::Period, Token::Symbol},
             Node::createTypeAccess(
                 {Node::createTypeSymbol(Field::createString8("x")),
                  Node::createTypeSymbol(Field::createString8("y"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_1) {
  testHelper(Parser::parseTypeAccess,
             "x.y.z",
             {Token::Symbol,
              Token::Period,
              Token::Symbol,
              Token::Period,
              Token::Symbol},
             Node::createTypeAccess(
                 {Node::createTypeSymbol(Field::createString8("x")),
                  Node::createTypeAccess(
                      {Node::createTypeSymbol(Field::createString8("y")),
                       Node::createTypeSymbol(Field::createString8("z"))})}),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_2) {
  testHelper(Parser::parseTypeAccessUnary,
             ".x.y",
             {Token::Period, Token::Symbol, Token::Period, Token::Symbol},
             Node::createTypeAccessUnary(Node::createTypeAccess(
                 {Node::createTypeSymbol(Field::createString8("x")),
                  Node::createTypeSymbol(Field::createString8("y"))})),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_3) {
  testHelper(Parser::parseTypeAccessUnary,
             ".x.y.z",
             {Token::Period,
              Token::Symbol,
              Token::Period,
              Token::Symbol,
              Token::Period,
              Token::Symbol},
             Node::createTypeAccessUnary(Node::createTypeAccess(
                 {Node::createTypeSymbol(Field::createString8("x")),
                  Node::createTypeAccess(
                      {Node::createTypeSymbol(Field::createString8("y")),
                       Node::createTypeSymbol(Field::createString8("z"))})})),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_4) {
  testHelper(Parser::parseTypeAccess, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_5) {
  testHelper(Parser::parseTypeAccess,
             "x.",
             {Token::Symbol, Token::Period},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_0) {
  testHelper(Parser::parseTypeFunction,
             "x <- ()",
             {Token::Symbol, Token::LArrow, Token::LParen, Token::RParen},
             Node::createTypeFunction(
                 Node::createTypeSymbol(Field::createString8("x")), {}),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_1) {
  testHelper(Parser::parseTypeFunction,
             "x <- (y)",
             {Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::Symbol,
              Token::RParen},
             Node::createTypeFunction(
                 Node::createTypeSymbol(Field::createString8("x")),
                 {Node::createTypeSymbol(Field::createString8("y"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_2) {
  testHelper(Parser::parseTypeFunction,
             "x <- (y, z)",
             {Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::Symbol,
              Token::RParen},
             Node::createTypeFunction(
                 Node::createTypeSymbol(Field::createString8("x")),
                 {Node::createTypeSymbol(Field::createString8("y")),
                  Node::createTypeSymbol(Field::createString8("z"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_3) {
  testHelper(Parser::parseTypeFunction,
             "x <- (y, z <- (a, b))",
             {Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::Symbol,
              Token::RParen,
              Token::RParen},
             Node::createTypeFunction(
                 Node::createTypeSymbol(Field::createString8("x")),
                 {Node::createTypeSymbol(Field::createString8("y")),
                  Node::createTypeFunction(
                      Node::createTypeSymbol(Field::createString8("z")),
                      {Node::createTypeSymbol(Field::createString8("a")),
                       Node::createTypeSymbol(Field::createString8("b"))})}),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_4) {
  testHelper(Parser::parseTypeFunction,
             "x <- (",
             {Token::Symbol, Token::LArrow, Token::LParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_5) {
  testHelper(Parser::parseTypeFunction,
             "x <- )",
             {Token::Symbol, Token::LArrow, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_6) {
  testHelper(Parser::parseTypeFunction,
             "x <- (,)",
             {Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::Comma,
              Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_7) {
  testHelper(Parser::parseTypeFunction,
             "x <- (x,)",
             {Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_0) {
  testHelper(
      Parser::parseTypeGroup,
      "(x)",
      {Token::LParen, Token::Symbol, Token::RParen},
      Node::createTypeGroup(Node::createTypeSymbol(Field::createString8("x"))),
      true);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_1) {
  testHelper(Parser::parseTypeGroup,
             "((x))",
             {Token::LParen,
              Token::LParen,
              Token::Symbol,
              Token::RParen,
              Token::RParen},
             Node::createTypeGroup(Node::createTypeGroup(
                 Node::createTypeSymbol(Field::createString8("x")))),
             true);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_2) {
  testHelper(Parser::parseTypeGroup,
             "((x)",
             {Token::LParen, Token::LParen, Token::Symbol, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_3) {
  testHelper(Parser::parseTypeGroup,
             "(x",
             {Token::LParen, Token::Symbol},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_4) {
  testHelper(Parser::parseTypeGroup,
             "x)",
             {Token::Symbol, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_5) {
  testHelper(Parser::parseTypeGroup,
             "()",
             {Token::LParen, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_6) {
  testHelper(Parser::parseTypeGroup, "x", {Token::Symbol}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_8) {
  testHelper(Parser::parseTypeFunction,
             "(x <- ()) <- ()",
             {Token::LParen,
              Token::Symbol,
              Token::LArrow,
              Token::LParen,
              Token::RParen,
              Token::RParen,
              Token::LArrow,
              Token::LParen,
              Token::RParen},
             Node::createTypeFunction(
                 Node::createTypeGroup(Node::createTypeFunction(
                     Node::createTypeSymbol(Field::createString8("x")), {})),
                 {}),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprSymbol_0) {
  testHelper(Parser::parseExprSymbol,
             "x",
             {Token::Symbol},
             Node::createExprSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprSymbol_1) {
  testHelper(Parser::parseExprSymbol, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralInt_0) {
  testHelper(Parser::parseExprLiteralUInt,
             "5",
             {Token::Int},
             Node::createExprLiteralUInt(Node::createTypeAtomicUInt64(), 5),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralInt_1) {
  testHelper(
      Parser::parseExprLiteralUInt, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralReal_0) {
  testHelper(Parser::parseExprLiteralReal,
             "3.14",
             {Token::Real},
             Node::createExprLiteralReal(Node::createTypeAtomicReal(), 3.14),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralReal_1) {
  testHelper(
      Parser::parseExprLiteralReal, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_0) {
  testHelper(Parser::parseExprAccessUnary,
             ".x",
             {Token::Period, Token::Symbol},
             Node::createExprAccessUnary(
                 Node::createExprSymbol(Field::createString8("x"))),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_1) {
  testHelper(Parser::parseExprAccessUnary,
             "..x",
             {Token::Period, Token::Period, Token::Symbol},
             Node::createExprAccessUnary(Node::createExprAccessUnary(
                 Node::createExprSymbol(Field::createString8("x")))),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_2) {
  testHelper(Parser::parseExprAccessUnary,
             "x",
             {Token::Symbol},
             Node::createExprSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_3) {
  testHelper(
      Parser::parseExprAccessUnary, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_0) {
  testHelper(Parser::parseExprAccess,
             "x.y",
             {Token::Symbol, Token::Period, Token::Symbol},
             Node::createExprAccess(
                 {Node::createExprSymbol(Field::createString8("x")),
                  Node::createExprSymbol(Field::createString8("y"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_1) {
  testHelper(Parser::parseExprAccess,
             "x.y.z",
             {Token::Symbol,
              Token::Period,
              Token::Symbol,
              Token::Period,
              Token::Symbol},
             Node::createExprAccess(
                 {Node::createExprSymbol(Field::createString8("x")),
                  Node::createExprAccess(
                      {Node::createExprSymbol(Field::createString8("y")),
                       Node::createExprSymbol(Field::createString8("z"))})}),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_2) {
  testHelper(Parser::parseExprAccessUnary,
             ".x.y",
             {Token::Period, Token::Symbol, Token::Period, Token::Symbol},
             Node::createExprAccessUnary(Node::createExprAccess(
                 {Node::createExprSymbol(Field::createString8("x")),
                  Node::createExprSymbol(Field::createString8("y"))})),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_3) {
  testHelper(Parser::parseExprAccessUnary,
             ".x.y.z",
             {Token::Period,
              Token::Symbol,
              Token::Period,
              Token::Symbol,
              Token::Period,
              Token::Symbol},
             Node::createExprAccessUnary(Node::createExprAccess(
                 {Node::createExprSymbol(Field::createString8("x")),
                  Node::createExprAccess(
                      {Node::createExprSymbol(Field::createString8("y")),
                       Node::createExprSymbol(Field::createString8("z"))})})),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_4) {
  testHelper(Parser::parseExprAccess, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_5) {
  testHelper(Parser::parseExprAccess,
             "x.",
             {Token::Symbol, Token::Period},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprAccess_6) {
  testHelper(Parser::parseExprAccess,
             "x",
             {Token::Symbol},
             Node::createExprSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprCall_0) {
  testHelper(Parser::parseExprCall,
             "x()",
             {Token::Symbol, Token::LParen, Token::RParen},
             Node::createExprCall(
                 Node::createExprSymbol(Field::createString8("x")), {}),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprCall_1) {
  testHelper(
      Parser::parseExprCall,
      "x(y)",
      {Token::Symbol, Token::LParen, Token::Symbol, Token::RParen},
      Node::createExprCall(Node::createExprSymbol(Field::createString8("x")),
                           {Node::createExprSymbol(Field::createString8("y"))}),
      true);
}

TEST(Integration_Parsing_Parser, ParseExprCall_2) {
  testHelper(
      Parser::parseExprCall,
      "x(y, z)",
      {Token::Symbol,
       Token::LParen,
       Token::Symbol,
       Token::Comma,
       Token::Symbol,
       Token::RParen},
      Node::createExprCall(Node::createExprSymbol(Field::createString8("x")),
                           {Node::createExprSymbol(Field::createString8("y")),
                            Node::createExprSymbol(Field::createString8("z"))}),
      true);
}

TEST(Integration_Parsing_Parser, ParseExprCall_3) {
  testHelper(Parser::parseExprCall,
             "x(y, z(a, b))",
             {Token::Symbol,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::Symbol,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::Symbol,
              Token::RParen,
              Token::RParen},
             Node::createExprCall(
                 Node::createExprSymbol(Field::createString8("x")),
                 {Node::createExprSymbol(Field::createString8("y")),
                  Node::createExprCall(
                      Node::createExprSymbol(Field::createString8("z")),
                      {Node::createExprSymbol(Field::createString8("a")),
                       Node::createExprSymbol(Field::createString8("b"))})}),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprCall_4) {
  testHelper(Parser::parseExprCall,
             "x(",
             {Token::Symbol, Token::LParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprCall_5) {
  testHelper(Parser::parseExprCall,
             "x)",
             {Token::Symbol, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprCall_6) {
  testHelper(Parser::parseExprCall,
             "x(,)",
             {Token::Symbol, Token::LParen, Token::Comma, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprCall_7) {
  testHelper(Parser::parseExprCall,
             "x(x,)",
             {Token::Symbol,
              Token::LParen,
              Token::Symbol,
              Token::Comma,
              Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprCall_8) {
  testHelper(Parser::parseExprCall,
             "x",
             {Token::Symbol},
             Node::createExprSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprUnaryRight_0) {
  testHelper(
      Parser::parseExpr,
      "++x",
      {Token::Inc, Token::Symbol},
      Node::createExprIncPre(Node::createExprSymbol(Field::createString8("x"))),
      true);
}

TEST(Integration_Parsing_Parser, ParseExprUnaryLeft_0) {
  testHelper(Parser::parseExpr,
             "x++",
             {Token::Symbol, Token::Inc},
             Node::createExprIncPost(
                 Node::createExprSymbol(Field::createString8("x"))),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprBinary_0) {
  testHelper(
      Parser::parseExpr,
      "x=y",
      {Token::Symbol, Token::Assign, Token::Symbol},
      Node::createExprAssign(Node::createExprSymbol(Field::createString8("x")),
                             Node::createExprSymbol(Field::createString8("y"))),
      true);
}

TEST(Integration_Parsing_Parser, ParseExprSymbol_2) {
  testHelper(Parser::parseExpr,
             "x",
             {Token::Symbol},
             Node::createExprSymbol(Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_0) {
  testHelper(
      Parser::parseExprGroup,
      "(x)",
      {Token::LParen, Token::Symbol, Token::RParen},
      Node::createExprGroup(Node::createExprSymbol(Field::createString8("x"))),
      true);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_1) {
  testHelper(Parser::parseExprGroup,
             "((x))",
             {Token::LParen,
              Token::LParen,
              Token::Symbol,
              Token::RParen,
              Token::RParen},
             Node::createExprGroup(Node::createExprGroup(
                 Node::createExprSymbol(Field::createString8("x")))),
             true);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_2) {
  testHelper(Parser::parseExprGroup,
             "((x)",
             {Token::LParen, Token::LParen, Token::Symbol, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_3) {
  testHelper(Parser::parseExprGroup,
             "(x",
             {Token::LParen, Token::Symbol},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_4) {
  testHelper(Parser::parseExprGroup,
             "x)",
             {Token::Symbol, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_5) {
  testHelper(Parser::parseExprGroup,
             "()",
             {Token::LParen, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_6) {
  testHelper(Parser::parseExprGroup, "x", {Token::Symbol}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseStmtEmpty_0) {
  testHelper(Parser::parseStmtEmpty,
             ";",
             {Token::Semicolon},
             Node::createStmtEmpty(),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtEmpty_1) {
  testHelper(Parser::parseStmtEmpty,
             "x;",
             {Token::Symbol, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtExpr_0) {
  testHelper(
      Parser::parseStmtExpr,
      "x;",
      {Token::Symbol, Token::Semicolon},
      Node::createStmtExpr(Node::createExprSymbol(Field::createString8("x"))),
      true);
}

TEST(Integration_Parsing_Parser, ParseStmtExpr_1) {
  testHelper(Parser::parseStmtExpr, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_0) {
  testHelper(Parser::parseDeclVariable,
             "int32 x;",
             {Token::KWInt32, Token::Symbol, Token::Semicolon},
             Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                      Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_1) {
  testHelper(Parser::parseDeclVariable,
             "my_type x;",
             {Token::Symbol, Token::Symbol, Token::Semicolon},
             Node::createDeclVariable(
                 Node::createTypeSymbol(Field::createString8("my_type")),
                 Field::createString8("x")),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_2) {
  testHelper(Parser::parseDeclVariable,
             "int32 x = y;",
             {Token::KWInt32,
              Token::Symbol,
              Token::Assign,
              Token::Symbol,
              Token::Semicolon},
             Node::createDeclVariable(
                 Node::createTypeAtomicInt32(),
                 Field::createString8("x"),
                 Node::createExprSymbol(Field::createString8("y"))),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_3) {
  testHelper(Parser::parseDeclVariable,
             "int32 x = y",
             {Token::KWInt32, Token::Symbol, Token::Assign, Token::Symbol},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_4) {
  testHelper(Parser::parseDeclVariable,
             "int32 x = ;",
             {Token::KWInt32, Token::Symbol, Token::Assign, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_5) {
  testHelper(Parser::parseDeclVariable,
             "int32 x=",
             {Token::KWInt32, Token::Symbol, Token::Assign},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclVariable_6) {
  testHelper(Parser::parseDeclVariable,
             "x = y;",
             {Token::Symbol, Token::Assign, Token::Symbol, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_0) {
  testHelper(Parser::parseDeclFunction,
             "int32 f();",
             {Token::KWInt32,
              Token::Symbol,
              Token::LParen,
              Token::RParen,
              Token::Semicolon},
             Node::createDeclFunction(
                 Node::createTypeAtomicInt32(), Field::createString8("f"), {}),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_1) {
  testHelper(Parser::parseDeclFunction,
             "int32 f(int32 x);",
             {Token::KWInt32,
              Token::Symbol,
              Token::LParen,
              Token::KWInt32,
              Token::Symbol,
              Token::RParen,
              Token::Semicolon},
             Node::createDeclFunction(
                 Node::createTypeAtomicInt32(),
                 Field::createString8("f"),
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_2) {
  testHelper(Parser::parseDeclFunction,
             "int32 f(int32 x, int32 y);",
             {Token::KWInt32,
              Token::Symbol,
              Token::LParen,
              Token::KWInt32,
              Token::Symbol,
              Token::Comma,
              Token::KWInt32,
              Token::Symbol,
              Token::RParen,
              Token::Semicolon},
             Node::createDeclFunction(
                 Node::createTypeAtomicInt32(),
                 Field::createString8("f"),
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x")),
                  Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("y"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_3) {
  testHelper(
      Parser::parseDeclFunction,
      "int32 f() = x;",
      {Token::KWInt32,
       Token::Symbol,
       Token::LParen,
       Token::RParen,
       Token::Assign,
       Token::Symbol,
       Token::Semicolon},
      Node::createDeclFunction(Node::createTypeAtomicInt32(),
                               Field::createString8("f"),
                               {},
                               Node::createStmtExpr(Node::createExprSymbol(
                                   Field::createString8("x")))),
      true);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_0) {
  testHelper(Parser::parseStmtBlock,
             "{}",
             {Token::LBrace, Token::RBrace},
             Node::createStmtBlock(),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_1) {
  testHelper(Parser::parseStmtBlock,
             "{;}",
             {Token::LBrace, Token::Semicolon, Token::RBrace},
             Node::createStmtBlock({Node::createStmtEmpty()}),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_2) {
  testHelper(
      Parser::parseStmtBlock,
      "{;;}",
      {Token::LBrace, Token::Semicolon, Token::Semicolon, Token::RBrace},
      Node::createStmtBlock({Node::createStmtEmpty(), Node::createStmtEmpty()}),
      true);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_3) {
  testHelper(Parser::parseStmtBlock,
             "{x;}",
             {Token::LBrace, Token::Symbol, Token::Semicolon, Token::RBrace},
             Node::createStmtBlock({Node::createStmtExpr(
                 Node::createExprSymbol(Field::createString8("x")))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_4) {
  testHelper(Parser::parseStmtBlock,
             "{x;y;}",
             {Token::LBrace,
              Token::Symbol,
              Token::Semicolon,
              Token::Symbol,
              Token::Semicolon,
              Token::RBrace},
             Node::createStmtBlock({Node::createStmtExpr(Node::createExprSymbol(
                                        Field::createString8("x"))),
                                    Node::createStmtExpr(Node::createExprSymbol(
                                        Field::createString8("y")))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_5) {
  testHelper(Parser::parseStmtBlock,
             "{x;y;",
             {Token::LBrace,
              Token::Symbol,
              Token::Semicolon,
              Token::Symbol,
              Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtBlock_6) {
  testHelper(Parser::parseStmtBlock,
             "x;y;}",
             {Token::Symbol,
              Token::Semicolon,
              Token::Symbol,
              Token::Semicolon,
              Token::RBrace},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_4) {
  testHelper(Parser::parseDeclFunction,
             "int32 f() {}",
             {Token::KWInt32,
              Token::Symbol,
              Token::LParen,
              Token::RParen,
              Token::LBrace,
              Token::RBrace},
             Node::createDeclFunction(Node::createTypeAtomicInt32(),
                                      Field::createString8("f"),
                                      {},
                                      Node::createStmtBlock()),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_5) {
  testHelper(Parser::parseDeclFunction,
             "int32 f()",
             {Token::KWInt32, Token::Symbol, Token::LParen, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_6) {
  testHelper(Parser::parseDeclFunction,
             "int32 f(;",
             {Token::KWInt32, Token::Symbol, Token::LParen, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclFunction_7) {
  testHelper(Parser::parseDeclFunction,
             "f();",
             {Token::Symbol, Token::LParen, Token::RParen, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_0) {
  testHelper(Parser::parseDeclClass,
             "class a;",
             {Token::KWClass, Token::Symbol, Token::Semicolon},
             Node::createDeclClass(Field::createString8("a")),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_1) {
  testHelper(
      Parser::parseDeclClass,
      "class a inherits b;",
      {Token::KWClass,
       Token::Symbol,
       Token::KWInherits,
       Token::Symbol,
       Token::Semicolon},
      Node::createDeclClass(Field::createString8("a"),
                            {Node::createTypeSymbol(Field::createString8("b"))},
                            {}),
      true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_2) {
  testHelper(
      Parser::parseDeclClass,
      "class a inherits b, c;",
      {Token::KWClass,
       Token::Symbol,
       Token::KWInherits,
       Token::Symbol,
       Token::Comma,
       Token::Symbol,
       Token::Semicolon},
      Node::createDeclClass(Field::createString8("a"),
                            {Node::createTypeSymbol(Field::createString8("b")),
                             Node::createTypeSymbol(Field::createString8("c"))},
                            {}),
      true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_3) {
  testHelper(Parser::parseDeclClass,
             "class a {}",
             {Token::KWClass, Token::Symbol, Token::LBrace, Token::RBrace},
             Node::createDeclClass(Field::createString8("a")),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_4) {
  testHelper(
      Parser::parseDeclClass,
      "class a inherits b {}",
      {Token::KWClass,
       Token::Symbol,
       Token::KWInherits,
       Token::Symbol,
       Token::LBrace,
       Token::RBrace},
      Node::createDeclClass(Field::createString8("a"),
                            {Node::createTypeSymbol(Field::createString8("b"))},
                            {}),
      true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_5) {
  testHelper(
      Parser::parseDeclClass,
      "class a inherits b, c {}",
      {Token::KWClass,
       Token::Symbol,
       Token::KWInherits,
       Token::Symbol,
       Token::Comma,
       Token::Symbol,
       Token::LBrace,
       Token::RBrace},
      Node::createDeclClass(Field::createString8("a"),
                            {Node::createTypeSymbol(Field::createString8("b")),
                             Node::createTypeSymbol(Field::createString8("c"))},
                            {}),
      true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_6) {
  testHelper(Parser::parseDeclClass,
             "class a { int32 x; }",
             {Token::KWClass,
              Token::Symbol,
              Token::LBrace,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::RBrace},
             Node::createDeclClass(
                 Field::createString8("a"),
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclClass_7) {
  testHelper(Parser::parseDeclClass,
             "class a { int32 x; int32 y; }",
             {Token::KWClass,
              Token::Symbol,
              Token::LBrace,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::RBrace},
             Node::createDeclClass(
                 Field::createString8("a"),
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x")),
                  Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("y"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclNamespace_0) {
  testHelper(Parser::parseDeclNamespace,
             "namespace a {}",
             {Token::KWNamespace, Token::Symbol, Token::LBrace, Token::RBrace},
             Node::createDeclNamespace(Field::createString8("a")),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclNamespace_1) {
  testHelper(Parser::parseDeclNamespace,
             "namespace a { int32 x; }",
             {Token::KWNamespace,
              Token::Symbol,
              Token::LBrace,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::RBrace},
             Node::createDeclNamespace(
                 Field::createString8("a"),
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseDeclNamespace_2) {
  testHelper(Parser::parseDeclNamespace,
             "namespace a { int32 x; int32 y; }",
             {Token::KWNamespace,
              Token::Symbol,
              Token::LBrace,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::RBrace},
             Node::createDeclNamespace(
                 Field::createString8("a"),
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x")),
                  Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("y"))}),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtDecl_0) {
  testHelper(Parser::parseStmtDecl,
             "int32 x;",
             {Token::KWInt32, Token::Symbol, Token::Semicolon},
             Node::createStmtDecl(Node::createDeclVariable(
                 Node::createTypeAtomicInt32(), Field::createString8("x"))),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtDecl_1) {
  testHelper(Parser::parseStmtDecl, ";", {Token::Semicolon}, nullptr, false);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_0) {
  testHelper(Parser::parseStmtFor,
             "for (;;);",
             {Token::KWFor,
              Token::LParen,
              Token::Semicolon,
              Token::Semicolon,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtFor({}, nullptr, {}, Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_1) {
  testHelper(Parser::parseStmtFor,
             "for (int32 x;;);",
             {Token::KWFor,
              Token::LParen,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::Semicolon,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtFor(
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x"))},
                 nullptr,
                 {},
                 Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_2) {
  testHelper(Parser::parseStmtFor,
             "for (int32 x, int32 y;;);",
             {Token::KWFor,
              Token::LParen,
              Token::KWInt32,
              Token::Symbol,
              Token::Comma,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::Semicolon,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtFor(
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x")),
                  Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("y"))},
                 nullptr,
                 {},
                 Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_3) {
  testHelper(
      Parser::parseStmtFor,
      "for (; x;);",
      {Token::KWFor,
       Token::LParen,
       Token::Semicolon,
       Token::Symbol,
       Token::Semicolon,
       Token::RParen,
       Token::Semicolon},
      Node::createStmtFor({},
                          Node::createExprSymbol(Field::createString8("x")),
                          {},
                          Node::createStmtEmpty()),
      true);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_4) {
  testHelper(
      Parser::parseStmtFor,
      "for (;; x);",
      {Token::KWFor,
       Token::LParen,
       Token::Semicolon,
       Token::Semicolon,
       Token::Symbol,
       Token::RParen,
       Token::Semicolon},
      Node::createStmtFor({},
                          nullptr,
                          {Node::createExprSymbol(Field::createString8("x"))},
                          Node::createStmtEmpty()),
      true);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_5) {
  testHelper(
      Parser::parseStmtFor,
      "for (;; x, y);",
      {Token::KWFor,
       Token::LParen,
       Token::Semicolon,
       Token::Semicolon,
       Token::Symbol,
       Token::Comma,
       Token::Symbol,
       Token::RParen,
       Token::Semicolon},
      Node::createStmtFor({},
                          nullptr,
                          {Node::createExprSymbol(Field::createString8("x")),
                           Node::createExprSymbol(Field::createString8("y"))},
                          Node::createStmtEmpty()),
      true);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_6) {
  testHelper(Parser::parseStmtFor,
             "for (;;)",
             {Token::KWFor,
              Token::LParen,
              Token::Semicolon,
              Token::Semicolon,
              Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_7) {
  testHelper(Parser::parseStmtFor,
             "for (;;",
             {Token::KWFor, Token::LParen, Token::Semicolon, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_8) {
  testHelper(Parser::parseStmtFor,
             "for (;)",
             {Token::KWFor, Token::LParen, Token::Semicolon, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_9) {
  testHelper(Parser::parseStmtFor,
             "for ()",
             {Token::KWFor, Token::LParen, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtFor_10) {
  testHelper(Parser::parseStmtFor,
             "for ;;)",
             {Token::KWFor, Token::Semicolon, Token::Semicolon, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_0) {
  testHelper(Parser::parseStmtForEach,
             "foreach (;);",
             {Token::KWForEach,
              Token::LParen,
              Token::Semicolon,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtForEach({}, {}, Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_1) {
  testHelper(Parser::parseStmtForEach,
             "foreach (int32 x;);",
             {Token::KWForEach,
              Token::LParen,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtForEach(
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x"))},
                 {},
                 Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_2) {
  testHelper(Parser::parseStmtForEach,
             "foreach (int32 x, int32 y;);",
             {Token::KWForEach,
              Token::LParen,
              Token::KWInt32,
              Token::Symbol,
              Token::Comma,
              Token::KWInt32,
              Token::Symbol,
              Token::Semicolon,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtForEach(
                 {Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("x")),
                  Node::createDeclVariable(Node::createTypeAtomicInt32(),
                                           Field::createString8("y"))},
                 {},
                 Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_3) {
  testHelper(Parser::parseStmtForEach,
             "foreach (; x);",
             {Token::KWForEach,
              Token::LParen,
              Token::Semicolon,
              Token::Symbol,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtForEach(
                 {},
                 {Node::createExprSymbol(Field::createString8("x"))},
                 Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_4) {
  testHelper(Parser::parseStmtForEach,
             "foreach (; x, y);",
             {Token::KWForEach,
              Token::LParen,
              Token::Semicolon,
              Token::Symbol,
              Token::Comma,
              Token::Symbol,
              Token::RParen,
              Token::Semicolon},
             Node::createStmtForEach(
                 {},
                 {Node::createExprSymbol(Field::createString8("x")),
                  Node::createExprSymbol(Field::createString8("y"))},
                 Node::createStmtEmpty()),
             true);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_5) {
  testHelper(Parser::parseStmtForEach,
             "foreach (;)",
             {Token::KWForEach, Token::LParen, Token::Semicolon, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_6) {
  testHelper(Parser::parseStmtForEach,
             "foreach ();",
             {Token::KWForEach, Token::LParen, Token::RParen, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_7) {
  testHelper(Parser::parseStmtForEach,
             "foreach (;",
             {Token::KWForEach, Token::LParen, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseStmtForEach_8) {
  testHelper(
      Parser::parseStmtForEach,
      "foreach ;);",
      {Token::KWForEach, Token::Semicolon, Token::RParen, Token::Semicolon},
      nullptr,
      false);
}

TEST(Integration_Parsing_Parser, ParseImport_0) {
  testHelper(Parser::parseImport,
             "import(\"a\");",
             {Token::KWImport,
              Token::LParen,
              Token::String,
              Token::RParen,
              Token::Semicolon},
             Node::createImport(Field::createString8("a")),
             true);
}

TEST(Integration_Parsing_Parser, ParseImport_1) {
  testHelper(Parser::parseImport,
             "import(\"a\")",
             {Token::KWImport, Token::LParen, Token::String, Token::RParen},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseImport_2) {
  testHelper(Parser::parseImport,
             "import(\"a\";",
             {Token::KWImport, Token::LParen, Token::String, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseImport_3) {
  testHelper(Parser::parseImport,
             "import\"a\");",
             {Token::KWImport, Token::String, Token::RParen, Token::Semicolon},
             nullptr,
             false);
}

TEST(Integration_Parsing_Parser, ParseImport_4) {
  testHelper(Parser::parseImport,
             "import;",
             {Token::KWImport, Token::Semicolon},
             nullptr,
             false);
}
