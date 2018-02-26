#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Parsing/ParserGrammar.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserRuleEmpty.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserRuleEmpty, Good) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<ParserRuleEmpty>("asdf", []() {
    return Node(NodeType::StmtEmpty);
  }));

  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Symbol);
  ASSERT_FALSE(ctx.more());
}
