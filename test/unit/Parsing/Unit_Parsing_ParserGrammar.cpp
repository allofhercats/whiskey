#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/Parsing/ParserGrammar.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Good_Empty) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Bad_Empty_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Bad_Empty_MissingLeft) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Good_One) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol, "x"),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 1);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Bad_One_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Bad_One_SepInsteadOfRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol),
    Token(TokenID::Comma)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Good_Two) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol, "x"),
    Token(TokenID::Comma),
    Token(TokenID::Symbol, "y"),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getToken().getText().c_str(), "x");
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getToken().getText().c_str(), "y");

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Two_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol),
    Token(TokenID::Comma),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Two_SepInsteadOfRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol),
    Token(TokenID::Comma),
    Token(TokenID::Symbol),
    Token(TokenID::Comma)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Two_MissingFirst) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Comma),
    Token(TokenID::Symbol),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Two_MissingSecond) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol),
    Token(TokenID::Comma),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBoundSeparated_Two_MissingBoth) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBoundSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Comma),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}














TEST(Unit_Parsing_ParserGrammar, ListSeparated_Good_Empty) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListSeparated_Good_One) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol, "x")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 1);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListSeparated_Good_Two) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListSeparated(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf4",
			"asdf4",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol, "x"),
    Token(TokenID::Comma),
    Token(TokenID::Symbol, "y")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getToken().getText().c_str(), "x");
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getToken().getText().c_str(), "y");

  ASSERT_FALSE(ctx.more());
}





















TEST(Unit_Parsing_ParserGrammar, List_Good_Empty) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addList(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, List_Good_One) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addList(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol, "x")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 1);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, List_Good_Two) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addList(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol, "x"),
    Token(TokenID::Symbol, "y")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getToken().getText().c_str(), "x");
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getToken().getText().c_str(), "y");

  ASSERT_FALSE(ctx.more());
}



















TEST(Unit_Parsing_ParserGrammar, ListBound_Good_Empty) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Bad_Empty_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Bad_Empty_MissingLeft) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Good_One) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol, "x"),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 1);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Bad_One_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Bad_One_SepInsteadOfRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Good_Two) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol, "x"),
    Token(TokenID::Symbol, "y"),
    Token(TokenID::RParen)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::TypeAccess);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[0].getToken().getText().c_str(), "x");
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue()[1].getToken().getText().c_str(), "y");

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Two_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, ListBound_Two_SepInsteadOfRight) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addListBound(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::TypeSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::LParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		grammar.addTerm(
			"asdf5",
			"asdf5",
			TokenID::RParen,
			[](Token token, MessageContext &ctx) {
				return Node();
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = Node(NodeType::TypeAccess);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LParen),
    Token(TokenID::Symbol),
    Token(TokenID::Symbol),
    Token(TokenID::Comma)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Good_Base) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Bad_Base) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Int)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Good_Inc) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Inc),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprIncPre);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPre_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPre_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Bad_MissingBase) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Inc)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Good_Dec) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Dec),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprDecPre);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Good_DecDec) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Dec),
    Token(TokenID::Dec),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprDecPre);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprDecPre);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprDecPre_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryRight_Good_DecInc) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryRight(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf2",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Dec),
    Token(TokenID::Inc),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprDecPre);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprIncPre);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprIncPre_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPre_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprIncPre_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryLeft_Good_Base) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryLeft(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPost, token);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPost, token);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryLeft_Good_Inc) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryLeft(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPost, token);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPost, token);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Inc)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprIncPost);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPost_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPost_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryLeft_Good_Dec) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryLeft(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPost, token);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPost, token);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Dec)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprDecPost);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPost_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPost_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryLeft_Good_DecDec) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryLeft(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPost, token);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPost, token);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Dec),
    Token(TokenID::Dec)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprDecPost);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPost_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPost_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprDecPost);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPost_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprDecPost_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprDecPost_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprDecPost_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, UnaryLeft_Good_DecInc) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addUnaryLeft(
		"asdf",
		"asdf",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf3",
				"asdf3",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn = Node(NodeType::ExprIncPost, token);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn = Node(NodeType::ExprDecPost, token);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Dec),
    Token(TokenID::Inc)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprIncPost);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPost_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPost_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprDecPost);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPost_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprDecPost_Arg).getFormat(), FieldFormat::Node);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprIncPost_Arg).as<FieldNode>().getValue().getField(FieldTag::ExprDecPost_Arg).as<FieldNode>().getValue().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, Binary_Good_Base) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addBinary(
		"asdf",
		"asdf2",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf4",
				"asdf4",
				TokenID::Add,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf5",
				"asdf5",
				TokenID::Sub,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Add) {
				Node rtn = Node(NodeType::ExprAdd, token);
				rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Sub) {
				Node rtn = Node(NodeType::ExprSub, token);
				rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
	ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprSymbol);
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, Binary_Good_Add) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addBinary(
		"asdf",
		"asdf2",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf4",
				"asdf4",
				TokenID::Add,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf5",
				"asdf5",
				TokenID::Sub,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Add) {
				Node rtn = Node(NodeType::ExprAdd, token);
				rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Sub) {
				Node rtn = Node(NodeType::ExprSub, token);
				rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Add),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
	ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprAdd);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, Binary_Good_Sub) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addBinary(
		"asdf",
		"asdf2",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf4",
				"asdf4",
				TokenID::Add,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf5",
				"asdf5",
				TokenID::Sub,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Add) {
				Node rtn = Node(NodeType::ExprAdd, token);
				rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Sub) {
				Node rtn = Node(NodeType::ExprSub, token);
				rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Sub),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
	ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprSub);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprSub_LHS).as<FieldNode>().getValue().getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprSub_RHS).as<FieldNode>().getValue().getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, Binary_Good_AddSub) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addBinary(
		"asdf",
		"asdf2",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf4",
				"asdf4",
				TokenID::Add,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf5",
				"asdf5",
				TokenID::Sub,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Add) {
				Node rtn = Node(NodeType::ExprAdd, token);
				rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Sub) {
				Node rtn = Node(NodeType::ExprSub, token);
				rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Add),
    Token(TokenID::Symbol),
    Token(TokenID::Sub),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
	ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::ExprAdd);
  ASSERT_EQ(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::ExprSub)
  );
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue()[1].getField(FieldTag::ExprSub_LHS).as<FieldNode>().getValue().getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue()[1].getField(FieldTag::ExprSub_RHS).as<FieldNode>().getValue().getType()),
  	static_cast<int>(NodeType::ExprSymbol)
  );
  
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, Binary_Bad_Sub_MissingRHS) {
	ParserGrammar grammar;

	ParserRuleID rule = grammar.addBinary(
		"asdf",
		"asdf2",
		grammar.addTerm(
			"asdf2",
			"asdf2",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		grammar.addTerm(
			"asdf3",
			"asdf3",
			TokenID::Symbol,
			[](Token token, MessageContext &ctx) {
				return Node(NodeType::ExprSymbol, token);
			}
		),
		{
			grammar.addTerm(
				"asdf4",
				"asdf4",
				TokenID::Add,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"asdf5",
				"asdf5",
				TokenID::Sub,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Add) {
				Node rtn = Node(NodeType::ExprAdd, token);
				rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Sub) {
				Node rtn = Node(NodeType::ExprSub, token);
				rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator token.");
			}
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::Symbol),
    Token(TokenID::Sub)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
	ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_GT(msgs.getMessageCount(), 0);
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Good_Empty) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::List);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::TypeAccess_Args).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().size(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Bad_Empty_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Bad_Empty_MissingLeft) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Good_One) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeSymbol, token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::ExprLiteralInt32, token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol, "x"),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::List);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::List_Children).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().size(), 1);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::TypeSymbol)
  );

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Bad_One_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Int, "5")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Bad_One_SepInsteadOfRight) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol),
    Token(TokenID::Comma)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Good_Two) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol, "x"),
    Token(TokenID::Comma),
    Token(TokenID::Int, "5"),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::List);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::List_Children).getFormat()),
  	static_cast<int>(FieldFormat::NodeVector)
  );
  ASSERT_EQ(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().size(), 2);
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[0].getType()),
  	static_cast<int>(NodeType::None)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[0].getToken().getText().c_str(), "x");
  ASSERT_EQ(
  	static_cast<int>(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[1].getType()),
  	static_cast<int>(NodeType::None)
  );
  ASSERT_STREQ(res.getNode().getField(FieldTag::List_Children).as<FieldNodeVector>().getValue()[1].getToken().getText().c_str(), "5");

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Two_MissingRight) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Int),
    Token(TokenID::Comma),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Two_SepInsteadOfRight) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Symbol),
    Token(TokenID::Comma),
    Token(TokenID::Int),
    Token(TokenID::Comma)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Two_MissingFirst) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Comma),
    Token(TokenID::Symbol),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Two_MissingSecond) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Int),
    Token(TokenID::Comma),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserGrammar, TemplateList_Two_MissingBoth) {
	ParserGrammar grammar;

	ParserRuleID type = grammar.addTerm(
		"type",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID expr = grammar.addTerm(
		"expr",
		"expr",
		TokenID::Int,
		[](Token token, MessageContext &ctx) {
			return Node(token);
		}
	);

	ParserRuleID rule = grammar.addListBoundSeparated(
		"template args",
		"template args",
		grammar.addAny(
			"template arg",
			"template arg",
			{
				type,
				expr
			}
		),
		grammar.addTerm(
			"<",
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			">",
			">",
			TokenID::GT,
			{
				{TokenID::GE, TokenID::Assign},
				{TokenID::BitShR, TokenID::GT},
				{TokenID::BitShRAssign, TokenID::GE}
			},
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
				nodes.begin(),
				nodes.end()
			);
			return rtn;
		}
	);

  std::vector<Token> toks = {
    Token(TokenID::LT),
    Token(TokenID::Comma),
    Token(TokenID::GT)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

	ASSERT_GT(msgs.getMessageCount(), 0);

  ASSERT_FALSE(res.isGood());
}
