#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

void testHelper(ParserContext::Rule rule, const char *text, AST *ast, bool success) {
	Source src;
	src.loadCString(text);

	Location loc(src);

	std::vector<Token> tokens;
	MessageBuffer msgs;

	Lexer lexer(loc, tokens, msgs);
	lexer.lex();

	ASSERT_EQ(msgs.getNMessages(), 0);

	ParserContext ctx(tokens, msgs);

	ParserResult res = rule(ctx);

	if (success) {
		ASSERT_TRUE(res.isGood());

		if (AST::compare(Ref<AST>(ast), res.getAST())) {

		} else {
			std::cout << "AST do not match.\n";
		}
	}
}

TEST(Test_Parsing_Parser, ParseTemplateEvalArg_0) {

}

TEST(Test_Parsing_Parser, ParseTypeSymbol_0) {

}
