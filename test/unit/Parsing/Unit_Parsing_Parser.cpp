#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Core/Literals.hpp>
#include <whiskey/Core/Verbose.hpp>
#include <whiskey/Source/Source.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Lexing/LexerContext.hpp>
#include <whiskey/Lexing/Lexer.hpp>
#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldString.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserGrammar.hpp>
#include <whiskey/Parsing/Parser.hpp>

using namespace whiskey;

#pragma clang diagnostic ignored "-Wmissing-prototypes"

void testParser(const Parser &parser, ParserRuleID rule, std::string text, std::initializer_list<TokenID> tokenIDsExpected, Node astExpected, bool expectsSuccess) {
  std::stringstream textStream(text);
  Source source(textStream);
  std::vector<Token> tokensActual;
  MessageContext messageContext;
  LexerContext lexerContext(source, tokensActual);
  Lexer lexer;

  lexer.lex(lexerContext, messageContext);

  messageContext.print(std::cout, source);
  ASSERT_EQ(messageContext.getMessageCount(), 0);

  std::vector<Token>::const_iterator tokensActualIter = tokensActual.cbegin();
  std::initializer_list<TokenID>::const_iterator tokenIDsExpectedIter = tokenIDsExpected.begin();

  while (tokensActualIter != tokensActual.cend() && tokenIDsExpectedIter != tokenIDsExpected.end()) {
    ASSERT_EQ(tokensActualIter->getID(), *tokenIDsExpectedIter);
    tokensActualIter++;
    tokenIDsExpectedIter++;
  }

  ASSERT_EQ((tokensActualIter == tokensActual.cend()), (tokenIDsExpectedIter == tokenIDsExpected.end()));

  ParserContext parserContext(tokensActual);

  ParserResult result = parser.getGrammar().getRule(rule).parse(parser.getGrammar(), parserContext, messageContext);

  messageContext.print(std::cout, source);

  ASSERT_FALSE(parserContext.more());

  if (expectsSuccess) {
    ASSERT_TRUE(result.isGood());
    ASSERT_EQ(messageContext.getMessageCount(), 0);
    if (result.getNode() != astExpected) {
      std::cout << "Actual AST: ";
      result.getNode().print(std::cout);
      std::cout << "\nExpected AST: ";
      astExpected.print(std::cout);
      std::cout << "\n\n";
      FAIL();
    }
  } else {
    ASSERT_FALSE(result.isGood());
  }
}

TEST(Unit_Parsing_Parser, Good_TypeAtomicBool) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeAtomicBool);

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "bool",
    {
      TokenID::KWBool
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeSymbol_NoTemplateArgs) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeSymbol);
  ast.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "x",
    {
      TokenID::Symbol
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeSymbol_TemplateArgsEmpty) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeSymbol);
  ast.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "x<>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::GT
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeSymbol_TemplateArgsOne) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeSymbol);
  ast.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "x<y>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::Symbol,
      TokenID::GT
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeSymbol_TemplateArgsTwo) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeSymbol);
  ast.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "x<y, z>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::Symbol,
      TokenID::Comma,
      TokenID::Symbol,
      TokenID::GT
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeSymbol_TemplateArgsNested) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeSymbol);
  ast.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeAtomicBool));

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "x<y<bool>>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::Symbol,
      TokenID::LT,
      TokenID::KWBool,
      TokenID::BitShR
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeAccess) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeAccess);
  ast.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeAtomicInt8));
  ast.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeAtomicInt16));

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "int8.int16",
    {
      TokenID::KWInt8,
      TokenID::Period,
      TokenID::KWInt16
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeAccessUnary) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeAccessUnary);
  ast.setField(FieldTag::TypeAccessUnary_Arg, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));

  testParser(
    parser,
    parser.getGrammarRuleType(),
    ".int8",
    {
      TokenID::Period,
      TokenID::KWInt8
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeGroup) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeAtomicInt8);

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "(int8)",
    {
      TokenID::LParen,
      TokenID::KWInt8,
      TokenID::RParen
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_TypeFunction) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::TypeFunction);
  ast.setField(FieldTag::TypeFunction_Return, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::TypeFunction_Args, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleType(),
    "int8 <- ()",
    {
      TokenID::KWInt8,
      TokenID::LArrow,
      TokenID::LParen,
      TokenID::RParen
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprLiteralBool) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprLiteralBool);
  ast.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "true",
    {
      TokenID::KWTrue
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprLiteralUInt) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprLiteralUInt64);
  ast.setField(FieldTag::ExprLiteralUInt64_Value, std::make_unique<FieldUInt>(5));

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "5",
    {
      TokenID::Int
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprSymbol_NoTemplateArgs) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprSymbol);
  ast.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "x",
    {
      TokenID::Symbol
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprSymbol_TemplateArgsEmpty) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprSymbol);
  ast.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "x<>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::GT
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprSymbol_TemplateArgsOne) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprSymbol);
  ast.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "x<y>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::Symbol,
      TokenID::GT
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprSymbol_TemplateArgsTwo) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprSymbol);
  ast.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "x<y, z>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::Symbol,
      TokenID::Comma,
      TokenID::Symbol,
      TokenID::GT
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprSymbol_TemplateArgsNested) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprSymbol);
  ast.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::TypeSymbol));
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::ExprLiteralBool));
  ast.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().getField(FieldTag::TypeSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "x<y<true>>",
    {
      TokenID::Symbol,
      TokenID::LT,
      TokenID::Symbol,
      TokenID::LT,
      TokenID::KWTrue,
      TokenID::BitShR
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprAccess) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprAccess);
  ast.setField(FieldTag::ExprAccess_Args, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(Node(NodeType::ExprLiteralBool));
  ast.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().back().setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(0));
  ast.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(Node(NodeType::ExprLiteralBool));
  ast.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().back().setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "false.true",
    {
      TokenID::KWFalse,
      TokenID::Period,
      TokenID::KWTrue
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprAccessUnary) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprAccessUnary);
  ast.setField(FieldTag::ExprAccessUnary_Arg, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
  ast.getField(FieldTag::ExprAccessUnary_Arg).as<FieldNode>().getValue().setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(0));

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    ".false",
    {
      TokenID::Period,
      TokenID::KWFalse
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprGroup) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprLiteralBool);
  ast.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "(true)",
    {
      TokenID::LParen,
      TokenID::KWTrue,
      TokenID::RParen
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_ExprCall) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::ExprCall);
  ast.setField(FieldTag::ExprCall_Callee, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralBool)));
  ast.getField(FieldTag::ExprCall_Callee).as<FieldNode>().getValue().setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));
  ast.setField(FieldTag::ExprCall_Args, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleExpr(),
    "true()",
    {
      TokenID::KWTrue,
      TokenID::LParen,
      TokenID::RParen
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtEmpty) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtEmpty);

  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    ";",
    {
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtExpr) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtExpr);
  ast.setField(FieldTag::StmtExpr_Expr, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::StmtExpr_Expr).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "x;",
    {
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtReturn_Void) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtReturn);

  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "return;",
    {
      TokenID::KWReturn,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtReturn_NonVoid) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtReturn);
  ast.setField(FieldTag::StmtReturn_Arg, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::StmtReturn_Arg).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());

  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "return x;",
    {
      TokenID::KWReturn,
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtContinue_WithoutSymbol) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtContinue);

  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "continue;",
    {
      TokenID::KWContinue,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtContinue_WithSymbol) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtContinue);
  ast.setField(FieldTag::StmtContinue_Name, std::make_unique<FieldString>("x"));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "continue x;",
    {
      TokenID::KWContinue,
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtBreak_WithoutSymbol) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtBreak);

  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "break;",
    {
      TokenID::KWBreak,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtBreak_WithSymbol) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtBreak);
  ast.setField(FieldTag::StmtBreak_Name, std::make_unique<FieldString>("x"));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "break x;",
    {
      TokenID::KWBreak,
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtIf_WithoutElse) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtIf);
  ast.setField(FieldTag::StmtIf_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::StmtIf_Condition).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::StmtIf_Then, std::make_unique<FieldNode>(Node(NodeType::StmtReturn)));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "if (x) return;",
    {
      TokenID::KWIf,
      TokenID::LParen,
      TokenID::Symbol,
      TokenID::RParen,
      TokenID::KWReturn,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtIf_WithElse) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtIf);
  ast.setField(FieldTag::StmtIf_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::StmtIf_Condition).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::StmtIf_Then, std::make_unique<FieldNode>(Node(NodeType::StmtReturn)));
  ast.setField(FieldTag::StmtIf_Else, std::make_unique<FieldNode>(Node(NodeType::StmtContinue)));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "if (x) return; else continue;",
    {
      TokenID::KWIf,
      TokenID::LParen,
      TokenID::Symbol,
      TokenID::RParen,
      TokenID::KWReturn,
      TokenID::Semicolon,
      TokenID::KWElse,
      TokenID::KWContinue,
      TokenID::Semicolon,
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtWhile) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtWhile);
  ast.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::StmtWhile_Condition).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::StmtWhile_Body, std::make_unique<FieldNode>(Node(NodeType::StmtReturn)));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "while (x) return;",
    {
      TokenID::KWWhile,
      TokenID::LParen,
      TokenID::Symbol,
      TokenID::RParen,
      TokenID::KWReturn,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtBlock_Empty) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtBlock);
  ast.setField(FieldTag::StmtBlock_Stmts, std::make_unique<FieldNodeVector>());
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "{}",
    {
      TokenID::LBrace,
      TokenID::RBrace
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtBlock_One) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtBlock);
  ast.setField(FieldTag::StmtBlock_Stmts, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::StmtBlock_Stmts).as<FieldNodeVector>().getValue().push_back(Node(NodeType::StmtReturn));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "{return;}",
    {
      TokenID::LBrace,
      TokenID::KWReturn,
      TokenID::Semicolon,
      TokenID::RBrace
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_StmtBlock_Two) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::StmtBlock);
  ast.setField(FieldTag::StmtBlock_Stmts, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::StmtBlock_Stmts).as<FieldNodeVector>().getValue().push_back(Node(NodeType::StmtReturn));
  ast.getField(FieldTag::StmtBlock_Stmts).as<FieldNodeVector>().getValue().push_back(Node(NodeType::StmtContinue));
  
  testParser(
    parser,
    parser.getGrammarRuleStmt(),
    "{return;continue;}",
    {
      TokenID::LBrace,
      TokenID::KWReturn,
      TokenID::Semicolon,
      TokenID::KWContinue,
      TokenID::Semicolon,
      TokenID::RBrace
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_DeclVariable_NonTemplateNoInitial) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::DeclVariable);
  ast.setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  
  testParser(
    parser,
    parser.getGrammarRuleDecl(),
    "int8 x;",
    {
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_DeclVariable_TemplateNoInitial) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::DeclVariable);
  ast.setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::DeclVariable_TemplateDeclArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::DeclVariable));
  ast.getField(FieldTag::DeclVariable_TemplateDeclArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt16)));
  ast.getField(FieldTag::DeclVariable_TemplateDeclArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  
  testParser(
    parser,
    parser.getGrammarRuleDecl(),
    "int8 x<int16 y>;",
    {
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::LT,
      TokenID::KWInt16,
      TokenID::Symbol,
      TokenID::GT,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_DeclVariable_NonTemplateInitial) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::DeclVariable);
  ast.setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclVariable_Initial, std::make_unique<FieldNode>(Node(NodeType::ExprLiteralUInt64)));
  ast.getField(FieldTag::DeclVariable_Initial).as<FieldNode>().getValue().setField(FieldTag::ExprLiteralUInt64_Value, std::make_unique<FieldUInt>(5));
  
  testParser(
    parser,
    parser.getGrammarRuleDecl(),
    "int8 x = 5;",
    {
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::Assign,
      TokenID::Int,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_DeclFunction_NonTemplateNoArgsExpr) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::DeclFunction);
  ast.setField(FieldTag::DeclFunction_Return, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::DeclFunction_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclFunction_Args, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclFunction_Body, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::DeclFunction_Body).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  
  testParser(
    parser,
    parser.getGrammarRuleDecl(),
    "int8 f()=x;",
    {
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::LParen,
      TokenID::RParen,
      TokenID::Assign,
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_DeclFunction_TemplateNoArgsExpr) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::DeclFunction);
  ast.setField(FieldTag::DeclFunction_Return, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::DeclFunction_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  ast.getField(FieldTag::DeclFunction_TemplateDeclArgs).as<FieldNodeVector>().getValue().push_back(Node(NodeType::DeclVariable));
  ast.getField(FieldTag::DeclFunction_TemplateDeclArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.getField(FieldTag::DeclFunction_TemplateDeclArgs).as<FieldNodeVector>().getValue().back().setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclFunction_Args, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclFunction_Body, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  ast.getField(FieldTag::DeclFunction_Body).as<FieldNode>().getValue().setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
  
  testParser(
    parser,
    parser.getGrammarRuleDecl(),
    "int8 f<int8 x>()=y;",
    {
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::LT,
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::GT,
      TokenID::LParen,
      TokenID::RParen,
      TokenID::Assign,
      TokenID::Symbol,
      TokenID::Semicolon
    },
    ast,
    true
  );
}

TEST(Unit_Parsing_Parser, Good_DeclFunction_NonTemplateNoArgsBlock) {
  Parser parser;
  parser.initGrammar();

  Node ast(NodeType::DeclFunction);
  ast.setField(FieldTag::DeclFunction_Return, std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8)));
  ast.setField(FieldTag::DeclFunction_TemplateDeclArgs, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclFunction_Args, std::make_unique<FieldNodeVector>());
  ast.setField(FieldTag::DeclFunction_Body, std::make_unique<FieldNode>(Node(NodeType::StmtBlock)));
  ast.getField(FieldTag::DeclFunction_Body).as<FieldNode>().getValue().setField(FieldTag::StmtBlock_Stmts, std::make_unique<FieldNodeVector>());
  
  testParser(
    parser,
    parser.getGrammarRuleDecl(),
    "int8 f(){}",
    {
      TokenID::KWInt8,
      TokenID::Symbol,
      TokenID::LParen,
      TokenID::RParen,
      TokenID::LBrace,
      TokenID::RBrace
    },
    ast,
    true
  );
}
