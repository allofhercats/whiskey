#include "Module.inc"

#include <whiskey/Parsing/Parser.hpp>

namespace whiskey {
// ParserResult Parser::parseTemplateEvalArg(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseType,
// 		parseExpr
// 	});
// }

// ParserResult Parser::parseTypeSymbol(ParserContext &ctx) {
// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (!tokenLBracket.isGood()) {
// 		return ParserResult(new TypeSymbol(tokenSymbol.getRange(), tokenSymbol.getRange().getText()));
// 	} else {
// 		Container<TypeSymbol> ast = new TypeSymbol(tokenSymbol.getRange(), tokenSymbol.getRange().getText());
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseTemplateEvalArg, "template arg");
// 			if (arg.isGood()) {
// 				ast->getTemplateEvalArgs().push_back(arg.getAST()->clone());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.emitMessageUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.emitMessageUnexpectedToken("closing >");
// 		}

// 		return ParserResult(ast->clone());
// 	}
// }

// ParserResult Parser::parseTypeTerm(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseTypeSymbol,
// 		parseTypeGroup
// 	});
// }

// ParserResult Parser::parseTypeAccessUnary(ParserContext &ctx) {
// 	Token tokenOp = ctx.tryToken(Token::Period);
// 	if (!tokenOp.isGood()) {
// 		return parseTypeTerm(ctx);
// 	}

// 	ParserResult res = ctx.expectParse(parseTypeAccessUnary, "type");
// 	if (!res.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new TypeUnary(AST::ID::TypeAccessUnary, tokenOp.getRange(), res.getAST()->cloneAs<Type>()));
// }

// ParserResult Parser::parseTypeAccessBinary(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseTypeAccessUnary);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.tryToken(Token::Period);
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	ParserResult rhs = ctx.expectParse(parseTypeAccessBinary, "type");
// 	if (!rhs.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new TypeBinary(AST::ID::TypeAccessBinary, tokenOp.getRange(), lhs.getAST()->cloneAs<Type>(), rhs.getAST()->cloneAs<Type>()));
// }

// ParserResult Parser::parseTypeFunction(ParserContext &ctx) {
// 	ParserResult ret = ctx.tryParse(parseTypeAccessBinary);
// 	if (!ret.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLArrow = ctx.tryToken(Token::LArrow);
// 	if (!tokenLArrow.isGood()) {
// 		return ret;
// 	}

// 	Token tokenLParen = ctx.expectToken(Token::LParen, "(");
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	Container<TypeFunction> ast = new TypeFunction(tokenLArrow.getRange(), ret.getAST()->cloneAs<Type>(), {});
// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (tokenSep.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		}

// 		ParserResult arg = ctx.expectParse(parseType, "type");
// 		if (arg.isGood()) {
// 			ast->getArgs().push_back(arg.getAST()->cloneAs<Type>());
// 		} else {
// 			return ParserResult();
// 		}
		
// 		tokenSep = ctx.getToken();
// 		if (tokenSep.getID() == Token::Comma) {
// 			ctx.eatToken();
// 			tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::RParen) {
// 				ctx.emitMessageUnexpectedToken("type");
// 				return ParserResult();
// 			}
// 		} else if (tokenSep.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ctx.emitMessageUnexpectedToken(", or )");
// 			return ParserResult();
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken("closing )");
// 		return ParserResult();
// 	}

// 	return ParserResult(ast->clone());
// }

// ParserResult Parser::parseTypeGroup(ParserContext &ctx) {
// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult arg = ctx.expectParse(parseType, "type");
// 	if (!arg.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.expectToken(Token::RParen, ")");
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(
// 		new TypeUnary(
// 			AST::ID::TypeGroup,
// 			tokenLParen.getRange(),
// 			arg.getAST()->cloneAs<Type>()
// 		)
// 	);
// }

// ParserResult Parser::parseType(ParserContext &ctx) {
// 	return parseTypeFunction(ctx);
// }

// ParserResult Parser::parseExprSymbol(ParserContext &ctx) {
// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (!tokenLBracket.isGood()) {
// 		return ParserResult(new ExprSymbol(tokenSymbol.getRange(), tokenSymbol.getRange().getText()));
// 	} else {
// 		Container<ExprSymbol> ast = new ExprSymbol(tokenSymbol.getRange(), tokenSymbol.getRange().getText());
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseTemplateEvalArg, "template arg");
// 			if (arg.isGood()) {
// 				ast->getTemplateEvalArgs().push_back(arg.getAST()->clone());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.emitMessageUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.emitMessageUnexpectedToken("closing >");
// 		}

// 		return ParserResult(ast->clone());
// 	}
// }

// ParserResult Parser::parseExprLiteralInt(ParserContext &ctx) {
// 	Token tokenInt = ctx.tryToken(Token::Int);
// 	if (!tokenInt.isGood()) {
// 		return ParserResult();
// 	}

// 	uint64_t tmp;
// 	if (!evalLiteralUInt64(tokenInt.getRange(), tmp)) {
// 		return ParserResult();
// 	}

// 	return ParserResult(
// 		new ExprLiteralInt(
// 			tokenInt.getRange(),
// 			new TypeAtomic(AST::ID::TypeAtomicUInt64, Range()),
// 			tmp
// 		)
// 	);
// }

// ParserResult Parser::parseExprLiteralFloat(ParserContext &ctx) {
// 	Token tokenInt = ctx.tryToken(Token::Float);
// 	if (!tokenInt.isGood()) {
// 		return ParserResult();
// 	}

// 	long double tmp;
// 	if (!evalLiteralReal(tokenInt.getRange(), tmp)) {
// 		return ParserResult();
// 	}

// 	return ParserResult(
// 		new ExprLiteralFloat(
// 			tokenInt.getRange(),
// 			new TypeAtomic(AST::ID::TypeAtomicReal, Range()),
// 			tmp
// 		)
// 	);
// }

// ParserResult Parser::parseExprGroup(ParserContext &ctx) {
// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult arg = ctx.expectParse(parseExpr, "expression");
// 	if (!arg.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.expectToken(Token::RParen, ")");
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(
// 		new ExprUnary(
// 			AST::ID::ExprGroup,
// 			tokenLParen.getRange(),
// 			arg.getAST()->cloneAs<Expr>()
// 		)
// 	);
// }

// ParserResult Parser::parseExprTerm(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseExprSymbol,
// 		parseExprLiteralInt,
// 		parseExprLiteralFloat,
// 		parseExprGroup
// 	});
// }

// ParserResult Parser::parseExprAccessUnary(ParserContext &ctx) {
// 	Token tokenOp = ctx.tryToken(Token::Period);
// 	if (!tokenOp.isGood()) {
// 		return parseExprTerm(ctx);
// 	}

// 	ParserResult res = ctx.expectParse(parseExprAccessUnary, "expression");
// 	if (!res.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new ExprUnary(AST::ID::ExprAccessUnary, tokenOp.getRange(), res.getAST()->cloneAs<Expr>()));
// }

// ParserResult Parser::parseExprAccessBinary(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprAccessUnary);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.tryToken(Token::Period);
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	ParserResult rhs = ctx.expectParse(parseExprAccessBinary, "expression");
// 	if (!rhs.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new ExprBinary(AST::ID::ExprAccessBinary, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// }

// ParserResult Parser::parseExprCall(ParserContext &ctx) {
// 	ParserResult ret = ctx.tryParse(parseExprAccessBinary);
// 	if (!ret.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ret;
// 	}

// 	Container<ExprCall> ast = new ExprCall(tokenLParen.getRange(), ret.getAST()->cloneAs<Expr>(), {});
// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (tokenSep.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		}

// 		ParserResult arg = ctx.expectParse(parseExpr, "expression");
// 		if (arg.isGood()) {
// 			ast->getArgs().push_back(arg.getAST()->cloneAs<Expr>());
// 		} else {
// 			return ParserResult();
// 		}
		
// 		tokenSep = ctx.getToken();
// 		if (tokenSep.getID() == Token::Comma) {
// 			ctx.eatToken();
// 			tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::RParen) {
// 				ctx.emitMessageUnexpectedToken("expression");
// 			return ParserResult();
// 			}
// 		} else if (tokenSep.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ctx.emitMessageUnexpectedToken(", or )");
// 			return ParserResult();
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken("closing )");
// 		return ParserResult();
// 	}

// 	return ParserResult(ast->clone());
// }

// ParserResult Parser::parseExprUnaryRight(ParserContext &ctx) {
// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return ParserResult();
// 	}

// 	if (tokenOp.getID() == Token::Inc) {
// 		ctx.eatToken();
// 		ParserResult res = ctx.expectParse(parseExprUnaryRight, "expression");
// 		if (!res.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprUnary(AST::ID::ExprIncPre, tokenOp.getRange(), res.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::Dec) {
// 		ctx.eatToken();
// 		ParserResult res = ctx.expectParse(parseExprUnaryRight, "expression");
// 		if (!res.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprUnary(AST::ID::ExprDecPre, tokenOp.getRange(), res.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::Sub) {
// 		ctx.eatToken();
// 		ParserResult res = ctx.expectParse(parseExprUnaryRight, "expression");
// 		if (!res.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprUnary(AST::ID::ExprNegate, tokenOp.getRange(), res.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitNot) {
// 		ctx.eatToken();
// 		ParserResult res = ctx.expectParse(parseExprUnaryRight, "expression");
// 		if (!res.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprUnary(AST::ID::ExprBitNot, tokenOp.getRange(), res.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return parseExprCall(ctx);
// 	}
// }

// ParserResult Parser::parseExprUnaryLeft(ParserContext &ctx) {
// 	ParserResult res = ctx.expectParse(parseExprUnaryRight, "expression");
// 	if (!res.isGood()) {
// 		return ParserResult();
// 	}

// 	Container<Expr> ast = res.getAST()->cloneAs<Expr>();

// 	while (true) {
// 		Token tokenOp = ctx.getToken();
// 		if (!tokenOp.isGood()) {
// 			return ParserResult(ast->clone());
// 		} else if (tokenOp.getID() == Token::Inc) {
// 			ctx.eatToken();
// 			ast = new ExprUnary(AST::ID::ExprIncPost, tokenOp.getRange(), ast->cloneAs<Expr>());
// 		} else if (tokenOp.getID() == Token::Dec) {
// 			ctx.eatToken();
// 			ast = new ExprUnary(AST::ID::ExprDecPost, tokenOp.getRange(), ast->cloneAs<Expr>());
// 		} else {
// 			return ParserResult(ast->clone());
// 		}
// 	}
// }

// ParserResult Parser::parseExprExp(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprUnaryLeft);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::Exp) {
// 		ParserResult rhs = ctx.expectParse(parseExprExp, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprExp, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprMul(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprExp);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::Mul) {
// 		ParserResult rhs = ctx.expectParse(parseExprMul, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprMul, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::Div) {
// 		ParserResult rhs = ctx.expectParse(parseExprMul, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprDiv, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::DivInt) {
// 		ParserResult rhs = ctx.expectParse(parseExprMul, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprDivInt, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::DivReal) {
// 		ParserResult rhs = ctx.expectParse(parseExprMul, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprDivReal, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprAdd(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprMul);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::Add) {
// 		ParserResult rhs = ctx.expectParse(parseExprAdd, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprAdd, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::Sub) {
// 		ParserResult rhs = ctx.expectParse(parseExprAdd, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprSub, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprMod(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprAdd);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::Mod) {
// 		ParserResult rhs = ctx.expectParse(parseExprMod, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprMod, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBitShR(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprMod);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::BitShR) {
// 		ParserResult rhs = ctx.expectParse(parseExprBitShR, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitShR, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBitShL(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBitShR);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::BitShL) {
// 		ParserResult rhs = ctx.expectParse(parseExprBitShL, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitShL, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBitAnd(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBitShL);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::BitAnd) {
// 		ParserResult rhs = ctx.expectParse(parseExprBitAnd, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitAnd, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBitOr(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBitAnd);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::BitOr) {
// 		ParserResult rhs = ctx.expectParse(parseExprBitOr, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitOr, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitXor) {
// 		ParserResult rhs = ctx.expectParse(parseExprBitOr, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitXor, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprCompare(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBitOr);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::LT) {
// 		ParserResult rhs = ctx.expectParse(parseExprCompare, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprLT, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::LE) {
// 		ParserResult rhs = ctx.expectParse(parseExprCompare, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprLE, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::GT) {
// 		ParserResult rhs = ctx.expectParse(parseExprCompare, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprGT, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::GE) {
// 		ParserResult rhs = ctx.expectParse(parseExprCompare, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprGE, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::NE) {
// 		ParserResult rhs = ctx.expectParse(parseExprCompare, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprNE, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::EQ) {
// 		ParserResult rhs = ctx.expectParse(parseExprCompare, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprEQ, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBoolNot(ParserContext &ctx) {
// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return ParserResult();
// 	}

// 	if (tokenOp.getID() == Token::KWNot) {
// 		ParserResult res = ctx.expectParse(parseExprBoolNot, "expression");
// 		if (!res.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprUnary(AST::ID::ExprBoolNot, tokenOp.getRange(), res.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return parseExprCompare(ctx);
// 	}
// }

// ParserResult Parser::parseExprBoolAnd(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBoolNot);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::KWAnd) {
// 		ParserResult rhs = ctx.expectParse(parseExprBoolAnd, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBoolAnd, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBoolOr(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBoolAnd);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::KWOr) {
// 		ParserResult rhs = ctx.expectParse(parseExprBoolOr, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBoolOr, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprBoolImplies(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBoolOr);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::BoolImplies) {
// 		ParserResult rhs = ctx.expectParse(parseExprBoolImplies, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBoolImplies, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExprAssign(ParserContext &ctx) {
// 	ParserResult lhs = ctx.tryParse(parseExprBoolImplies);
// 	if (!lhs.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenOp = ctx.getToken();
// 	if (!tokenOp.isGood()) {
// 		return lhs;
// 	}

// 	if (tokenOp.getID() == Token::ExpAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprExpAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::MulAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprMulAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::DivAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprDivAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::DivIntAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprDivIntAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::DivRealAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprDivRealAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::AddAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprAddAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::SubAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprSubAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::ModAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprModAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitShRAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitShRAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitShLAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitShLAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitAndAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitAndAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitOrAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitOrAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::BitXorAssign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprBitXorAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else if (tokenOp.getID() == Token::Assign) {
// 		ctx.eatToken();
// 		ParserResult rhs = ctx.expectParse(parseExprAssign, "expression");
// 		if (!rhs.isGood()) {
// 			return ParserResult();
// 		}

// 		return ParserResult(new ExprBinary(AST::ID::ExprAssign, tokenOp.getRange(), lhs.getAST()->cloneAs<Expr>(), rhs.getAST()->cloneAs<Expr>()));
// 	} else {
// 		return lhs;
// 	}
// }

// ParserResult Parser::parseExpr(ParserContext &ctx) {
// 	return parseExprAssign(ctx);
// }

// ParserResult Parser::parseStmtEmpty(ParserContext &ctx) {
// 	Token tokenSemicolon = ctx.tryToken(Token::Semicolon);
// 	if (!tokenSemicolon.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new StmtEmpty(tokenSemicolon.getRange()));
// }

// ParserResult Parser::parseStmtExpr(ParserContext &ctx) {
// 	ParserResult res = ctx.tryParse(parseExpr);
// 	if (!res.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSemicolon = ctx.tryToken(Token::Semicolon);
// 	if (!tokenSemicolon.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new StmtExpr(AST::ID::StmtExpr, tokenSemicolon.getRange(), res.getAST()->cloneAs<Expr>()));
// }

// ParserResult Parser::parseStmtReturn(ParserContext &ctx) {
// 	Token tokenReturn = ctx.tryToken(Token::KWReturn);
// 	if (!tokenReturn.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ctx.tryParse(parseExpr);

// 	Token tokenRParen = ctx.tryToken(Token::RParen);
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSemicolon = ctx.tryToken(Token::Semicolon);
// 	if (!tokenSemicolon.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new StmtExpr(AST::ID::StmtReturn, tokenSemicolon.getRange(), res.isGood() ? res.getAST()->cloneAs<Expr>() : nullptr));
// }

// ParserResult Parser::parseStmtIf(ParserContext &ctx) {
// 	Token tokenIf = ctx.tryToken(Token::KWIf);
// 	if (!tokenIf.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult cond = ctx.expectParse(parseExpr, "condition");
// 	if (!cond.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.tryToken(Token::RParen);
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult thenClause = ctx.expectParse(parseStmt, "then clause");
// 	if (!thenClause.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenElse = ctx.tryToken(Token::KWElse);
// 	if (!tokenElse.isGood()) {
// 		return ParserResult(new StmtIf(tokenIf.getRange(), cond.getAST()->cloneAs<Expr>(), thenClause.getAST()->cloneAs<Stmt>()));
// 	}

// 	ParserResult elseClause = ctx.expectParse(parseStmt, "else clause");
// 	if (!elseClause.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new StmtIf(tokenIf.getRange(), cond.getAST()->cloneAs<Expr>(), thenClause.getAST()->cloneAs<Stmt>(), elseClause.getAST()->cloneAs<Stmt>()));
// }

// ParserResult Parser::parseStmtWhile(ParserContext &ctx) {
// 	Token tokenWhile = ctx.tryToken(Token::KWWhile);
// 	if (!tokenWhile.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult cond = ctx.expectParse(parseExpr, "condition");
// 	if (!cond.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.tryToken(Token::RParen);
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult body = ctx.expectParse(parseStmt, "body");
// 	if (!body.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new StmtWhile(tokenWhile.getRange(), cond.getAST()->cloneAs<Expr>(), body.getAST()->cloneAs<Stmt>()));
// }

// ParserResult Parser::parseStmtFor(ParserContext &ctx) {
// 	Token tokenFor = ctx.tryToken(Token::KWFor);
// 	if (!tokenFor.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new StmtFor(tokenFor.getRange()));

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSepFirst = ctx.getToken();
// 		if (!tokenSepFirst.isGood()) {
// 			ctx.emitMessageUnexpectedToken("variable declaration or ;");
// 			return ParserResult();
// 		} else if (tokenSepFirst.getID() == Token::Semicolon) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else if (tokenSepFirst.getID() == Token::Comma) {
// 			ctx.eatToken();
// 		} else {
// 			ParserResult decl = ctx.expectParse(parseDeclVariable, "variable declaration");
// 			if (!decl.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<StmtFor>()->getDecls().push_back(decl.getAST()->cloneAs<DeclVariable>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken(";");
// 		return ParserResult();
// 	}

// 	ParserResult cond = ctx.expectParse(parseExpr, "condition");
// 	if (!cond.isGood()) {
// 		return ParserResult();
// 	}

// 	res.getAST()->as<StmtFor>()->setCondition(cond.getAST()->cloneAs<Expr>());

// 	Token tokenSepSecond = ctx.expectToken(Token::Semicolon, ";");
// 	if (!tokenSepSecond.isGood()) {
// 		return ParserResult();
// 	}

// 	endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSepThird = ctx.getToken();
// 		if (!tokenSepThird.isGood()) {
// 			ctx.emitMessageUnexpectedToken("expression or )");
// 		} else if (tokenSepThird.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			break;
// 		} else if (tokenSepThird.getID() == Token::Comma) {
// 			ctx.eatToken();
// 		} else {
// 			ParserResult step = ctx.expectParse(parseExpr, "expression");
// 			if (!step.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<StmtFor>()->getSteps().push_back(step.getAST()->cloneAs<Expr>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken(")");
// 		return ParserResult();
// 	}

// 	ParserResult body = ctx.expectParse(parseStmt, "body");
// 	if (!body.isGood()) {
// 		return ParserResult();
// 	}

// 	res.getAST()->as<StmtFor>()->setBodyClause(body.getAST()->cloneAs<Stmt>());

// 	return res;
// }

// ParserResult Parser::parseStmtForEach(ParserContext &ctx) {
// 	Token tokenForEach = ctx.tryToken(Token::KWForEach);
// 	if (!tokenForEach.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult decl = ctx.expectParse(parseDeclVariable, "variable declaration");
// 	if (!decl.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSemicolon = ctx.expectToken(Token::Semicolon, ";");
// 	if (!tokenSemicolon.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult seq = ctx.expectParse(parseExpr, "expression");
// 	if (!seq.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.tryToken(Token::RParen);
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult body = ctx.expectParse(parseStmt, "body");
// 	if (!body.isGood()) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new StmtForEach(tokenForEach.getRange(), decl.getAST()->cloneAs<Decl>(), seq.getAST()->cloneAs<Expr>(), body.getAST()->cloneAs<Stmt>()));
// }

// ParserResult Parser::parseStmtBlock(ParserContext &ctx) {
// 	Token tokenLBrace = ctx.expectToken(Token::LBrace, "{");
// 	if (!tokenLBrace.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new StmtBlock(tokenLBrace.getRange()));

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.emitMessageUnexpectedToken("statement or }");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RBrace) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult stmt = ctx.expectParse(parseStmt, "statement");
// 			if (!stmt.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<StmtBlock>()->getBody().push_back(stmt.getAST()->cloneAs<Stmt>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken("}");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseStmt(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseStmtBlock,
// 		parseStmtIf,
// 		parseStmtWhile,
// 		parseStmtFor,
// 		parseStmtForEach,
// 		parseStmtReturn,
// 		parseStmtEmpty,
// 		parseStmtExpr
// 	});
// }

// ParserResult Parser::parseDeclVariable(ParserContext &ctx) {
// 	ParserResult type = ctx.expectParse(parseType, "type");
// 	if (!type.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclVariable(tokenSymbol.getRange(), type.getAST()->cloneAs<Type>(), tokenSymbol.getRange().getText()));

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (tokenLBracket.isGood()) {
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable, "template arg");
// 			if (arg.isGood()) {
// 				res.getAST()->as<DeclVariable>()->getTemplateDeclArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.emitMessageUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.emitMessageUnexpectedToken("closing >");
// 			return ParserResult();
// 		}
// 	}

// 	Token tokenSep = ctx.getToken();
// 	if (!tokenSep.isGood()) {
// 		ctx.emitMessageUnexpectedToken("= or ;");
// 		return ParserResult();
// 	} else if (tokenSep.getID() == Token::Semicolon) {
// 		ctx.eatToken();
// 		return res;
// 	} else if (tokenSep.getID() == Token::Assign) {
// 		ctx.eatToken();
// 		ParserResult init = ctx.expectParse(parseExpr, "expression");
// 		if (!init.isGood()) {
// 			return ParserResult();
// 		}

// 		tokenSep = ctx.expectToken(Token::Semicolon, ";");
// 		if (!tokenSep.isGood()) {
// 			return ParserResult();
// 		}

// 		res.getAST()->as<DeclVariable>()->setInit(init.getAST()->cloneAs<Expr>());
// 	}

// 	return res;
// }

// ParserResult Parser::parseDeclFunction(ParserContext &ctx) {
// 	ParserResult type = ctx.expectParse(parseType, "type");
// 	if (!type.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclFunction(tokenSymbol.getRange(), type.getAST()->cloneAs<Type>(), tokenSymbol.getRange().getText()));

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (tokenLBracket.isGood()) {
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable, "template arg");
// 			if (arg.isGood()) {
// 				res.getAST()->as<DeclFunction>()->getTemplateDeclArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.emitMessageUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.emitMessageUnexpectedToken("closing >");
// 			return ParserResult();
// 		}
// 	}

// 	Token tokenLBrace = ctx.expectToken(Token::LParen, "(");
// 	if (!tokenLBrace.isGood()) {
// 		return ParserResult();
// 	}

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.emitMessageUnexpectedToken("argument or )");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RParen) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable, "argument");
// 			if (!arg.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<DeclFunction>()->getArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken(")");
// 		return ParserResult();
// 	}

// 	Token tokenSep = ctx.getToken();
// 	if (!tokenSep.isGood()) {
// 		ctx.emitMessageUnexpectedToken("=, ;, or {");
// 		return ParserResult();
// 	} else if (tokenSep.getID() == Token::Semicolon) {
// 		ctx.eatToken();
// 		return res;
// 	} else if (tokenSep.getID() == Token::Assign) {
// 		ctx.eatToken();
// 		ParserResult init = ctx.expectParse(parseStmtExpr, "expression");
// 		if (!init.isGood()) {
// 			return ParserResult();
// 		}

// 		res.getAST()->as<DeclFunction>()->setBody(init.getAST()->cloneAs<Stmt>());
// 	} else if (tokenSep.getID() == Token::LBrace) {
// 		ParserResult body = ctx.expectParse(parseStmtBlock, "body");
// 		if (!body.isGood()) {
// 			return ParserResult();
// 		}

// 		tokenSep = ctx.expectToken(Token::Semicolon, ";");
// 		if (!tokenSep.isGood()) {
// 			return ParserResult();
// 		}

// 		res.getAST()->as<DeclFunction>()->setBody(body.getAST()->cloneAs<Stmt>());
// 	} else {
// 		ctx.emitMessageUnexpectedToken("=, ;, or {");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseDeclClass(ParserContext &ctx) {
// 	Token tokenClass = ctx.tryToken(Token::KWClass);
// 	if (!tokenClass.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclClass(tokenSymbol.getRange(), tokenSymbol.getRange().getText()));

// 	Token tokenLBracket = ctx.tryToken(Token::LT);
// 	if (tokenLBracket.isGood()) {
// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			ParserResult arg = ctx.expectParse(parseDeclVariable, "template arg");
// 			if (arg.isGood()) {
// 				res.getAST()->as<DeclClass>()->getTemplateDeclArgs().push_back(arg.getAST()->cloneAs<DeclVariable>());
// 			}
// 			Token tokenSep = ctx.getToken();
// 			if (tokenSep.getID() == Token::Comma) {
// 				ctx.eatToken();
// 			} else if (tokenSep.getID() == Token::GT) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::GE) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::Assign));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShR) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GT));
// 				endedCorrectly = true;
// 				break;
// 			} else if (tokenSep.getID() == Token::BitShRAssign) {
// 				ctx.eatToken();
// 				ctx.injectToken(Token(Token::GE));
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ctx.emitMessageUnexpectedToken(", or >");
// 				ctx.eatToken();
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.emitMessageUnexpectedToken("closing >");
// 			return ParserResult();
// 		}
// 	}

// 	Token tokenSep = ctx.getToken();
// 	if (!tokenSep.isGood()) {
// 		ctx.emitMessageUnexpectedToken("inherits or {");
// 		return ParserResult();
// 	} else if (tokenSep.getID() == Token::KWInherits) {
// 		ctx.eatToken();

// 		bool endedCorrectly = false;
// 		while (ctx.areMoreTokens()) {
// 			Token tokenSep = ctx.getToken();
// 			if (!tokenSep.isGood()) {
// 				ctx.emitMessageUnexpectedToken("type or {");
// 				return ParserResult();
// 			} else if (tokenSep.getID() == Token::LBrace) {
// 				ctx.eatToken();
// 				endedCorrectly = true;
// 				break;
// 			} else {
// 				ParserResult arg = ctx.expectParse(parseType, "type");
// 				if (!arg.isGood()) {
// 					return ParserResult();
// 				}
// 				res.getAST()->as<DeclClass>()->getInherits().push_back(arg.getAST()->cloneAs<Type>());
// 			}
// 		}

// 		if (!endedCorrectly) {
// 			ctx.emitMessageUnexpectedToken("{");
// 			return ParserResult();
// 		}
// 	} else if (tokenSep.getID() == Token::LBrace) {
// 		ctx.eatToken();
// 	} else {
// 		ctx.emitMessageUnexpectedToken("implements or {");
// 		return ParserResult();
// 	}

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.emitMessageUnexpectedToken("declaration or }");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RBrace) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult decl = ctx.expectParse(parseDecl, "declaration");
// 			if (!decl.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<DeclClass>()->getMembers().push_back(decl.getAST()->cloneAs<Decl>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken("}");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseDeclNamespace(ParserContext &ctx) {
// 	Token tokenClass = ctx.tryToken(Token::KWNamespace);
// 	if (!tokenClass.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSymbol = ctx.tryToken(Token::Symbol);
// 	if (!tokenSymbol.isGood()) {
// 		return ParserResult();
// 	}

// 	ParserResult res = ParserResult(new DeclNamespace(tokenSymbol.getRange(), tokenSymbol.getRange().getText()));

// 	Token tokenSep = ctx.expectToken(Token::LBrace, "{");
// 	if (!tokenSep.isGood()) {
// 		return ParserResult();
// 	}

// 	bool endedCorrectly = false;
// 	while (ctx.areMoreTokens()) {
// 		Token tokenSep = ctx.getToken();
// 		if (!tokenSep.isGood()) {
// 			ctx.emitMessageUnexpectedToken("declaration or }");
// 			return ParserResult();
// 		} else if (tokenSep.getID() == Token::RBrace) {
// 			ctx.eatToken();
// 			endedCorrectly = true;
// 			break;
// 		} else {
// 			ParserResult decl = ctx.expectParse(parseDecl, "declaration");
// 			if (!decl.isGood()) {
// 				return ParserResult();
// 			}
// 			res.getAST()->as<DeclNamespace>()->getMembers().push_back(decl.getAST()->cloneAs<Decl>());
// 		}
// 	}

// 	if (!endedCorrectly) {
// 		ctx.emitMessageUnexpectedToken("}");
// 		return ParserResult();
// 	}

// 	return res;
// }

// ParserResult Parser::parseDecl(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseDeclClass,
// 		parseDeclNamespace,
// 		parseDeclFunction,
// 		parseDeclVariable
// 	});
// }

// ParserResult Parser::parseImport(ParserContext &ctx) {
// 	Token tokenImport = ctx.tryToken(Token::KWImport);
// 	if (!tokenImport.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenLParen = ctx.tryToken(Token::LParen);
// 	if (!tokenLParen.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenPath = ctx.expectToken(Token::String, "path");
// 	if (!tokenPath.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenRParen = ctx.tryToken(Token::RParen);
// 	if (!tokenRParen.isGood()) {
// 		return ParserResult();
// 	}

// 	Token tokenSemicolon = ctx.tryToken(Token::Semicolon);
// 	if (!tokenSemicolon.isGood()) {
// 		return ParserResult();
// 	}

// 	std::string path;
// 	if (!evalLiteralString(tokenPath.getRange(), path)) {
// 		return ParserResult();
// 	}

// 	return ParserResult(new Import(tokenImport.getRange(), path));
// }

// ParserResult Parser::parseTopLevel(ParserContext &ctx) {
// 	return ctx.tryParseAny({
// 		parseImport,
// 		parseDecl
// 	});
// }

Parser::Parser(const std::vector<Token> &tokens, MessageBuffer &msgs, unsigned int offset) : ctx(tokens, msgs, offset) {}

std::vector<Container<AST>> Parser::parse() {
	std::vector<Container<AST>> rtn;

	while (ctx.areMoreTokens()) {
		ParserResult res = ctx.expectParse(parseTopLevel, "top-level statement");
		if (res.isGood()) {
			rtn.push_back(res.getAST()->clone());
		}
	}

	return rtn;
}
}
