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
#include <whiskey/Parsing/ParserRuleConcat.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserRuleConcat, Good_Empty_Complete) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
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

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::LT);
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Symbol);
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::GT);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleConcat, Good_Terms_Complete) {
	ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm2 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf4",
			"asdf4",
			TokenID::GT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm1,
				ruleTerm2
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
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

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleConcat, Bad_Terms_Incomplete) {
	ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm2 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf4",
			"asdf4",
			TokenID::GT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm1,
				ruleTerm2
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleConcat, Good_Terms_Incorrect) {
	ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm2 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf4",
			"asdf4",
			TokenID::GT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm1,
				ruleTerm2
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Int),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleConcat, Good_Empties_Complete) {
	ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleEmpty>(
			"asdf2",
			[](MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm0,
				ruleTerm0,
				ruleTerm0
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
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

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::LT);
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Symbol);
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::GT);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleConcat, Good_TermsWithEmpties_Complete) {
	ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm2 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf4",
			"asdf4",
			TokenID::GT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm3 = grammar.addRule(
		std::make_unique<ParserRuleEmpty>(
			"asdf5",	
			[](MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm3,
				ruleTerm0,
				ruleTerm3,
				ruleTerm1,
				ruleTerm3,
				ruleTerm2,
				ruleTerm3
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
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

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleConcat, Bad_TermsWithEmpties_Incomplete) {
  ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm2 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf4",
			"asdf4",
			TokenID::GT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm3 = grammar.addRule(
		std::make_unique<ParserRuleEmpty>(
			"asdf5",
			[](MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm3,
				ruleTerm0,
				ruleTerm3,
				ruleTerm1,
				ruleTerm3,
				ruleTerm2,
				ruleTerm3
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleConcat, Good_TermsWithEmpties_Incorrect) {
  ParserGrammar grammar;

	ParserRuleID ruleTerm0 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf2",
			"asdf2",
			TokenID::LT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm1 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm2 = grammar.addRule(
		std::make_unique<ParserRuleTerm>(
			"asdf4",
			"asdf4",
			TokenID::GT,
			[](Token, MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID ruleTerm3 = grammar.addRule(
		std::make_unique<ParserRuleEmpty>(
			"asdf5",
			[](MessageContext &) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	ParserRuleID rule = grammar.addRule(
		std::make_unique<ParserRuleConcat>(
			"asdf",
			"asdf",
			std::initializer_list<ParserRuleID>({
				ruleTerm3,
				ruleTerm0,
				ruleTerm3,
				ruleTerm1,
				ruleTerm3,
				ruleTerm2,
				ruleTerm3
			}),
			[](const std::vector<Node> &elements, MessageContext &ctx) {
		    return Node(NodeType::StmtEmpty);
		  }
		)
	);

	std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Int),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}
