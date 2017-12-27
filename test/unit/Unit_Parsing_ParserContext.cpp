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
	ctx.errorUnexpectedToken("not a symbol");
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
	ctx.errorUnexpectedToken("not a *");
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

ParserResult parseRule(ParserContext &ctx) {
	Token tokenSub = ctx.getToken();
	if (tokenSub.getID() == Token::Sub) {
		ctx.eatToken();
	} else {
		return ParserResult();
	}

	Token tokenSymbol = ctx.getToken();
	if (tokenSymbol.getID() == Token::Symbol) {
		ctx.eatToken();
	} else {
		ctx.errorUnexpectedToken("symbol");
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
	Token tokenAdd = ctx.getToken();
	if (tokenAdd.getID() == Token::Add) {
		ctx.eatToken();
	} else {
		return ParserResult();
	}

	Token tokenSymbol = ctx.getToken();
	if (tokenSymbol.getID() == Token::Symbol) {
		ctx.eatToken();
	} else {
		ctx.errorUnexpectedToken("symbol");
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

	ParserResult res = ctx.parse(parseRule);

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

	ParserResult res = ctx.parse(parseRule);

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

	ParserResult res = ctx.parse(parseRule);

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

	ParserResult res = ctx.parse(parseRule);

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

	ParserResult res = ctx.parse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::Add);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParse_5) {
	std::vector<Token> tokens;

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.parse(parseRule);

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}

TEST(Unit_Parsing_ParserContext, TryParseAny_0) {
	std::vector<Token> tokens = {
		Token(Token::Sub),
		Token(Token::Symbol)
	};

	MessageBuffer msgs;

	ParserContext ctx(tokens, msgs);

	ParserResult res = ctx.parseAny({
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

	ParserResult res = ctx.parseAny({
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

	ParserResult res = ctx.parseAny({
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

	ParserResult res = ctx.parseAny({
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

	ParserResult res = ctx.parseAny({
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

	ParserResult res = ctx.parseAny({
		parseRule,
		parseRule2
	});

	ASSERT_FALSE(res.isGood());
	ASSERT_EQ(ctx.getToken().getID(), Token::None);
	ASSERT_EQ(msgs.getNMessages(), 0);
}
