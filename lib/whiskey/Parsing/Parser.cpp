#include <whiskey/Parsing/Parser.hpp>

#include <whiskey/Core/Literals.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/FieldUInt.hpp>
#include <whiskey/AST/FieldReal.hpp>
#include <whiskey/AST/FieldString.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/Parsing/ParserResult.hpp>
#include <whiskey/Parsing/ParserContext.hpp>

namespace whiskey {
Parser::Parser() {}

bool Parser::isGrammarInitted() const {
	return grammar.getNRules() > 0;
}

void Parser::initGrammar() {
	grammar = ParserGrammar();
	
	// ParserRuleID typeTerm = grammar.addForward();
	// ParserRuleID type = grammar.addForward();
	// ParserRuleID expr = grammar.addForward();
	// ParserRuleID exprList = grammar.addForward();
	// ParserRuleID stmt = grammar.addForward();
	// ParserRuleID declVariableNoSemicolon = grammar.addForward();
	// ParserRuleID declVariable = grammar.addForward();
	// ParserRuleID declVariableList = grammar.addForward();
	// ParserRuleID decl = grammar.addForward();	

	// ParserRuleID empty = grammar.addEmpty(
	// 	"Empty",
	// 	[](MessageContext &ctx) {
	// 		return Node();
	// 	}
	// );

	// ParserRuleID typeAtomicBool = grammar.addTerm(
	// 	"TypeAtomicBool",
	// 	"'bool'",
	// 	TokenID::Symbol,
	// 	"bool",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicBool, token);
	// 	}
	// );

	// ParserRuleID typeAtomicInt8 = grammar.addTerm(
	// 	"TypeAtomicInt8",
	// 	"'int8'",
	// 	TokenID::Symbol,
	// 	"int8",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicInt8, token);
	// 	}
	// );

	// ParserRuleID typeAtomicInt16 = grammar.addTerm(
	// 	"TypeAtomicInt16",
	// 	"'int16'",
	// 	TokenID::Symbol,
	// 	"int16",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicInt16, token);
	// 	}
	// );

	// ParserRuleID typeAtomicInt32 = grammar.addTerm(
	// 	"TypeAtomicInt32",
	// 	"'int32'",
	// 	TokenID::Symbol,
	// 	"int32",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicInt32, token);
	// 	}
	// );

	// ParserRuleID typeAtomicInt64 = grammar.addTerm(
	// 	"TypeAtomicInt64",
	// 	"'int64'",
	// 	TokenID::Symbol,
	// 	"int64",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicInt64, token);
	// 	}
	// );

	// ParserRuleID typeAtomicUInt8 = grammar.addTerm(
	// 	"TypeAtomicUInt8",
	// 	"'uint8'",
	// 	TokenID::Symbol,
	// 	"uint8",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicUInt8, token);
	// 	}
	// );

	// ParserRuleID typeAtomicUInt16 = grammar.addTerm(
	// 	"TypeAtomicUInt16",
	// 	"'uint16'",
	// 	TokenID::Symbol,
	// 	"uint16",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicUInt16, token);
	// 	}
	// );

	// ParserRuleID typeAtomicUInt32 = grammar.addTerm(
	// 	"TypeAtomicUInt32",
	// 	"'uint32'",
	// 	TokenID::Symbol,
	// 	"uint32",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicUInt32, token);
	// 	}
	// );

	// ParserRuleID typeAtomicUInt64 = grammar.addTerm(
	// 	"TypeAtomicUInt64",
	// 	"'uint64'",
	// 	TokenID::Symbol,
	// 	"uint64",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicUInt64, token);
	// 	}
	// );

	// ParserRuleID typeAtomicFloat32 = grammar.addTerm(
	// 	"TypeAtomicFloat32",
	// 	"'float32'",
	// 	TokenID::Symbol,
	// 	"float32",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicFloat32, token);
	// 	}
	// );

	// ParserRuleID typeAtomicFloat64 = grammar.addTerm(
	// 	"TypeAtomicFloat64",
	// 	"'float64'",
	// 	TokenID::Symbol,
	// 	"float64",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicFloat64, token);
	// 	}
	// );

	// ParserRuleID typeAtomicReal = grammar.addTerm(
	// 	"TypeAtomicReal",
	// 	"'real'",
	// 	TokenID::Symbol,
	// 	"real",
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeAtomicReal, token);
	// 	}
	// );

	// ParserRuleID typeSymbolNoTemplateArgs = grammar.addTerm(
	// 	"TypeSymbolNoTemplateArgs",
	// 	"type",
	// 	TokenID::Symbol,
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::TypeSymbol, token);
	// 	}
	// );

	// ParserRuleID templateArgsEval = grammar.addList(
	// 	"TemplateArgEvalList",
	// 	"template args",
	// 	grammar.addAny(
	// 		"TemplateArgEval",
	// 		"template arg",
	// 		{
	// 			typeAtomicInt8,
	// 			//expr
	// 		}
	// 	),
	// 	grammar.addTerm(
	// 		"<",
	// 		TokenID::LT,
	// 		[](Token token, MessageContext &ctx) {
	// 			return Node(token);
	// 		}
	// 	),
	// 	grammar.addTerm(
	// 		",",
	// 		TokenID::Comma,
	// 		[](Token token, MessageContext &ctx) {
	// 			return Node(token);
	// 		}
	// 	),
	// 	grammar.addTerm(
	// 		">",
	// 		TokenID::GT,
	// 		{
	// 			{TokenID::GE, TokenID::Assign},
	// 			{TokenID::BitShR, TokenID::GT},
	// 			{TokenID::BitShRAssign, TokenID::GE}
	// 		},
	// 		[](Token token, MessageContext &ctx) {
	// 			return Node(token);
	// 		}
	// 	),
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::List);
	// 		rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
	// 			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
	// 			nodes.begin(),
	// 			nodes.end()
	// 		);
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID typeSymbol = grammar.addConcat(
	// 	"TypeSymbol",
	// 	"type",
	// 	{
	// 		typeSymbolNoTemplateArgs,
	// 		grammar.addAny(
	// 			"TemplateArgsEvalOptional",
	// 			"type",
	// 			{
	// 				templateArgsEval,
	// 				grammar.addEmpty(
	// 					"Empty",
	// 					[](MessageContext &ctx) {
	// 						Node rtn(NodeType::List);
	// 						rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 						return rtn;
	// 					}
	// 				)
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::TypeSymbol, nodes[0].getToken());
	// 		rtn.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID typeAccess = grammar.addBinary(
	// 	"TypeAccess",
	// 	"type",
	// 	typeTerm,
	// 	typeTerm,
	// 	{
	// 		grammar.addTerm(
	// 			"Period",
	// 			".",
	// 			TokenID::Period,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn(NodeType::TypeAccess, token);
	// 		rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 		rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID typeAccessUnary = grammar.addUnaryRight(
	// 	"type",
	// 	typeAccess,
	// 	{
	// 		grammar.addTerm(
	// 			".",
	// 			TokenID::Period,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn(NodeType::TypeAccessUnary);
	// 		rtn.setField(FieldTag::TypeAccessUnary_Arg, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID typeGroup = grammar.addConcat(
	// 	"type",
	// 	{
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		type,
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		return nodes[1];
	// 	}
	// );

	// grammar.addAny(
	// 	typeTerm,
	// 	"type",
	// 	{
	// 		typeAtomicBool,
	// 		typeAtomicInt8,
	// 		typeAtomicInt16,
	// 		typeAtomicInt32,
	// 		typeAtomicInt64,
	// 		typeAtomicUInt8,
	// 		typeAtomicUInt16,
	// 		typeAtomicUInt32,
	// 		typeAtomicUInt64,
	// 		typeAtomicFloat32,
	// 		typeAtomicFloat64,
	// 		typeAtomicReal,
	// 		typeSymbol,
	// 		typeGroup
	// 	}
	// );

	// ParserRuleID typeFunction = grammar.addConcat(
	// 	"type",
	// 	{
	// 		typeAccessUnary,
	// 		grammar.addTerm(
	// 			"<-",
	// 			TokenID::LArrow,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addList(
	// 			"function type args",
	// 			type,
	// 			grammar.addTerm(
	// 				"(",
	// 				TokenID::LParen,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			grammar.addTerm(
	// 				",",
	// 				TokenID::Comma,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			grammar.addTerm(
	// 				")",
	// 				TokenID::RParen,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				Node rtn(NodeType::TypeFunction);
	// 				rtn.setField(FieldTag::TypeFunction_Args, std::make_unique<FieldNodeVector>());
	// 				if (!nodes.empty()) {
	// 					rtn.getField(FieldTag::TypeFunction_Args).as<FieldNodeVector>().getValue().insert(
	// 						rtn.getField(FieldTag::TypeFunction_Args).as<FieldNodeVector>().getValue().end(),
	// 						nodes.begin(),
	// 						nodes.end()
	// 					);
	// 				}
	// 				return rtn;
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn = nodes[2];
	// 		rtn.setToken(nodes[1].getToken());
	// 		rtn.setField(FieldTag::TypeFunction_Return, std::make_unique<FieldNode>(nodes[0]));
	// 		return rtn;
	// 	},
	// 	2
	// );

	// grammar.addAny(
	// 	type,
	// 	"type",
	// 	{
	// 		typeFunction,
	// 		typeAccessUnary
	// 	}
	// );

	// ParserRuleID typeListNonEmpty = grammar.addForward();

	// grammar.addAny(
	// 	typeListNonEmpty,
	// 	"type list",
	// 	{
	// 		grammar.addConcat(
	// 			"type list",
	// 			{
	// 				typeListNonEmpty,
	// 				grammar.addTerm(
	// 					",",
	// 					TokenID::Comma,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				expr
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				if (nodes[0].getType() == NodeType::List) {
	// 					Node rtn = nodes[0];
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[2]);
	// 					return rtn;
	// 				} else {
	// 					Node rtn(NodeType::List);
	// 					rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[0]);
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[2]);
	// 					return rtn;
	// 				}
	// 			}
	// 		),
	// 		type
	// 	}
	// );

	// ParserRuleID exprLiteralUInt = grammar.addAny(
	// 	"int literal",
	// 	{
	// 		grammar.addTerm(
	// 			"'true'",
	// 			TokenID::Symbol,
	// 			"true",
	// 			[](Token token, MessageContext &ctx) {
	// 				Node rtn(NodeType::ExprLiteralBool, token);
	// 				rtn.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));
	// 				return rtn;
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"'false'",
	// 			TokenID::Symbol,
	// 			"false",
	// 			[](Token token, MessageContext &ctx) {
	// 				Node rtn(NodeType::ExprLiteralBool, token);
	// 				rtn.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(0));
	// 				return rtn;
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"int literal",
	// 			TokenID::Int,
	// 			[](Token token, MessageContext &ctx) {
	// 				Node rtn(NodeType::ExprLiteralUInt64, token);
	// 				UInt64 tmp;
	// 				if (evalLiteralUInt(token.getText(), tmp)) {
	// 					rtn.setField(FieldTag::ExprLiteralUInt64_Value, std::make_unique<FieldUInt>(tmp));
	// 					return rtn;
	// 				} else {
	// 					ctx.describe() << "invalid int format";
	// 					ctx.emit(token, Message::Severity::Error);
	// 					return Node();
	// 				}
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"char literal",
	// 			TokenID::Char,
	// 			[](Token token, MessageContext &ctx) {
	// 				Node rtn(NodeType::ExprLiteralChar32, token);
	// 				Char32 tmp;
	// 				if (evalLiteralChar(token.getText(), tmp)) {
	// 					rtn.setField(FieldTag::ExprLiteralChar32_Value, std::make_unique<FieldUInt>(tmp));
	// 					return rtn;
	// 				} else {
	// 					ctx.describe() << "invalid char format";
	// 					ctx.emit(token, Message::Severity::Error);
	// 					return Node();
	// 				}
	// 			}
	// 		)
	// 	}
	// );

	// ParserRuleID exprLiteralReal = grammar.addTerm(
	// 	"real literal",
	// 	TokenID::Real,
	// 	[](Token token, MessageContext &ctx) {
	// 		Node rtn(NodeType::ExprLiteralReal, token);
	// 		Real tmp;
	// 		if (evalLiteralReal(token.getText(), tmp)) {
	// 			rtn.setField(FieldTag::ExprLiteralReal_Value, std::make_unique<FieldReal>(tmp));
	// 			return rtn;
	// 		} else {
	// 			ctx.describe() << "invalid real format";
	// 			ctx.emit(token, Message::Severity::Error);
	// 			return Node();
	// 		}
	// 	}
	// );

	// ParserRuleID exprSymbolNoTemplateArgs = grammar.addTerm(
	// 	"expression",
	// 	TokenID::Symbol,
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::ExprSymbol, token);
	// 	}
	// );

	// ParserRuleID exprSymbol = grammar.addConcat(
	// 	"expression",
	// 	{
	// 		exprSymbolNoTemplateArgs,
	// 		templateArgsEval
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::ExprSymbol, nodes[0].getToken());
	// 		rtn.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprTerm = grammar.addAny(
	// 	"expression",
	// 	{
	// 		exprLiteralUInt,
	// 		exprLiteralReal,
	// 		exprSymbol
	// 	}
	// );

	// ParserRuleID exprAccess = grammar.addBinary(
	// 	"expression",
	// 	exprTerm,
	// 	exprTerm,
	// 	{
	// 		grammar.addTerm(
	// 			".",
	// 			TokenID::Period,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn(NodeType::ExprAccess, token);
	// 		rtn.setField(FieldTag::ExprAccess_Args, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 		rtn.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprAccessUnary = grammar.addUnaryRight(
	// 	"expression",
	// 	exprAccess,
	// 	{
	// 		grammar.addTerm(
	// 			".",
	// 			TokenID::Period,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn(NodeType::ExprAccessUnary);
	// 		rtn.setField(FieldTag::ExprAccessUnary_Arg, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprGroup = grammar.addConcat(
	// 	"expression",
	// 	{
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		expr,
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		return nodes[1];
	// 	}
	// );

	// grammar.getRule(exprTerm).as<ParserRuleAny>().getChildren().push_back(exprGroup);

	// ParserRuleID exprCall = grammar.addConcat(
	// 	"expression",
	// 	{
	// 		typeAccessUnary,
	// 		grammar.addList(
	// 			"call args",
	// 			expr,
	// 			grammar.addTerm(
	// 				"(",
	// 				TokenID::LParen,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			grammar.addTerm(
	// 				",",
	// 				TokenID::Comma,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			grammar.addTerm(
	// 				")",
	// 				TokenID::RParen,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				Node rtn(NodeType::ExprCall);
	// 				rtn.setField(FieldTag::ExprCall_Args, std::make_unique<FieldNodeVector>());
	// 				if (!nodes.empty()) {
	// 					rtn.getField(FieldTag::ExprCall_Args).as<FieldNodeVector>().getValue().insert(
	// 						rtn.getField(FieldTag::ExprCall_Args).as<FieldNodeVector>().getValue().end(),
	// 						nodes.begin(),
	// 						nodes.end()
	// 					);
	// 				}
	// 				return rtn;
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn = nodes[2];
	// 		rtn.setToken(nodes[1].getToken());
	// 		rtn.setField(FieldTag::ExprCall_Callee, std::make_unique<FieldNode>(nodes[0]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprCallOptional = grammar.addAny(
	// 	"expression",
	// 	{
	// 		exprCall,
	// 		exprAccessUnary
	// 	}
	// );

	// ParserRuleID exprUnaryRight = grammar.addUnaryRight(
	// 	"expression",
	// 	exprCallOptional,
	// 	{
	// 		grammar.addTerm(
	// 			"++",
	// 			TokenID::Inc,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"--",
	// 			TokenID::Dec,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"-",
	// 			TokenID::Sub,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"~",
	// 			TokenID::BitNot,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Token token, Node rhs, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::Inc) {
	// 			Node rtn(NodeType::ExprIncPre, token);
	// 			rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::Dec) {
	// 			Node rtn(NodeType::ExprDecPre, token);
	// 			rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::Sub) {
	// 			Node rtn(NodeType::ExprNeg, token);
	// 			rtn.setField(FieldTag::ExprNeg_Arg, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitNot) {
	// 			Node rtn(NodeType::ExprBitNot, token);
	// 			rtn.setField(FieldTag::ExprBitNot_Arg, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprUnaryLeft = grammar.addUnaryLeft(
	// 	"expression",
	// 	exprUnaryRight,
	// 	{
	// 		grammar.addTerm(
	// 			"++",
	// 			TokenID::Inc,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"--",
	// 			TokenID::Dec,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::Inc) {
	// 			Node rtn(NodeType::ExprIncPost, token);
	// 			rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::Dec) {
	// 			Node rtn(NodeType::ExprDecPost, token);
	// 			rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprExp = grammar.addBinary(
	// 	"expression",
	// 	exprUnaryLeft,
	// 	exprUnaryLeft,
	// 	{
	// 		grammar.addTerm(
	// 			"**",
	// 			TokenID::Exp,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn(NodeType::ExprExp, token);
	// 		rtn.setField(FieldTag::ExprExp_LHS, std::make_unique<FieldNode>(lhs));
	// 		rtn.setField(FieldTag::ExprExp_RHS, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprMul = grammar.addBinary(
	// 	"expression",
	// 	exprExp,
	// 	exprExp,
	// 	{
	// 		grammar.addTerm(
	// 			"*",
	// 			TokenID::Mul,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"/",
	// 			TokenID::Div,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"//",
	// 			TokenID::DivInt,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"/.",
	// 			TokenID::DivReal,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::Mul) {
	// 			Node rtn = Node(NodeType::ExprMul, token);
	// 			rtn.setField(FieldTag::ExprMul_Args, std::make_unique<FieldNodeVector>());
	// 			rtn.getField(FieldTag::ExprMul_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 			rtn.getField(FieldTag::ExprMul_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::Div) {
	// 			Node rtn = Node(NodeType::ExprDiv, token);
	// 			rtn.setField(FieldTag::ExprDiv_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprDiv_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::DivInt) {
	// 			Node rtn = Node(NodeType::ExprDivInt, token);
	// 			rtn.setField(FieldTag::ExprDivInt_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprDivInt_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::Real) {
	// 			Node rtn = Node(NodeType::ExprDivReal, token);
	// 			rtn.setField(FieldTag::ExprDivReal_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprDivReal_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprAdd = grammar.addBinary(
	// 	"expression",
	// 	exprMul,
	// 	exprMul,
	// 	{
	// 		grammar.addTerm(
	// 			"+",
	// 			TokenID::Add,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"-",
	// 			TokenID::Sub,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::Add) {
	// 			Node rtn = Node(NodeType::ExprAdd, token);
	// 			rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
	// 			rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 			rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::Sub) {
	// 			Node rtn = Node(NodeType::ExprSub, token);
	// 			rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprMod = grammar.addBinary(
	// 	"expression",
	// 	exprAdd,
	// 	exprAdd,
	// 	{
	// 		grammar.addTerm(
	// 			"%",
	// 			TokenID::Mod,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprMod, token);
	// 		rtn.setField(FieldTag::ExprMod_LHS, std::make_unique<FieldNode>(lhs));
	// 		rtn.setField(FieldTag::ExprMod_RHS, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBitShR = grammar.addBinary(
	// 	"expression",
	// 	exprMod,
	// 	exprMod,
	// 	{
	// 		grammar.addTerm(
	// 			">>",
	// 			TokenID::BitShR,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprBitShR, token);
	// 		rtn.setField(FieldTag::ExprBitShR_LHS, std::make_unique<FieldNode>(lhs));
	// 		rtn.setField(FieldTag::ExprBitShR_RHS, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBitShL = grammar.addBinary(
	// 	"expression",
	// 	exprBitShR,
	// 	exprBitShR,
	// 	{
	// 		grammar.addTerm(
	// 			"<<",
	// 			TokenID::BitShL,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprBitShL, token);
	// 		rtn.setField(FieldTag::ExprBitShL_LHS, std::make_unique<FieldNode>(lhs));
	// 		rtn.setField(FieldTag::ExprBitShL_RHS, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBitAnd = grammar.addBinary(
	// 	"expression",
	// 	exprBitShL,
	// 	exprBitShL,
	// 	{
	// 		grammar.addTerm(
	// 			"&",
	// 			TokenID::BitAnd,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprBitAnd, token);
	// 		rtn.setField(FieldTag::ExprBitAnd_Args, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::ExprBitAnd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 		rtn.getField(FieldTag::ExprBitAnd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBitOr = grammar.addBinary(
	// 	"expression",
	// 	exprBitAnd,
	// 	exprBitAnd,
	// 	{
	// 		grammar.addTerm(
	// 			"|",
	// 			TokenID::BitOr,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"^",
	// 			TokenID::BitXor,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::BitOr) {
	// 			Node rtn = Node(NodeType::ExprBitOr, token);
	// 			rtn.setField(FieldTag::ExprBitOr_Args, std::make_unique<FieldNodeVector>());
	// 			rtn.getField(FieldTag::ExprBitOr_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 			rtn.getField(FieldTag::ExprBitOr_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitXor) {
	// 			Node rtn = Node(NodeType::ExprBitXor, token);
	// 			rtn.setField(FieldTag::ExprBitXor_Args, std::make_unique<FieldNodeVector>());
	// 			rtn.getField(FieldTag::ExprBitXor_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 			rtn.getField(FieldTag::ExprBitXor_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprCompare = grammar.addBinary(
	// 	"expression",
	// 	exprBitOr,
	// 	exprBitOr,
	// 	{
	// 		grammar.addTerm(
	// 			"<",
	// 			TokenID::LT,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"<=",
	// 			TokenID::LE,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			">",
	// 			TokenID::GT,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			">=",
	// 			TokenID::GE,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"!=",
	// 			TokenID::NE,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"==",
	// 			TokenID::EQ,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::LT) {
	// 			Node rtn = Node(NodeType::ExprLT, token);
	// 			rtn.setField(FieldTag::ExprLT_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprLT_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::LE) {
	// 			Node rtn = Node(NodeType::ExprLE, token);
	// 			rtn.setField(FieldTag::ExprLE_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprLE_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::GT) {
	// 			Node rtn = Node(NodeType::ExprGT, token);
	// 			rtn.setField(FieldTag::ExprGT_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprGT_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::GE) {
	// 			Node rtn = Node(NodeType::ExprGE, token);
	// 			rtn.setField(FieldTag::ExprGE_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprGE_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::NE) {
	// 			Node rtn = Node(NodeType::ExprNE, token);
	// 			rtn.setField(FieldTag::ExprNE_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprNE_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::EQ) {
	// 			Node rtn = Node(NodeType::ExprEQ, token);
	// 			rtn.setField(FieldTag::ExprEQ_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprEQ_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprBoolNot = grammar.addUnaryRight(
	// 	"expression",
	// 	exprCompare,
	// 	{
	// 		grammar.addTerm(
	// 			"'not'",
	// 			TokenID::Symbol,
	// 			"not",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn(NodeType::ExprBoolNot);
	// 		rtn.setField(FieldTag::ExprBoolNot_Arg, std::make_unique<FieldNode>(rhs));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBoolAnd = grammar.addBinary(
	// 	"expression",
	// 	exprBoolNot,
	// 	exprBoolNot,
	// 	{
	// 		grammar.addTerm(
	// 			"'and'",
	// 			TokenID::Symbol,
	// 			"and",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprBoolAnd, token);
	// 		rtn.setField(FieldTag::ExprBoolAnd_Args, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 		rtn.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBoolOr = grammar.addBinary(
	// 	"expression",
	// 	exprBoolAnd,
	// 	exprBoolAnd,
	// 	{
	// 		grammar.addTerm(
	// 			"'or'",
	// 			TokenID::Symbol,
	// 			"or",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprBoolOr, token);
	// 		rtn.setField(FieldTag::ExprBoolOr_Args, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::ExprBoolOr_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 		rtn.getField(FieldTag::ExprBoolOr_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID exprBoolImplies = grammar.addBinary(
	// 	"expression",
	// 	exprBoolOr,
	// 	exprBoolOr,
	// 	{
	// 		grammar.addTerm(
	// 			"=>",
	// 			TokenID::BoolImplies,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		Node rtn = Node(NodeType::ExprBoolImplies, token);
	// 		rtn.setField(FieldTag::ExprBoolImplies_Args, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::ExprBoolImplies_Args).as<FieldNodeVector>().getValue().push_back(lhs);
	// 		rtn.getField(FieldTag::ExprBoolImplies_Args).as<FieldNodeVector>().getValue().push_back(rhs);
	// 		return rtn;
	// 	}
	// );

	// grammar.addBinary(
	// 	expr,
	// 	"expression",
	// 	exprBoolImplies,
	// 	exprBoolImplies,
	// 	{
	// 		grammar.addTerm(
	// 			"=",
	// 			TokenID::Assign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"+=",
	// 			TokenID::AddAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"-=",
	// 			TokenID::SubAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"*=",
	// 			TokenID::MulAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"**=",
	// 			TokenID::ExpAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"/=",
	// 			TokenID::DivAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"//=",
	// 			TokenID::DivIntAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"/.=",
	// 			TokenID::DivRealAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"%",
	// 			TokenID::ModAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"&=",
	// 			TokenID::BitAndAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"|=",
	// 			TokenID::BitOrAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"^=",
	// 			TokenID::BitXorAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"<<=",
	// 			TokenID::BitShLAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			">>=",
	// 			TokenID::BitShRAssign,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](Node lhs, Token token, Node rhs, MessageContext &ctx) {
	// 		if (token.getID() == TokenID::Assign) {
	// 			Node rtn = Node(NodeType::ExprAssign, token);
	// 			rtn.setField(FieldTag::ExprAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::AddAssign) {
	// 			Node rtn = Node(NodeType::ExprAddAssign, token);
	// 			rtn.setField(FieldTag::ExprAddAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprAddAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::SubAssign) {
	// 			Node rtn = Node(NodeType::ExprSubAssign, token);
	// 			rtn.setField(FieldTag::ExprSubAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprSubAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::MulAssign) {
	// 			Node rtn = Node(NodeType::ExprMulAssign, token);
	// 			rtn.setField(FieldTag::ExprMulAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprMulAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::ExpAssign) {
	// 			Node rtn = Node(NodeType::ExprExpAssign, token);
	// 			rtn.setField(FieldTag::ExprExpAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprExpAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::DivAssign) {
	// 			Node rtn = Node(NodeType::ExprDivAssign, token);
	// 			rtn.setField(FieldTag::ExprDivAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprDivAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::DivIntAssign) {
	// 			Node rtn = Node(NodeType::ExprDivIntAssign, token);
	// 			rtn.setField(FieldTag::ExprDivIntAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprDivIntAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::DivRealAssign) {
	// 			Node rtn = Node(NodeType::ExprDivRealAssign, token);
	// 			rtn.setField(FieldTag::ExprDivRealAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprDivRealAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::ModAssign) {
	// 			Node rtn = Node(NodeType::ExprModAssign, token);
	// 			rtn.setField(FieldTag::ExprModAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprModAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitAndAssign) {
	// 			Node rtn = Node(NodeType::ExprBitAndAssign, token);
	// 			rtn.setField(FieldTag::ExprBitAndAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprBitAndAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitOrAssign) {
	// 			Node rtn = Node(NodeType::ExprBitOrAssign, token);
	// 			rtn.setField(FieldTag::ExprBitOrAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprBitOrAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitXorAssign) {
	// 			Node rtn = Node(NodeType::ExprBitXorAssign, token);
	// 			rtn.setField(FieldTag::ExprBitXorAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprBitXorAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitShLAssign) {
	// 			Node rtn = Node(NodeType::ExprBitShLAssign, token);
	// 			rtn.setField(FieldTag::ExprBitShLAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprBitShLAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else if (token.getID() == TokenID::BitShRAssign) {
	// 			Node rtn = Node(NodeType::ExprBitShRAssign, token);
	// 			rtn.setField(FieldTag::ExprBitShRAssign_LHS, std::make_unique<FieldNode>(lhs));
	// 			rtn.setField(FieldTag::ExprBitShRAssign_RHS, std::make_unique<FieldNode>(rhs));
	// 			return rtn;
	// 		} else {
	// 			W_ASSERT_UNREACHABLE("Unsupported operator token.");
	// 		}
	// 	}
	// );

	// ParserRuleID exprListNonEmpty = grammar.addForward();

	// grammar.addAny(
	// 	exprListNonEmpty,
	// 	"expression list",
	// 	{
	// 		grammar.addConcat(
	// 			"expression list",
	// 			{
	// 				exprListNonEmpty,
	// 				grammar.addTerm(
	// 					",",
	// 					TokenID::Comma,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				expr
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				if (nodes[0].getType() == NodeType::List) {
	// 					Node rtn = nodes[0];
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[2]);
	// 					return rtn;
	// 				} else {
	// 					Node rtn(NodeType::List);
	// 					rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[0]);
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[2]);
	// 					return rtn;
	// 				}
	// 			}
	// 		),
	// 		expr
	// 	}
	// );

	// grammar.addAny(
	// 	exprList,
	// 	"expression list",
	// 	{
	// 		exprListNonEmpty,
	// 		grammar.addEmpty(
	// 			"empty",
	// 			[](MessageContext &ctx) {
	// 				Node rtn(NodeType::List);
	// 				rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 				return rtn;
	// 			}
	// 		)
	// 	}
	// );

	// ParserRuleID stmtEmpty = grammar.addTerm(
	// 	"statement",
	// 	TokenID::Semicolon,
	// 	[](Token token, MessageContext &ctx) {
	// 		return Node(NodeType::StmtEmpty, token);
	// 	}
	// );

	// ParserRuleID stmtExpr = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		expr,
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtExpr, nodes[1].getToken());
	// 		rtn.setField(FieldTag::StmtExpr_Expr, std::make_unique<FieldNode>(nodes[0]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtDecl = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		decl,
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtDecl, nodes[1].getToken());
	// 		rtn.setField(FieldTag::StmtDecl_Decl, std::make_unique<FieldNode>(nodes[0]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtReturn = grammar.addAny(
	// 	"statement",
	// 	{
	// 		grammar.addConcat(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"'return'",
	// 					TokenID::Symbol,
	// 					"return",
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				grammar.addTerm(
	// 					";",
	// 					TokenID::Semicolon,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				)
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				return Node(NodeType::StmtReturn, nodes[0].getToken());
	// 			}
	// 		),
	// 		grammar.addConcat(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"'return'",
	// 					TokenID::Symbol,
	// 					"return",
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				expr,
	// 				grammar.addTerm(
	// 					";",
	// 					TokenID::Semicolon,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				)
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				Node rtn(NodeType::StmtReturn, nodes[0].getToken());
	// 				rtn.setField(FieldTag::StmtReturn_Arg, std::make_unique<FieldNode>(nodes[1]));
	// 				return rtn;
	// 			}
	// 		)
	// 	}
	// );

	// ParserRuleID stmtContinue = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		grammar.addTerm(
	// 			"'continue'",
	// 			TokenID::Symbol,
	// 			"continue",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"loop symbol",
	// 					TokenID::Symbol,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				empty
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtContinue, nodes[0].getToken());
	// 		if (nodes[1].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::StmtContinue_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
	// 		}
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtBreak = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		grammar.addTerm(
	// 			"'break'",
	// 			TokenID::Symbol,
	// 			"break",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"loop symbol",
	// 					TokenID::Symbol,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				empty
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtBreak, nodes[0].getToken());
	// 		if (nodes[1].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::StmtBreak_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
	// 		}
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtElse = grammar.addAny(
	// 	"statement",
	// 	{
	// 		grammar.addConcat(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"'else'",
	// 					TokenID::Symbol,
	// 					"else",
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				stmt
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				return nodes[1];
	// 			}
	// 		),
	// 		empty
	// 	}
	// );

	// ParserRuleID stmtIf = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		grammar.addTerm(
	// 			"'if'",
	// 			TokenID::Symbol,
	// 			"if",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		expr,
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		stmt,
	// 		stmtElse
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtIf, nodes[0].getToken());
	// 		rtn.setField(FieldTag::StmtIf_Condition, std::make_unique<FieldNode>(nodes[2]));
	// 		rtn.setField(FieldTag::StmtIf_Then, std::make_unique<FieldNode>(nodes[4]));
	// 		if (nodes[5].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::StmtIf_Else, std::make_unique<FieldNode>(nodes[5]));
	// 		}
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtWhile = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		grammar.addTerm(
	// 			"'while'",
	// 			TokenID::Symbol,
	// 			"while",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"loop symbol",
	// 					TokenID::Symbol,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				empty
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		expr,
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		stmt
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtWhile, nodes[0].getToken());
	// 		if (nodes[1].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::StmtWhile_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
	// 		}
	// 		rtn.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(nodes[3]));
	// 		rtn.setField(FieldTag::StmtWhile_Body, std::make_unique<FieldNode>(nodes[5]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtFor = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		grammar.addTerm(
	// 			"'for'",
	// 			TokenID::Symbol,
	// 			"for",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"loop symbol",
	// 					TokenID::Symbol,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				empty
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		declVariableList,
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		expr,
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		exprList,
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		stmt
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtFor, nodes[0].getToken());
	// 		if (nodes[1].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::StmtFor_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
	// 		}
	// 		rtn.setField(FieldTag::StmtFor_Decls, std::make_unique<FieldNodeVector>(nodes[3].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		rtn.setField(FieldTag::StmtFor_Condition, std::make_unique<FieldNode>(nodes[5]));
	// 		rtn.setField(FieldTag::StmtFor_Steps, std::make_unique<FieldNodeVector>(nodes[7].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		rtn.setField(FieldTag::StmtFor_Body, std::make_unique<FieldNode>(nodes[9]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtForEach = grammar.addConcat(
	// 	"statement",
	// 	{
	// 		grammar.addTerm(
	// 			"'for'",
	// 			TokenID::Symbol,
	// 			"for",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"statement",
	// 			{
	// 				grammar.addTerm(
	// 					"loop symbol",
	// 					TokenID::Symbol,
	// 					[](Token token, MessageContext &ctx) {
	// 						return Node(token);
	// 					}
	// 				),
	// 				empty
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		declVariable,
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		expr,
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		stmt
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtForEach, nodes[0].getToken());
	// 		if (nodes[1].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::StmtForEach_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
	// 		}
	// 		rtn.setField(FieldTag::StmtForEach_Decl, std::make_unique<FieldNode>(nodes[3]));
	// 		rtn.setField(FieldTag::StmtForEach_Sequence, std::make_unique<FieldNode>(nodes[5]));
	// 		rtn.setField(FieldTag::StmtForEach_Body, std::make_unique<FieldNode>(nodes[7]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID stmtListNonEmpty = grammar.addForward();

	// grammar.addAny(
	// 	stmtListNonEmpty,
	// 	"statement list",
	// 	{
	// 		grammar.addConcat(
	// 			"statement list",
	// 			{
	// 				stmtListNonEmpty,
	// 				stmt
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				if (nodes[0].getType() == NodeType::List) {
	// 					Node rtn = nodes[0];
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				} else {
	// 					Node rtn(NodeType::List);
	// 					rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[0]);
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				}
	// 			}
	// 		),
	// 		stmt
	// 	}
	// );

	// ParserRuleID stmtList = grammar.addAny(
	// 	"statement list",
	// 	{
	// 		stmtListNonEmpty,
	// 		grammar.addEmpty(
	// 			"empty",
	// 			[](MessageContext &ctx) {
	// 				Node rtn(NodeType::List);
	// 				rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 				return rtn;
	// 			}
	// 		)
	// 	}
	// );

	// ParserRuleID stmtBlock = grammar.addConcat(
	// 	"statement block",
	// 	{
	// 		grammar.addTerm(
	// 			"{",
	// 			TokenID::LBrace,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		stmtList,
	// 		grammar.addTerm(
	// 			"}",
	// 			TokenID::RBrace,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::StmtBlock, nodes[0].getToken());
	// 		rtn.setField(FieldTag::StmtBlock_Stmts, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		return rtn;
	// 	}
	// );

	// grammar.addAny(
	// 	stmt,
	// 	"statement",
	// 	{
	// 		stmtEmpty,
	// 		stmtBlock,
	// 		stmtReturn,
	// 		stmtBreak,
	// 		stmtContinue,
	// 		stmtIf,
	// 		stmtWhile,
	// 		stmtForEach,
	// 		stmtFor,
	// 		stmtDecl,
	// 		stmtExpr
	// 	}
	// );

	// ParserRuleID templateArgsDecl = grammar.addList(
	// 	"template args",
	// 	declVariableNoSemicolon,
	// 	grammar.addTerm(
	// 		"<",
	// 		TokenID::LT,
	// 		[](Token token, MessageContext &ctx) {
	// 			return Node(token);
	// 		}
	// 	),
	// 	grammar.addTerm(
	// 		",",
	// 		TokenID::Comma,
	// 		[](Token token, MessageContext &ctx) {
	// 			return Node(token);
	// 		}
	// 	),
	// 	grammar.addTerm(
	// 		">",
	// 		TokenID::GT,
	// 		{
	// 			{TokenID::GE, TokenID::Assign},
	// 			{TokenID::BitShR, TokenID::GT},
	// 			{TokenID::BitShRAssign, TokenID::GE}
	// 		},
	// 		[](Token token, MessageContext &ctx) {
	// 			return Node(token);
	// 		}
	// 	),
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::List);
	// 		rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 		rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
	// 			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
	// 			nodes.begin(),
	// 			nodes.end()
	// 		);
	// 		return rtn;
	// 	}
	// );

	// grammar.addConcat(
	// 	declVariableNoSemicolon,
	// 	"declaration",
	// 	{
	// 		type,
	// 		grammar.addTerm(
	// 			"symbol",
	// 			TokenID::Symbol,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"declaration",
	// 			{
	// 				templateArgsDecl,
	// 				grammar.addEmpty(
	// 					"empty",
	// 					[](MessageContext &ctx) {
	// 						Node rtn(NodeType::List);
	// 						rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 						return rtn;
	// 					}
	// 				)
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"declaration",
	// 			{
	// 				grammar.addConcat(
	// 					"declaration",
	// 					{
	// 						grammar.addTerm(
	// 							"=",
	// 							TokenID::Assign,
	// 							[](Token token, MessageContext &ctx) {
	// 								return Node(token);
	// 							}
	// 						),
	// 						expr
	// 					},
	// 					[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 						return nodes[1];
	// 					}
	// 				),
	// 				grammar.addEmpty(
	// 					"empty",
	// 					[](MessageContext &ctx) {
	// 						return Node();
	// 					}
	// 				)
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::DeclVariable, nodes[1].getToken());
	// 		rtn.setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(nodes[0]));
	// 		rtn.setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		if (nodes[3].getType() != NodeType::None) {
	// 			rtn.setField(FieldTag::DeclVariable_Initial, std::make_unique<FieldNode>(nodes[3]));
	// 		}
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID declVariableListNonEmpty = grammar.addForward();

	// grammar.addAny(
	// 	declVariableListNonEmpty,
	// 	"variable declaration list",
	// 	{
	// 		grammar.addConcat(
	// 			"variable declaration list",
	// 			{
	// 				declVariableListNonEmpty,
	// 				declVariableNoSemicolon
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				if (nodes[0].getType() == NodeType::List) {
	// 					Node rtn = nodes[0];
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				} else {
	// 					Node rtn(NodeType::List);
	// 					rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[0]);
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				}
	// 			}
	// 		),
	// 		declVariableNoSemicolon
	// 	}
	// );

	// grammar.addAny(
	// 	declVariableList,
	// 	"variable declaration list",
	// 	{
	// 		declVariableListNonEmpty,
	// 		grammar.addEmpty(
	// 			"empty",
	// 			[](MessageContext &ctx) {
	// 				Node rtn(NodeType::List);
	// 				rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 				return rtn;
	// 			}
	// 		)
	// 	}
	// );

	// grammar.addConcat(
	// 	declVariable,
	// 	"declaration",
	// 	{
	// 		declVariableNoSemicolon,
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		return nodes[0];
	// 	}
	// );

	// ParserRuleID declFunction = grammar.addConcat(
	// 	"declaration",
	// 	{
	// 		type,
	// 		grammar.addTerm(
	// 			"symbol",
	// 			TokenID::Symbol,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"declaration",
	// 			{
	// 				templateArgsDecl,
	// 				grammar.addEmpty(
	// 					"empty",
	// 					[](MessageContext &ctx) {
	// 						Node rtn(NodeType::List);
	// 						rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 						return rtn;
	// 					}
	// 				)
	// 			}
	// 		),
	// 		grammar.addList(
	// 			"args",
	// 			declVariableNoSemicolon,
	// 			grammar.addTerm(
	// 				"(",
	// 				TokenID::LParen,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			grammar.addTerm(
	// 				",",
	// 				TokenID::Comma,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			grammar.addTerm(
	// 				")",
	// 				TokenID::RParen,
	// 				[](Token token, MessageContext &ctx) {
	// 					return Node(token);
	// 				}
	// 			),
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				Node rtn(NodeType::List);
	// 				rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().end(),
	// 					nodes.begin(),
	// 					nodes.end()
	// 				);
	// 				return rtn;
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"function body",
	// 			{
	// 				grammar.addConcat(
	// 					"function body",
	// 					{
	// 						grammar.addTerm(
	// 							"=",
	// 							TokenID::Assign,
	// 							[](Token token, MessageContext &ctx) {
	// 								return Node(token);
	// 							}
	// 						),
	// 						expr,
	// 						grammar.addTerm(
	// 							";",
	// 							TokenID::Semicolon,
	// 							[](Token token, MessageContext &ctx) {
	// 								return Node(token);
	// 							}
	// 						)
	// 					},
	// 					[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 						return nodes[1];
	// 					}
	// 				),
	// 				stmtBlock
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::DeclFunction, nodes[1].getToken());
	// 		rtn.setField(FieldTag::DeclFunction_Return, std::make_unique<FieldNode>(nodes[0]));
	// 		rtn.setField(FieldTag::DeclFunction_TemplateDeclArgs, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		rtn.setField(FieldTag::DeclFunction_Args, std::make_unique<FieldNodeVector>(nodes[3].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		rtn.setField(FieldTag::DeclFunction_Body, std::make_unique<FieldNode>(nodes[4]));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID declListNonEmpty = grammar.addForward();

	// grammar.addAny(
	// 	declListNonEmpty,
	// 	"declaration list",
	// 	{
	// 		grammar.addConcat(
	// 			"declaration list",
	// 			{
	// 				declListNonEmpty,
	// 				decl
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				if (nodes[0].getType() == NodeType::List) {
	// 					Node rtn = nodes[0];
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				} else {
	// 					Node rtn(NodeType::List);
	// 					rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[0]);
	// 					rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				}
	// 			}
	// 		),
	// 		decl
	// 	}
	// );

	// ParserRuleID declList = grammar.addAny(
	// 	"declaration list",
	// 	{
	// 		declListNonEmpty,
	// 		grammar.addEmpty(
	// 			"empty",
	// 			[](MessageContext &ctx) {
	// 				Node rtn(NodeType::List);
	// 				rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 				return rtn;
	// 			}
	// 		)
	// 	}
	// );

	// ParserRuleID declClass = grammar.addConcat(
	// 	"declaration",
	// 	{
	// 		grammar.addTerm(
	// 			"'class'",
	// 			TokenID::Symbol,
	// 			"class",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"symbol",
	// 			TokenID::Symbol,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"declaration",
	// 			{
	// 				templateArgsDecl,
	// 				grammar.addEmpty(
	// 					"empty",
	// 					[](MessageContext &ctx) {
	// 						Node rtn(NodeType::List);
	// 						rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
	// 						return rtn;
	// 					}
	// 				)
	// 			}
	// 		),
	// 		grammar.addAny(
	// 			"declaration",
	// 			{
	// 				grammar.addConcat(
	// 					"declaration",
	// 					{
	// 						grammar.addTerm(
	// 							"'inherits'",
	// 							TokenID::Symbol,
	// 							"inherits",
	// 							[](Token token, MessageContext &ctx) {
	// 								return Node(token);
	// 							}
	// 						),
	// 						typeListNonEmpty
	// 					},
	// 					[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 						return nodes[1];
	// 					}
	// 				)
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"{",
	// 			TokenID::LBrace,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		declList,
	// 		grammar.addTerm(
	// 			"}",
	// 			TokenID::RBrace,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::DeclClass, nodes[1].getToken());
	// 		rtn.setField(FieldTag::DeclClass_TemplateDeclArgs, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		rtn.setField(FieldTag::DeclClass_Inherits, std::make_unique<FieldNodeVector>(nodes[3].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		rtn.setField(FieldTag::DeclClass_Members, std::make_unique<FieldNodeVector>(nodes[5].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		return rtn;
	// 	}
	// );

	// ParserRuleID declNamespace = grammar.addConcat(
	// 	"declaration",
	// 	{
	// 		grammar.addTerm(
	// 			"'namespace'",
	// 			TokenID::Symbol,
	// 			"namespace",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"symbol",
	// 			TokenID::Symbol,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"{",
	// 			TokenID::LBrace,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		declList,
	// 		grammar.addTerm(
	// 			"}",
	// 			TokenID::RBrace,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::DeclNamespace, nodes[1].getToken());
	// 		rtn.setField(FieldTag::DeclNamespace_Members, std::make_unique<FieldNodeVector>(nodes[3].getField(FieldTag::List_Children).as<FieldNodeVector>()));
	// 		return rtn;
	// 	}
	// );

	// grammar.addAny(
	// 	decl,
	// 	"declaration",
	// 	{
	// 		declClass,
	// 		declNamespace,
	// 		declFunction,
	// 		declVariable
	// 	}
	// );

	// ParserRuleID import = grammar.addConcat(
	// 	"import",
	// 	{
	// 		grammar.addTerm(
	// 			"'import'",
	// 			TokenID::Symbol,
	// 			"import",
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"(",
	// 			TokenID::LParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			"path",
	// 			TokenID::String,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			")",
	// 			TokenID::RParen,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		),
	// 		grammar.addTerm(
	// 			";",
	// 			TokenID::Semicolon,
	// 			[](Token token, MessageContext &ctx) {
	// 				return Node(token);
	// 			}
	// 		)
	// 	},
	// 	[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 		Node rtn(NodeType::Import, nodes[0].getToken());
	// 		std::string tmp;
	// 		if (evalLiteralString(nodes[2].getToken().getText(), tmp)) {
	// 			rtn.setField(FieldTag::Import_Path, std::make_unique<FieldString>(tmp));
	// 			return rtn;
	// 		} else {
	// 			ctx.describe() << "invalid string format";
	// 			ctx.emit(nodes[2].getToken(), Message::Severity::Error);
	// 			return Node();
	// 		}
	// 	}
	// );

	// ParserRuleID unitMember = grammar.addAny(
	// 	"top-level statement",
	// 	{
	// 		import,
	// 		decl
	// 	}
	// );

	// ParserRuleID unitMemberListNonEmpty = grammar.addForward();

	// grammar.addAny(
	// 	unitMemberListNonEmpty,
	// 	"top-level statement",
	// 	{
	// 		grammar.addConcat(
	// 			"top-level statement",
	// 			{
	// 				unitMemberListNonEmpty,
	// 				unitMember
	// 			},
	// 			[](const std::vector<Node> &nodes, MessageContext &ctx) {
	// 				if (nodes[0].getType() == NodeType::Unit) {
	// 					Node rtn = nodes[0];
	// 					rtn.getField(FieldTag::Unit_Members).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				} else {
	// 					Node rtn(NodeType::Unit);
	// 					rtn.setField(FieldTag::Unit_Members, std::make_unique<FieldNodeVector>());
	// 					rtn.getField(FieldTag::Unit_Members).as<FieldNodeVector>().getValue().push_back(nodes[0]);
	// 					rtn.getField(FieldTag::Unit_Members).as<FieldNodeVector>().getValue().push_back(nodes[1]);
	// 					return rtn;
	// 				}
	// 			}
	// 		),
	// 		unitMember
	// 	}
	// );

	// ParserRuleID unit = grammar.addAny(
	// 	"top-level statement",
	// 	{
	// 		unitMemberListNonEmpty,
	// 		grammar.addEmpty(
	// 			"empty",
	// 			[](MessageContext &ctx) {
	// 				Node rtn(NodeType::Unit);
	// 				rtn.setField(FieldTag::Unit_Members, std::make_unique<FieldNodeVector>());
	// 				return rtn;
	// 			}
	// 		)
	// 	}
	// );

	// ruleType = type;
	// ruleExpr = expr;
	// ruleStmt = stmt;
	// ruleDecl = decl;

	// grammar.setStartID(unit);

	ParserRuleID typeAtomicBool = grammar.addTerm(
		"TypeAtomicBool",
		"'bool'",
		TokenID::Symbol,
		"bool",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicBool, token);
		}
	);

	ParserRuleID typeAtomicInt8 = grammar.addTerm(
		"TypeAtomicInt8",
		"'int8'",
		TokenID::Symbol,
		"int8",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt8, token);
		}
	);

	ParserRuleID typeAtomicInt16 = grammar.addTerm(
		"TypeAtomicInt16",
		"'int16'",
		TokenID::Symbol,
		"int16",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt16, token);
		}
	);

	ParserRuleID typeAtomicInt32 = grammar.addTerm(
		"TypeAtomicInt32",
		"'int32'",
		TokenID::Symbol,
		"int32",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt32, token);
		}
	);

	ParserRuleID typeAtomicInt64 = grammar.addTerm(
		"TypeAtomicInt64",
		"'int64'",
		TokenID::Symbol,
		"int64",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicInt64, token);
		}
	);

	ParserRuleID typeAtomicUInt8 = grammar.addTerm(
		"TypeAtomicUInt8",
		"'uint8'",
		TokenID::Symbol,
		"uint8",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt8, token);
		}
	);

	ParserRuleID typeAtomicUInt16 = grammar.addTerm(
		"TypeAtomicUInt16",
		"'uint16'",
		TokenID::Symbol,
		"uint16",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt16, token);
		}
	);

	ParserRuleID typeAtomicUInt32 = grammar.addTerm(
		"TypeAtomicUInt32",
		"'uint32'",
		TokenID::Symbol,
		"uint32",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt32, token);
		}
	);

	ParserRuleID typeAtomicUInt64 = grammar.addTerm(
		"TypeAtomicUInt64",
		"'uint64'",
		TokenID::Symbol,
		"uint64",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicUInt64, token);
		}
	);

	ParserRuleID typeAtomicFloat32 = grammar.addTerm(
		"TypeAtomicFloat32",
		"'float32'",
		TokenID::Symbol,
		"float32",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicFloat32, token);
		}
	);

	ParserRuleID typeAtomicFloat64 = grammar.addTerm(
		"TypeAtomicFloat64",
		"'float64'",
		TokenID::Symbol,
		"float64",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicFloat64, token);
		}
	);

	ParserRuleID typeAtomicReal = grammar.addTerm(
		"TypeAtomicReal",
		"'real'",
		TokenID::Symbol,
		"real",
		[](Token token, MessageContext &ctx) {
			return Node(NodeType::TypeAtomicReal, token);
		}
	);

	ParserRuleID typeSymbolNonTemplate = grammar.addTerm(
		"TypeSymbolNonTemplate",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &ctx) {
			Node rtn(NodeType::TypeSymbol, token);
			rtn.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID templateArgsEval = grammar.addList(
		
	);

	ParserRuleID typeTerm = grammar.addAny(
		"TypeAtomic",
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
			typeSymbolNonTemplate
		}
	);

	ruleType = typeTerm;
}

const ParserGrammar &Parser::getGrammar() const {
	W_ASSERT_TRUE(isGrammarInitted(), "Cannot get uninitialized grammar.");
	return grammar;
}

ParserRuleID Parser::getGrammarRuleType() const {
	return ruleType;
}

ParserRuleID Parser::getGrammarRuleExpr() const {
	return ruleExpr;
}

ParserRuleID Parser::getGrammarRuleStmt() const {
	return ruleStmt;
}

ParserRuleID Parser::getGrammarRuleDecl() const {
	return ruleDecl;
}

Node Parser::parse(ParserContext &ctx, MessageContext &msgs) const {
	Node rtn = grammar.getStartRule().parse(grammar, ctx, msgs).getNode();
	W_ASSERT_FALSE(ctx.more(), "Not all tokens parsed.");
	return rtn;
}
} // namespace whiskey
