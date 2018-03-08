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

  messageContext.print(std::cout);
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

  messageContext.print(std::cout);

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
      TokenID::Symbol
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

  verbose = true;

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

  verbose = false;
}
