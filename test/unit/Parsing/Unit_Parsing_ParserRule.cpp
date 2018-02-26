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
#include <whiskey/Parsing/ParserRule.hpp>

using namespace whiskey;

class MyRule : public ParserRule {
protected:
  ParserResult onParse(const ParserGrammar &grammar, ParserContext &ctx, MessageContext &msgs) const {
    msgs.emit(ctx.get(), Message::Severity::Error);
    return Node(NodeType::StmtEmpty, ctx.eat());
  }

public:
  MyRule() : ParserRule("asdf") {}
};

TEST(Unit_Parsing_ParserRule, Simple) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<MyRule>());

  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;

  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::Symbol);
  ASSERT_EQ(msgs.getMessageCount(), 1);
  ASSERT_EQ(msgs.getErrorCount(), 1);
}
