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
#include <whiskey/Parsing/ParserRuleTerm.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserRuleTerm, Good) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<ParserRuleTerm>("asdf", "asdf", TokenID::Symbol, [](Token token, MessageContext &) {
    return Node(NodeType::StmtEmpty, token);
  }));

  std::vector<Token> toks = {
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;

  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::Symbol);
  ASSERT_EQ(msgs.getMessageCount(), 0);
}

TEST(Unit_Parsing_ParserRuleTerm, Bad) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<ParserRuleTerm>("asdf", "asdf", TokenID::Symbol, [](Token token, MessageContext &) {
    return Node(NodeType::StmtEmpty, token);
  }));

  std::vector<Token> toks = {
    Token(TokenID::Int)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleTerm, Keyword_Good) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<ParserRuleTerm>("asdf", "asdf", TokenID::Symbol, "hi", [](Token token, MessageContext &) {
    return Node(NodeType::StmtEmpty, token);
  }));

  std::vector<Token> toks = {
    Token(TokenID::Symbol, "hi")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::Symbol);
  ASSERT_STREQ(res.getNode().getToken().getText().c_str(), "hi");
  ASSERT_EQ(msgs.getMessageCount(), 0);
}

TEST(Unit_Parsing_ParserRuleTerm, Keyword_Bad_Text) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<ParserRuleTerm>("asdf", "asdf", TokenID::Symbol, "hi", [](Token token, MessageContext &) {
    return Node(NodeType::StmtEmpty, token);
  }));

  std::vector<Token> toks = {
    Token(TokenID::Symbol, "bye")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleTerm, Keyword_Bad_TokenID) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(std::make_unique<ParserRuleTerm>("asdf", "asdf", TokenID::Symbol, "hi", [](Token token, MessageContext &) {
    return Node(NodeType::StmtEmpty, token);
  }));

  std::vector<Token> toks = {
    Token(TokenID::Int, "hi")
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Good_WithBase_Base_Middle) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      TokenID::GT,
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
    )
  );

  std::vector<Token> toks = {
    Token(TokenID::GT),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::GT);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Symbol);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Good_WithBase_Base_End) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      TokenID::GT,
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
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
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Good_WithBase_Injecting_Middle) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      TokenID::GT,
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
    )
  );

  std::vector<Token> toks = {
    Token(TokenID::GE),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::GE);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Assign);
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Symbol);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Good_WithBase_Injecting_End) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      TokenID::GT,
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
    )
  );

  std::vector<Token> toks = {
    Token(TokenID::BitShR)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::BitShR);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::GT);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Bad_NoBase_Base_Middle) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
    )
  );

  std::vector<Token> toks = {
    Token(TokenID::GT),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Bad_NoBase_Base_End) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
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

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Good_NoBase_Injecting_Middle) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
    )
  );

  std::vector<Token> toks = {
    Token(TokenID::GE),
    Token(TokenID::Symbol)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::GE);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Assign);
  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::Symbol);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Good_NoBase_Injecting_End) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
      }
    )
  );

  std::vector<Token> toks = {
    Token(TokenID::BitShR)
  };

  ParserContext ctx(toks);
  MessageContext msgs;
  
  ParserResult res = grammar.getRule(rule).parse(grammar, ctx, msgs);

  ASSERT_TRUE(res.isGood());
  ASSERT_EQ(res.getNode().getType(), NodeType::StmtEmpty);
  ASSERT_EQ(res.getNode().getToken().getID(), TokenID::BitShR);
  ASSERT_EQ(msgs.getMessageCount(), 0);

  ASSERT_TRUE(ctx.more());
  ASSERT_EQ(ctx.eat().getID(), TokenID::GT);
  ASSERT_FALSE(ctx.more());
}

TEST(Unit_Parsing_ParserRuleTerm, Injecting_Bad_TokenID) {
  ParserGrammar grammar;

  ParserRuleID rule = grammar.addRule(
    std::make_unique<ParserRuleTerm>(
      "asdf",
      "asdf",
      TokenID::GT,
      std::vector<std::pair<TokenID, TokenID>>({
        {TokenID::GE, TokenID::Assign},
        {TokenID::BitShR, TokenID::GT},
        {TokenID::BitShRAssign, TokenID::GE}
      }),
      [](Token token, MessageContext &) {
        return Node(NodeType::StmtEmpty, token);
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
