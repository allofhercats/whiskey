#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserContext, Simple) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	Token tok;

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Sub);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Sub);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);

	ASSERT_FALSE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::None);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::None);

	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Simple_Error) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	Token tok;

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Sub);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Sub);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	ctx.emitMessageUnexpectedToken("not a symbol");
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);

	ASSERT_FALSE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::None);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::None);

	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, Injected) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	Token tok;

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Sub);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Sub);

	ctx.injectToken(Token(Token::Add));
	ctx.injectToken(Token(Token::Mul));

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Mul);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Mul);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Add);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Add);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);

	ASSERT_FALSE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::None);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::None);

	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Injected_Error) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	Token tok;

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Sub);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Sub);

	ctx.injectToken(Token(Token::Add));
	ctx.injectToken(Token(Token::Mul));

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Mul);
	ctx.emitMessageUnexpectedToken("not a *");
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Mul);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Mul);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Add);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Add);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);

	ASSERT_FALSE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::None);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::None);

	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryToken) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	Token tok;

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Sub);

	tok = ctx.tryToken(Token::Symbol);
	ASSERT_EQ(tok.getID(), Token::None);

	tok = ctx.tryToken(Token::Sub);
	ASSERT_EQ(tok.getID(), Token::Sub);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);

	ASSERT_FALSE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::None);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::None);

	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, ExpectToken) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	Token tok;

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Sub);

	tok = ctx.expectToken(Token::Symbol, "a symbol");
	ASSERT_EQ(tok.getID(), Token::None);

	tok = ctx.expectToken(Token::Sub, "a -");
	ASSERT_EQ(tok.getID(), Token::Sub);

	ASSERT_TRUE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::Symbol);

	ASSERT_FALSE(ctx.areMoreTokens());
	tok = ctx.getToken();
	ASSERT_EQ(tok.getID(), Token::None);
	tok = ctx.eatToken();
	ASSERT_EQ(tok.getID(), Token::None);

	ASSERT_EQ(msgs.getNMessages(), 1);
}

ParserResult parseRule(ParserContext &ctx) {
	Token tokenSub = ctx.tryToken(Token::Sub);
	if (!tokenSub.isGood()) {
		return ParserResult();
	}

	Token tokenSymbol = ctx.expectToken(Token::Symbol, "symbol");
	if (!tokenSymbol.isGood()) {
		return ParserResult();
	}

	ParserResult res;
	res.setGood(true);
	return res;
}

TEST(Unit_Parsing_ParserContext, Rule_0) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule(ctx);

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Rule_1) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Int)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Int);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, Rule_2) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Rule_3) {
	std::vector<Token> tokens = {
		Token(Token::Sub)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, Rule_4) {
	std::vector<Token> tokens = {
		Token(Token::Add)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Rule_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

ParserResult parseRule2(ParserContext &ctx) {
	Token tokenSub = ctx.tryToken(Token::Add);
	if (!tokenSub.isGood()) {
		return ParserResult();
	}

	Token tokenSymbol = ctx.expectToken(Token::Symbol, "symbol");
	if (!tokenSymbol.isGood()) {
		return ParserResult();
	}

	ParserResult res;
	res.setGood(true);
	return res;
}

TEST(Unit_Parsing_ParserContext, Rule2_0) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule2(ctx);

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Rule2_1) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Int)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule2(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Int);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, Rule2_2) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule2(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Rule2_3) {
	std::vector<Token> tokens = {
		Token(Token::Add)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule2(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, Rule2_4) {
	std::vector<Token> tokens = {
		Token(Token::Sub)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule2(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, Rule2_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = parseRule2(ctx);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParse_0) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParse(parseRule);

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParse_1) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Int)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryParse_2) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParse_3) {
	std::vector<Token> tokens = {
		Token(Token::Sub)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryParse_4) {
	std::vector<Token> tokens = {
		Token(Token::Add)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParse_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, ExpectParse_0) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParse(parseRule, "test syntax");

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, ExpectParse_1) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Int)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParse(parseRule, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 2);
}

TEST(Unit_Parsing_ParserContext, ExpectParse_2) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParse(parseRule, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, ExpectParse_3) {
	std::vector<Token> tokens = {
		Token(Token::Sub)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParse(parseRule, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 2);
}

TEST(Unit_Parsing_ParserContext, ExpectParse_4) {
	std::vector<Token> tokens = {
		Token(Token::Add)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParse(parseRule, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, ExpectParse_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParse(parseRule, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_0) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParseAny({
		parseRule,
		parseRule2
	});

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_1) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Int)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParseAny({
		parseRule,
		parseRule2
	});

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_2) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParseAny({
		parseRule,
		parseRule2
	});

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_3) {
	std::vector<Token> tokens = {
		Token(Token::Sub)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParseAny({
		parseRule,
		parseRule2
	});

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_4) {
	std::vector<Token> tokens = {
		Token(Token::Add)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParseAny({
		parseRule,
		parseRule2
	});

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 1);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.tryParseAny({
		parseRule,
		parseRule2
	});

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, ExpectParseAny_0) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParseAny({
		parseRule,
		parseRule2
	}, "test syntax");

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, ExpectParseAny_1) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Int)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParseAny({
		parseRule,
		parseRule2
	}, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 2);
}

TEST(Unit_Parsing_ParserContext, ExpectParseAny_2) {
	std::vector<Token> tokens = {
		Token(Token::Add),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParseAny({
		parseRule,
		parseRule2
	}, "test syntax");

	ASSERT_TRUE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, ExpectParseAny_3) {
	std::vector<Token> tokens = {
		Token(Token::Sub)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParseAny({
		parseRule,
		parseRule2
	}, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Sub);
	ASSERT_EQ(msgs.getNMessages(), 2);
}

TEST(Unit_Parsing_ParserContext, ExpectParseAny_4) {
	std::vector<Token> tokens = {
		Token(Token::Add)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParseAny({
		parseRule,
		parseRule2
	}, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 2);
}

TEST(Unit_Parsing_ParserContext, ExpectParseAny_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.expectParseAny({
		parseRule,
		parseRule2
	}, "test syntax");

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 1);
}
