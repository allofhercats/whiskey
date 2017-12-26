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
		if (!res.isGood()) {
			msgs.print(std::cout);
		}

		ASSERT_FALSE(ctx.areMoreTokens());

		ASSERT_TRUE(res.isGood());

		if (AST::compare(Ref<AST>(ast), res.getAST())) {
			SUCCEED();
		} else {
			std::cout << "ASTs do not match.\n";

			DebugPrinter dp(2);
			
			std::cout << "\nExpected:";
			dp.printNewline(std::cout, 1);
			dp.print(std::cout, ast, 1);

			std::cout << "\n\nActual:";
			dp.printNewline(std::cout, 1);
			dp.print(std::cout, res.getAST(), 1);
			std::cout << "\n\n";

			FAIL() << "ASTs do not match.";
		}
	} else if (!ctx.areMoreTokens()) {
		if (res.isGood()) {
			DebugPrinter dp(2);

			std::cout << "Unexpected:";
			dp.printNewline(std::cout, 1);
			dp.print(std::cout, res.getAST(), 1);
			std::cout << "\n\n";
		}

		ASSERT_FALSE(res.isGood());	
	}
}

TEST(Integration_Parsing_Parser, ParseTypeSymbol_0) {
	testHelper(
		Parser::parseTypeSymbol,
		"x",
		new TypeSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeSymbol_1) {
	testHelper(
		Parser::parseTypeSymbol,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_0) {
	testHelper(
		Parser::parseTypeAccessUnary,
		".x",
		new TypeUnary(AST::ID::TypeAccessUnary,
			new TypeSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_1) {
	testHelper(
		Parser::parseTypeAccessUnary,
		"..x",
		new TypeUnary(AST::ID::TypeAccessUnary,
			new TypeUnary(AST::ID::TypeAccessUnary,
				new TypeSymbol("x")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_2) {
	testHelper(
		Parser::parseTypeAccessUnary,
		"x",
		new TypeSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessUnary_3) {
	testHelper(
		Parser::parseTypeAccessUnary,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_0) {
	testHelper(
		Parser::parseTypeAccessBinary,
		"x.y",
		new TypeBinary(AST::ID::TypeAccessBinary,
			new TypeSymbol("x"),
			new TypeSymbol("y")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_1) {
	testHelper(
		Parser::parseTypeAccessBinary,
		"x.y.z",
		new TypeBinary(AST::ID::TypeAccessBinary,
			new TypeSymbol("x"),
			new TypeBinary(AST::ID::TypeAccessBinary,
				new TypeSymbol("y"),
				new TypeSymbol("z")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_2) {
	testHelper(
		Parser::parseTypeAccessBinary,
		".x.y",
		new TypeBinary(AST::ID::TypeAccessBinary,
			new TypeUnary(AST::ID::TypeAccessUnary,
				new TypeSymbol("x")
			),
			new TypeSymbol("y")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_3) {
	testHelper(
		Parser::parseTypeAccessBinary,
		".x.y.z",
		new TypeBinary(AST::ID::TypeAccessBinary,
			new TypeUnary(AST::ID::TypeAccessUnary,
				new TypeSymbol("x")
			),
			new TypeBinary(AST::ID::TypeAccessBinary,
				new TypeSymbol("y"),
				new TypeSymbol("z")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_4) {
	testHelper(
		Parser::parseTypeAccessBinary,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeAccessBinary_5) {
	testHelper(
		Parser::parseTypeAccessBinary,
		"x.",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_0) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- ()",
		new TypeFunction(
			new TypeSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_1) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- (y)",
		new TypeFunction(
			new TypeSymbol("x"),
			{
				new TypeSymbol("y")
			}
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_2) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- (y, z)",
		new TypeFunction(
			new TypeSymbol("x"),
			{
				new TypeSymbol("y"),
				new TypeSymbol("z")
			}
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_3) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- (y, z <- (a, b))",
		new TypeFunction(
			new TypeSymbol("x"),
			{
				new TypeSymbol("y"),
				new TypeFunction(
					new TypeSymbol("z"),
					{
						new TypeSymbol("a"),
						new TypeSymbol("b")
					}
				)
			}
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_4) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- (",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_5) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- )",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_6) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- (,)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_7) {
	testHelper(
		Parser::parseTypeFunction,
		"x <- (x,)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_0) {
	testHelper(
		Parser::parseTypeGroup,
		"(x)",
		new TypeUnary(AST::ID::TypeGroup,
			new TypeSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_1) {
	testHelper(
		Parser::parseTypeGroup,
		"((x))",
		new TypeUnary(AST::ID::TypeGroup,
			new TypeUnary(AST::ID::TypeGroup,
				new TypeSymbol("x")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_2) {
	testHelper(
		Parser::parseTypeGroup,
		"((x)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_3) {
	testHelper(
		Parser::parseTypeGroup,
		"(x",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_4) {
	testHelper(
		Parser::parseTypeGroup,
		"x)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_5) {
	testHelper(
		Parser::parseTypeGroup,
		"()",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeGroup_6) {
	testHelper(
		Parser::parseTypeGroup,
		"x",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseTypeFunction_8) {
	testHelper(
		Parser::parseTypeFunction,
		"(x <- ()) <- ()",
		new TypeFunction(
			new TypeUnary(AST::ID::TypeGroup,
				new TypeFunction(
					new TypeSymbol("x")
				)
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprSymbol_0) {
	testHelper(
		Parser::parseExprSymbol,
		"x",
		new ExprSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprSymbol_1) {
	testHelper(
		Parser::parseExprSymbol,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralInt_0) {
	testHelper(
		Parser::parseExprLiteralInt,
		"5",
		new ExprLiteralInt(new TypeAtomic(AST::ID::TypeAtomicUInt64), 5),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralInt_1) {
	testHelper(
		Parser::parseExprLiteralInt,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralFloat_0) {
	testHelper(
		Parser::parseExprLiteralFloat,
		"3.14",
		new ExprLiteralFloat(new TypeAtomic(AST::ID::TypeAtomicReal), 3.14),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprLiteralFloat_1) {
	testHelper(
		Parser::parseExprLiteralFloat,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_0) {
	testHelper(
		Parser::parseExprAccessUnary,
		".x",
		new ExprUnary(AST::ID::ExprAccessUnary,
			new ExprSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_1) {
	testHelper(
		Parser::parseExprAccessUnary,
		"..x",
		new ExprUnary(AST::ID::ExprAccessUnary,
			new ExprUnary(AST::ID::ExprAccessUnary,
				new ExprSymbol("x")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_2) {
	testHelper(
		Parser::parseExprAccessUnary,
		"x",
		new ExprSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessUnary_3) {
	testHelper(
		Parser::parseExprAccessUnary,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_0) {
	testHelper(
		Parser::parseExprAccessBinary,
		"x.y",
		new ExprBinary(AST::ID::ExprAccessBinary,
			new ExprSymbol("x"),
			new ExprSymbol("y")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_1) {
	testHelper(
		Parser::parseExprAccessBinary,
		"x.y.z",
		new ExprBinary(AST::ID::ExprAccessBinary,
			new ExprSymbol("x"),
			new ExprBinary(AST::ID::ExprAccessBinary,
				new ExprSymbol("y"),
				new ExprSymbol("z")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_2) {
	testHelper(
		Parser::parseExprAccessBinary,
		".x.y",
		new ExprBinary(AST::ID::ExprAccessBinary,
			new ExprUnary(AST::ID::ExprAccessUnary,
				new ExprSymbol("x")
			),
			new ExprSymbol("y")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_3) {
	testHelper(
		Parser::parseExprAccessBinary,
		".x.y.z",
		new ExprBinary(AST::ID::ExprAccessBinary,
			new ExprUnary(AST::ID::ExprAccessUnary,
				new ExprSymbol("x")
			),
			new ExprBinary(AST::ID::ExprAccessBinary,
				new ExprSymbol("y"),
				new ExprSymbol("z")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_4) {
	testHelper(
		Parser::parseExprAccessBinary,
		";",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_5) {
	testHelper(
		Parser::parseExprAccessBinary,
		"x.",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprAccessBinary_6) {
	testHelper(
		Parser::parseExprAccessBinary,
		"x",
		new ExprSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_0) {
	testHelper(
		Parser::parseExprCall,
		"x()",
		new ExprCall(
			new ExprSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_1) {
	testHelper(
		Parser::parseExprCall,
		"x(y)",
		new ExprCall(
			new ExprSymbol("x"),
			{
				new ExprSymbol("y")
			}
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_2) {
	testHelper(
		Parser::parseExprCall,
		"x(y, z)",
		new ExprCall(
			new ExprSymbol("x"),
			{
				new ExprSymbol("y"),
				new ExprSymbol("z")
			}
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_3) {
	testHelper(
		Parser::parseExprCall,
		"x(y, z(a, b))",
		new ExprCall(
			new ExprSymbol("x"),
			{
				new ExprSymbol("y"),
				new ExprCall(
					new ExprSymbol("z"),
					{
						new ExprSymbol("a"),
						new ExprSymbol("b")
					}
				)
			}
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_4) {
	testHelper(
		Parser::parseExprCall,
		"x(",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_5) {
	testHelper(
		Parser::parseExprCall,
		"x)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_6) {
	testHelper(
		Parser::parseExprCall,
		"x(,)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_7) {
	testHelper(
		Parser::parseExprCall,
		"x(x,)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprCall_8) {
	testHelper(
		Parser::parseExprCall,
		"x",
		new ExprSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprUnaryRight_0) {
	testHelper(
		Parser::parseExpr,
		"++x",
		new ExprUnary(AST::ID::ExprIncPre,
			new ExprSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprUnaryLeft_0) {
	testHelper(
		Parser::parseExpr,
		"x++",
		new ExprUnary(AST::ID::ExprIncPost,
			new ExprSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprBinary_0) {
	testHelper(
		Parser::parseExpr,
		"x=y",
		new ExprBinary(AST::ID::ExprAssign,
			new ExprSymbol("x"),
			new ExprSymbol("y")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprSymbol_2) {
	testHelper(
		Parser::parseExpr,
		"x",
		new ExprSymbol("x"),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_0) {
	testHelper(
		Parser::parseExprGroup,
		"(x)",
		new ExprUnary(AST::ID::ExprGroup,
			new ExprSymbol("x")
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_1) {
	testHelper(
		Parser::parseExprGroup,
		"((x))",
		new ExprUnary(AST::ID::ExprGroup,
			new ExprUnary(AST::ID::ExprGroup,
				new ExprSymbol("x")
			)
		),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_2) {
	testHelper(
		Parser::parseExprGroup,
		"((x)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_3) {
	testHelper(
		Parser::parseExprGroup,
		"(x",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_4) {
	testHelper(
		Parser::parseExprGroup,
		"x)",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_5) {
	testHelper(
		Parser::parseExprGroup,
		"()",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseExprGroup_6) {
	testHelper(
		Parser::parseExprGroup,
		"x",
		nullptr,
		false
	);
}

TEST(Integration_Parsing_Parser, ParseStmtEmpty_0) {
	testHelper(
		Parser::parseStmtEmpty,
		";",
		new StmtEmpty(),
		true
	);
}

TEST(Integration_Parsing_Parser, ParseStmtEmpty_1) {
	testHelper(
		Parser::parseStmtEmpty,
		"x;",
		nullptr,
		false
	);
}
