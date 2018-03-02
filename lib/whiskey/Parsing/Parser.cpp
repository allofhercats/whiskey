#include <whiskey/Parsing/Parser.hpp>

#include <whiskey/Core/Literals.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldReal.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserContext.hpp>

namespace whiskey {
void Parser::createGrammar(ParserGrammar &grammar) {
	ParserRuleID type = grammar.addAny(
		"type",
		{}
	);

	ParserRuleID typeAtomicBool = grammar.addTerm(
		"'bool'",
		TokenID::Symbol,
		"bool",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicBool, token);
		}
	);

	ParserRuleID typeAtomicInt8 = grammar.addTerm(
		"'int8'",
		TokenID::Symbol,
		"int8",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt8, token);
		}
	);

	ParserRuleID typeAtomicInt16 = grammar.addTerm(
		"'int16'",
		TokenID::Symbol,
		"int16",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt16, token);
		}
	);

	ParserRuleID typeAtomicInt32 = grammar.addTerm(
		"'int32'",
		TokenID::Symbol,
		"int32",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt32, token);
		}
	);

	ParserRuleID typeAtomicInt64 = grammar.addTerm(
		"'int64'",
		TokenID::Symbol,
		"int64",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt64, token);
		}
	);

	ParserRuleID typeAtomicUInt8 = grammar.addTerm(
		"'uint8'",
		TokenID::Symbol,
		"uint8",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt8, token);
		}
	);

	ParserRuleID typeAtomicUInt16 = grammar.addTerm(
		"'uint16'",
		TokenID::Symbol,
		"uint16",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt16, token);
		}
	);

	ParserRuleID typeAtomicUInt32 = grammar.addTerm(
		"'uint32'",
		TokenID::Symbol,
		"uint32",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt32, token);
		}
	);

	ParserRuleID typeAtomicUInt64 = grammar.addTerm(
		"'uint64'",
		TokenID::Symbol,
		"uint64",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt64, token);
		}
	);

	ParserRuleID typeAtomicFloat32 = grammar.addTerm(
		"'float32'",
		TokenID::Symbol,
		"float32",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicFloat32, token);
		}
	);

	ParserRuleID typeAtomicFloat64 = grammar.addTerm(
		"'float64'",
		TokenID::Symbol,
		"float64",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicFloat64, token);
		}
	);

	ParserRuleID typeAtomicReal = grammar.addTerm(
		"'real'",
		TokenID::Symbol,
		"real",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicReal, token);
		}
	);

	ParserRuleID typeSymbolNoTemplateArgs = grammar.addTerm(
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeSymbol, token);
		}
	);

	ParserRuleID templateArgsEval = grammar.addList(
		"template args",
		grammar.addAny(
			"template arg",
			{
				type,
				// expr
			}
		),
		grammar.addTerm(
			"<",
			TokenID::LT,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
			",",
			TokenID::Comma,
			[](Token token, MessageContext &ctx) {
				return Node(token);
			}
		),
		grammar.addTerm(
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
			Node rtn(NodeType::ExprSymbol);
			rtn.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
			for (const Node &i : nodes) {
				rtn.getField(FieldTag::ExprSymbol_TemplateEvalArgs).as<FieldNodeVector>().getValue().push_back(i);
			}
			return rtn;
		}
	);

	ParserRuleID typeSymbol = grammar.addConcat(
		"type",
		{
			typeSymbolNoTemplateArgs,
			templateArgsEval
		},
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = nodes[1];
			rtn.setType(NodeType::TypeSymbol);
			rtn.setToken(nodes[0].getToken());
			return rtn;
		}
	);

	ParserRuleID typeTerm = grammar.addAny(
		"type",
		{
			typeAtomicBool,
			typeAtomicInt8,
			typeAtomicInt16,
			typeAtomicInt32,
			typeAtomicInt64,
			typeAtomicUInt8,
			typeAtomicUInt16,
			typeAtomicUInt32,
			typeAtomicUInt64,
			typeAtomicFloat32,
			typeAtomicFloat64,
			typeAtomicReal,
			typeSymbol
		}
	);

	ParserRuleID typeAccess = grammar.addBinary(
		"type access",
		typeTerm,
		typeTerm,
		{
			grammar.addTerm(
				".",
				TokenID::Period,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			Node rtn(NodeType::TypeAccess, token);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(lhs);
			rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(rhs);
			return rtn;
		}
	);

	ParserRuleID typeAccessUnary = grammar.addUnaryRight(
		"type access",
		typeAccess,
		{
			grammar.addTerm(
				".",
				TokenID::Period,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			Node rtn(NodeType::TypeAccessUnary);
			rtn.setField(FieldTag::TypeAccessUnary_Arg, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);

	ParserRuleID typeGroup = grammar.addConcat(
		"type group",
		{
			grammar.addTerm(
				"(",
				TokenID::LParen,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			type,
			grammar.addTerm(
				")",
				TokenID::RParen,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			return nodes[1];
		}
	);

	grammar.getRule(typeTerm).as<ParserRuleAny>().getChildren().push_back(typeGroup);

	ParserRuleID typeFunction = grammar.addConcat(
		"function type",
		{
			typeAccessUnary,
			grammar.addTerm(
				"<-",
				TokenID::LArrow,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addList(
				"function type args",
				type,
				grammar.addTerm(
					"(",
					TokenID::LParen,
					[](Token token, MessageContext &ctx) {
						return Node(token);
					}
				),
				grammar.addTerm(
					",",
					TokenID::Comma,
					[](Token token, MessageContext &ctx) {
						return Node(token);
					}
				),
				grammar.addTerm(
					")",
					TokenID::RParen,
					[](Token token, MessageContext &ctx) {
						return Node(token);
					}
				),
				[](const std::vector<Node> &nodes, MessageContext &ctx) {
					Node rtn(NodeType::TypeFunction);
					rtn.setField(FieldTag::TypeFunction_Args, std::make_unique<FieldNodeVector>());
					if (!nodes.empty()) {
						rtn.getField(FieldTag::TypeFunction_Args).as<FieldNodeVector>().getValue().insert(
							rtn.getField(FieldTag::TypeFunction_Args).as<FieldNodeVector>().getValue().end(),
							nodes.begin(),
							nodes.end()
						);
					}
					return rtn;
				}
			)
		},
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = nodes[2];
			rtn.setToken(nodes[1].getToken());
			rtn.setField(FieldTag::TypeFunction_Return, std::make_unique<FieldNode>(nodes[0]));
			return rtn;
		}
	);

	grammar.getRule(type).as<ParserRuleAny>().getChildren().push_back(typeFunction);
	grammar.getRule(type).as<ParserRuleAny>().getChildren().push_back(typeAccessUnary);

	ParserRuleID exprLiteralUInt = grammar.addAny(
		"int literal",
		{
			grammar.addTerm(
				"'true'",
				TokenID::Symbol,
				"true",
				[](Token token, MessageContext &ctx) {
					Node rtn(NodeType::ExprLiteralBool, token);
					rtn.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));
					return rtn;
				}
			),
			grammar.addTerm(
				"'false'",
				TokenID::Symbol,
				"false",
				[](Token token, MessageContext &ctx) {
					Node rtn(NodeType::ExprLiteralBool, token);
					rtn.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(0));
					return rtn;
				}
			),
			grammar.addTerm(
				"int literal",
				TokenID::Int,
				[](Token token, MessageContext &ctx) {
					Node rtn(NodeType::ExprLiteralUInt64, token);
					UInt64 tmp;
					if (evalLiteralUInt(token.getText(), tmp)) {
						rtn.setField(FieldTag::ExprLiteralUInt64_Value, std::make_unique<FieldUInt>(tmp));
						return rtn;
					} else {
						ctx.describe() << "invalid int format";
						ctx.emit(token, Message::Severity::Error);
						return Node();
					}
				}
			),
			grammar.addTerm(
				"char literal",
				TokenID::Char,
				[](Token token, MessageContext &ctx) {
					Node rtn(NodeType::ExprLiteralChar32, token);
					Char32 tmp;
					if (evalLiteralChar(token.getText(), tmp)) {
						rtn.setField(FieldTag::ExprLiteralChar32_Value, std::make_unique<FieldUInt>(tmp));
						return rtn;
					} else {
						ctx.describe() << "invalid char format";
						ctx.emit(token, Message::Severity::Error);
						return Node();
					}
				}
			)
		}
	);

	ParserRuleID exprLiteralReal = grammar.addTerm(
		"real literal",
		TokenID::Real,
		[](Token token, MessageContext &ctx) {
			Node rtn(NodeType::ExprLiteralReal, token);
			Real tmp;
			if (evalLiteralReal(token.getText(), tmp)) {
				rtn.setField(FieldTag::ExprLiteralReal_Value, std::make_unique<FieldReal>(tmp));
				return rtn;
			} else {
				ctx.describe() << "invalid real format";
				ctx.emit(token, Message::Severity::Error);
				return Node();
			}
		}
	);

	ParserRuleID exprSymbolNoTemplateArgs = grammar.addTerm(
		"expression",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::ExprSymbol, token);
		}
	);

	ParserRuleID exprSymbol = grammar.addConcat(
		"expression",
		{
			exprSymbolNoTemplateArgs,
			templateArgsEval
		},
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = nodes[1];
			rtn.setType(NodeType::ExprSymbol);
			rtn.setToken(nodes[0].getToken());
			return rtn;
		}
	);

	ParserRuleID exprTerm = grammar.addAny(
		"expression",
		{
			exprLiteralUInt,
			exprLiteralReal,
			exprSymbol
		}
	);

	ParserRuleID exprAccess = grammar.addBinary(
		"access",
		exprTerm,
		exprTerm,
		{
			grammar.addTerm(
				".",
				TokenID::Period,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			Node rtn(NodeType::ExprAccess, token);
			rtn.setField(FieldTag::ExprAccess_Args, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(lhs);
			rtn.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(rhs);
			return rtn;
		}
	);

	ParserRuleID exprAccessUnary = grammar.addUnaryRight(
		"access",
		exprAccess,
		{
			grammar.addTerm(
				".",
				TokenID::Period,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			Node rtn(NodeType::ExprAccessUnary);
			rtn.setField(FieldTag::ExprAccessUnary_Arg, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);

	ParserRuleID exprGroup = grammar.addConcat(
		"group",
		{
			grammar.addTerm(
				"(",
				TokenID::LParen,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			// expr,
			grammar.addTerm(
				")",
				TokenID::RParen,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			return nodes[1];
		}
	);

	grammar.getRule(exprTerm).as<ParserRuleAny>().getChildren().push_back(exprGroup);

	ParserRuleID exprCall = grammar.addConcat(
		"call",
		{
			typeAccessUnary,
			grammar.addList(
				"call args",
				exprAccessUnary, // expr,
				grammar.addTerm(
					"(",
					TokenID::LParen,
					[](Token token, MessageContext &ctx) {
						return Node(token);
					}
				),
				grammar.addTerm(
					",",
					TokenID::Comma,
					[](Token token, MessageContext &ctx) {
						return Node(token);
					}
				),
				grammar.addTerm(
					")",
					TokenID::RParen,
					[](Token token, MessageContext &ctx) {
						return Node(token);
					}
				),
				[](const std::vector<Node> &nodes, MessageContext &ctx) {
					Node rtn(NodeType::ExprCall);
					rtn.setField(FieldTag::ExprCall_Args, std::make_unique<FieldNodeVector>());
					if (!nodes.empty()) {
						rtn.getField(FieldTag::ExprCall_Args).as<FieldNodeVector>().getValue().insert(
							rtn.getField(FieldTag::ExprCall_Args).as<FieldNodeVector>().getValue().end(),
							nodes.begin(),
							nodes.end()
						);
					}
					return rtn;
				}
			)
		},
		[](const std::vector<Node> &nodes, MessageContext &ctx) {
			Node rtn = nodes[2];
			rtn.setToken(nodes[1].getToken());
			rtn.setField(FieldTag::ExprCall_Callee, std::make_unique<FieldNode>(nodes[0]));
			return rtn;
		}
	);

	ParserRuleID exprCallOptional = grammar.addAny(
		"expression",
		{
			exprCall,
			exprAccessUnary
		}
	);

	ParserRuleID exprUnaryRight = grammar.addUnaryRight(
		"expression",
		exprCallOptional,
		{
			grammar.addTerm(
				"expression",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"expression",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"expression",
				TokenID::Sub,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"expression",
				TokenID::BitNot,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn(NodeType::ExprIncPre, token);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn(NodeType::ExprDecPre, token);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Sub) {
				Node rtn(NodeType::ExprNeg, token);
				rtn.setField(FieldTag::ExprNeg_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitNot) {
				Node rtn(NodeType::ExprBitNot, token);
				rtn.setField(FieldTag::ExprBitNot_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unsupported operator token.");
			}
		}
	);

	ParserRuleID exprUnaryLeft = grammar.addUnaryLeft(
		"expression",
		exprUnaryRight,
		{
			grammar.addTerm(
				"expression",
				TokenID::Inc,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"expression",
				TokenID::Dec,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, MessageContext &ctx) {
			if (token.getID() == TokenID::Inc) {
				Node rtn(NodeType::ExprIncPost, token);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn(NodeType::ExprDecPost, token);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unsupported operator token.");
			}
		}
	);

	ParserRuleID exprExp = grammar.addBinary(
		"expression",
		exprUnaryLeft,
		exprUnaryLeft,
		{
			grammar.addTerm(
				"**",
				TokenID::Exp,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			Node rtn(NodeType::ExprExp, token);
			rtn.setField(FieldTag::ExprExp_LHS, std::make_unique<FieldNode>(lhs));
			rtn.setField(FieldTag::ExprExp_RHS, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);

	ParserRuleID exprMul = grammar.addBinary(
		"expression",
		exprExp,
		exprExp,
		{
			grammar.addTerm(
				"*",
				TokenID::Mul,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"/",
				TokenID::Div,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"//",
				TokenID::DivInt,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"/.",
				TokenID::DivReal,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			if (token.getID() == TokenID::Mul) {
				Node rtn = Node(NodeType::ExprMul, token);
				rtn.setField(FieldTag::ExprMul_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprMul_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprMul_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Div) {
				Node rtn = Node(NodeType::ExprDiv, token);
				rtn.setField(FieldTag::ExprDiv_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDiv_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::DivInt) {
				Node rtn = Node(NodeType::ExprDivInt, token);
				rtn.setField(FieldTag::ExprDivInt_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDivInt_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Real) {
				Node rtn = Node(NodeType::ExprDivReal, token);
				rtn.setField(FieldTag::ExprDivReal_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDivReal_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unsupported operator token.");
			}
		}
	);

	ParserRuleID exprAdd = grammar.addBinary(
		"expression",
		exprMul,
		exprMul,
		{
			grammar.addTerm(
				"+",
				TokenID::Add,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			),
			grammar.addTerm(
				"-",
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
				W_ASSERT_UNREACHABLE("Unsupported operator token.");
			}
		}
	);

	ParserRuleID exprMod = grammar.addBinary(
		"expression",
		exprAdd,
		exprAdd,
		{
			grammar.addTerm(
				"expression",
				TokenID::Mod,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			Node rtn = Node(NodeType::ExprMod, token);
			rtn.setField(FieldTag::ExprMod_LHS, std::make_unique<FieldNode>(lhs));
			rtn.setField(FieldTag::ExprMod_RHS, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);

	ParserRuleID exprBitShR = grammar.addBinary(
		"expression",
		exprMod,
		exprMod,
		{
			grammar.addTerm(
				"expression",
				TokenID::BitShR,
				[](Token token, MessageContext &ctx) {
					return Node(token);
				}
			)
		},
		[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
			Node rtn = Node(NodeType::ExprBitShR, token);
			rtn.setField(FieldTag::ExprBitShR_LHS, std::make_unique<FieldNode>(lhs));
			rtn.setField(FieldTag::ExprBitShR_RHS, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);
}

Parser::Parser() {}

bool Parser::isGrammarInitted() const {
	return grammar.getNRules() > 0;
}

void Parser::initGrammar() {
	grammar = ParserGrammar();
	createGrammar(grammar);
}

Node Parser::parse(ParserContext &ctx, MessageContext &msgs) const {
	Node rtn = grammar.getStartRule().parse(grammar, ctx, msgs).getNode();
	W_ASSERT_FALSE(ctx.more(), "Not all tokens parsed.");
	return rtn;
}
} // namespace whiskey
