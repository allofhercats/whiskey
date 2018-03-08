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
#include <whiskey/Parsing/ParserRuleTerm.hpp>
#include <whiskey/Parsing/ParserRuleAny.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserRuleAny, Bad_Empty) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleAny>(
			"asdf",
			"asdf"
		)
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleAny, Good_One) {
	ParserGrammar grammar;

	ParserRuleID ruleTerm = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleAny>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm
			})
		)
	);

  std::vector<Token> toks = {
    Token(TokenID::LT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::LT);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleAny, Bad_One) {
  ParserGrammar grammar;

	ParserRuleID ruleTerm = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleAny>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm
			})
		)
	);

	std::vector<Token> toks = {
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleAny, Good_Two_First) {
  ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::GT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleAny>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm1
			})
		)
	);

	std::vector<Token> toks = {
    Token(TokenID::LT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::LT);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleAny, Good_Two_Second) {
  ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::GT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleAny>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm1
			})
		)
	);

	std::vector<Token> toks = {
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::GT);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleAny, Bad_Two) {
  ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::GT,
			[](Token token, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty, token);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleAny>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm1
			})
		)
	);

	std::vector<Token> toks = {
    Token(TokenID::Int)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}
