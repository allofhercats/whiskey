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

	ParserRuleID type = grammar.addForward();

	ParserRuleID typeAtomicBool = grammar.addTerm(
		"TypeAtomicBool",
		"'bool'",
		TokenID::KWBool,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicBool, token);
		}
	);

	ParserRuleID typeAtomicInt8 = grammar.addTerm(
		"TypeAtomicInt8",
		"'int8'",
		TokenID::KWInt8,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicInt8, token);
		}
	);

	ParserRuleID typeAtomicInt16 = grammar.addTerm(
		"TypeAtomicInt16",
		"'int16'",
		TokenID::KWInt16,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicInt16, token);
		}
	);

	ParserRuleID typeAtomicInt32 = grammar.addTerm(
		"TypeAtomicInt32",
		"'int32'",
		TokenID::KWInt32,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicInt32, token);
		}
	);

	ParserRuleID typeAtomicInt64 = grammar.addTerm(
		"TypeAtomicInt64",
		"'int64'",
		TokenID::KWInt64,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicInt64, token);
		}
	);

	ParserRuleID typeAtomicUInt8 = grammar.addTerm(
		"TypeAtomicUInt8",
		"'uint8'",
		TokenID::KWUInt8,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicUInt8, token);
		}
	);

	ParserRuleID typeAtomicUInt16 = grammar.addTerm(
		"TypeAtomicUInt16",
		"'uint16'",
		TokenID::KWUInt16,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicUInt16, token);
		}
	);

	ParserRuleID typeAtomicUInt32 = grammar.addTerm(
		"TypeAtomicUInt32",
		"'uint32'",
		TokenID::KWUInt32,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicUInt32, token);
		}
	);

	ParserRuleID typeAtomicUInt64 = grammar.addTerm(
		"TypeAtomicUInt64",
		"'uint64'",
		TokenID::KWUInt64,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicUInt64, token);
		}
	);

	ParserRuleID typeAtomicFloat32 = grammar.addTerm(
		"TypeAtomicFloat32",
		"'float32'",
		TokenID::KWFloat32,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicFloat32, token);
		}
	);

	ParserRuleID typeAtomicFloat64 = grammar.addTerm(
		"TypeAtomicFloat64",
		"'float64'",
		TokenID::KWFloat64,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicFloat64, token);
		}
	);

	ParserRuleID typeAtomicReal = grammar.addTerm(
		"TypeAtomicReal",
		"'real'",
		TokenID::KWReal,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeAtomicReal, token);
		}
	);

	ParserRuleID typeSymbolNonTemplate = grammar.addTerm(
		"TypeSymbolNonTemplate",
		"type",
		TokenID::Symbol,
		[](Token token, MessageContext &msgs) {
			Node rtn(NodeType::TypeSymbol, token);
			rtn.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID leftAngleBracket = grammar.addTerm(
		"LeftAngleBracket",
		"<",
		TokenID::LT,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID comma = grammar.addTerm(
		"Comma",
		",",
		TokenID::Comma,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID rightAngleBracket = grammar.addTerm(
		"RightAngleBracket",
		">",
		TokenID::GT,
		{
			{TokenID::GE, TokenID::Assign},
			{TokenID::BitShR, TokenID::GT},
			{TokenID::BitShRAssign, TokenID::GE}
		},
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprTerm = grammar.addForward();

	ParserRuleID templateArg = grammar.addAny(
		"TemplateArg",
		"template argument",
		{
			type,
			exprTerm
		}
	);

	ParserRuleID templateArgsEvalNonOptional = grammar.addListBoundSeparated(
		"TemplateArgsEvalListNonOptional",
		"template arguments",
		templateArg,
		leftAngleBracket,
		comma,
		rightAngleBracket,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
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

	ParserRuleID templateArgsEvalOptional = grammar.addEmpty(
		"TemplateArgsEvalOptional",
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID templateArgsEval = grammar.addAny(
		"TemplateArgsEval",
		"template arguments",
		{
			templateArgsEvalNonOptional,
			templateArgsEvalOptional
		}
	);

	ParserRuleID typeSymbol = grammar.addConcat(
		"TypeSymbol",
		"type",
		{
			typeSymbolNonTemplate,
			templateArgsEval
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[0];
			rtn.setField(FieldTag::TypeSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			return rtn;
		}
	);

	ParserRuleID typeGroup = grammar.addForward();

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
			typeSymbol,
			typeGroup
		}
	);

	ParserRuleID period = grammar.addTerm(
		"Period",
		".",
		TokenID::Period,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID typeAccess = grammar.addBinary(
		"TypeAccess",
		"type",
		typeTerm,
		typeTerm,
		{
			period
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			Node rtn(NodeType::TypeAccess, token);
			rtn.setField(FieldTag::TypeAccess_Args, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(lhs);
			rtn.getField(FieldTag::TypeAccess_Args).as<FieldNodeVector>().getValue().push_back(rhs);
			return rtn;
		}
	);

	ParserRuleID typeAccessUnary = grammar.addUnaryRight(
		"TypeAccessUnary",
		"type",
		typeAccess,
		{
			period,
		},
		[](Token token, Node rhs, MessageContext &msgs) {
			Node rtn(NodeType::TypeAccessUnary, token);
			rtn.setField(FieldTag::TypeAccessUnary_Arg, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);

	ParserRuleID leftParen = grammar.addTerm(
		"LeftParen",
		"(",
		TokenID::LParen,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID rightParen = grammar.addTerm(
		"RightParen",
		")",
		TokenID::RParen,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	grammar.addConcat(
		typeGroup,
		"TypeGroup",
		"type",
		{
			leftParen,
			type,
			rightParen
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return nodes[1];
		}
	);

	ParserRuleID leftArrow = grammar.addTerm(
		"LeftArrow",
		"<-",
		TokenID::LArrow,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID typeFunctionArgs = grammar.addListBoundSeparated(
		"TypeFunctionArgs",
		"function type arguments",
		type,
		leftParen,
		comma,
		rightParen,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
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

	ParserRuleID typeFunction = grammar.addConcat(
		"TypeFunction",
		"type",
		{
			typeAccessUnary,
			leftArrow,
			typeFunctionArgs
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::TypeFunction, nodes[1].getToken());
			rtn.setField(FieldTag::TypeFunction_Return, std::make_unique<FieldNode>(nodes[0]));
			rtn.setField(FieldTag::TypeFunction_Args, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			return rtn;
		},
		2
	);

	grammar.addAny(
		type,
		"Type",
		"type",
		{
			typeFunction,
			typeAccessUnary
		}
	);

	ParserRuleID exprLiteralBoolFalse = grammar.addTerm(
		"ExprLiteralBoolFalse",
		"'false'",
		TokenID::KWFalse,
		[](Token token, MessageContext &msgs) {
			Node rtn(NodeType::ExprLiteralBool, token);
			rtn.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(0));
			return rtn;
		}
	);

	ParserRuleID exprLiteralBoolTrue = grammar.addTerm(
		"ExprLiteralBoolTrue",
		"'true'",
		TokenID::KWTrue,
		[](Token token, MessageContext &msgs) {
			Node rtn(NodeType::ExprLiteralBool, token);
			rtn.setField(FieldTag::ExprLiteralBool_Value, std::make_unique<FieldUInt>(1));
			return rtn;
		}
	);

	ParserRuleID exprLiteralBool = grammar.addAny(
		"ExprLiteralBool",
		"literal bool",
		{
			exprLiteralBoolFalse,
			exprLiteralBoolTrue
		}
	);

	ParserRuleID exprLiteralUInt = grammar.addTerm(
		"ExprLiteralUInt",
		"literal integer",
		TokenID::Int,
		[](Token token, MessageContext &msgs) {
			UInt64 tmp;
			if (evalLiteralUInt(token.getText(), tmp)) {
				Node rtn(NodeType::ExprLiteralUInt64, token);
				rtn.setField(FieldTag::ExprLiteralUInt64_Value, std::make_unique<FieldUInt>(tmp));
				return rtn;
			} else {
				msgs.describe() << "invalid integer format";
				msgs.emit(token, Message::Severity::Error);
				Node rtn(NodeType::ExprLiteralUInt64, token);
				rtn.setField(FieldTag::ExprLiteralUInt64_Value, std::make_unique<FieldUInt>(0));
				return rtn;
			}
		}
	);

	ParserRuleID exprLiteralChar = grammar.addTerm(
		"ExprLiteralChar",
		"literal character",
		TokenID::Char,
		[](Token token, MessageContext &msgs) {
			Char32 tmp;
			if (evalLiteralChar(token.getText(), tmp)) {
				Node rtn(NodeType::ExprLiteralChar32, token);
				rtn.setField(FieldTag::ExprLiteralChar32_Value, std::make_unique<FieldUInt>(tmp));
				return rtn;
			} else {
				msgs.describe() << "invalid character format";
				msgs.emit(token, Message::Severity::Error);
				Node rtn(NodeType::ExprLiteralChar32, token);
				rtn.setField(FieldTag::ExprLiteralChar32_Value, std::make_unique<FieldUInt>(0));
				return rtn;
			}
		}
	);

	ParserRuleID exprLiteralReal = grammar.addTerm(
		"ExprLiteralReal",
		"literal real",
		TokenID::Real,
		[](Token token, MessageContext &msgs) {
			Real tmp;
			if (evalLiteralReal(token.getText(), tmp)) {
				Node rtn(NodeType::ExprLiteralReal, token);
				rtn.setField(FieldTag::ExprLiteralReal_Value, std::make_unique<FieldReal>(tmp));
				return rtn;
			} else {
				msgs.describe() << "invalid real format";
				msgs.emit(token, Message::Severity::Error);
				Node rtn(NodeType::ExprLiteralReal, token);
				rtn.setField(FieldTag::ExprLiteralReal_Value, std::make_unique<FieldReal>(0));
				return rtn;
			}
		}
	);

	ParserRuleID exprSymbolNonTemplate = grammar.addTerm(
		"ExprSymbolNonTemplate",
		"expression",
		TokenID::Symbol,
		[](Token token, MessageContext &msgs) {
			Node rtn(NodeType::ExprSymbol, token);
			rtn.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID exprSymbol = grammar.addConcat(
		"ExprSymbol",
		"expression",
		{
			exprSymbolNonTemplate,
			templateArgsEval
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[0];
			rtn.setField(FieldTag::ExprSymbol_TemplateEvalArgs, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			return rtn;
		}
	);

	ParserRuleID exprGroup = grammar.addForward();

	grammar.addAny(
		exprTerm,
		"ExprTerm",
		"expression",
		{
			exprLiteralBool,
			exprLiteralUInt,
			exprLiteralChar,
			exprLiteralReal,
			exprSymbol,
			exprGroup
		}
	);

	ParserRuleID exprAccess = grammar.addBinary(
		"ExprAccess",
		"expression",
		exprTerm,
		exprTerm,
		{
			period
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			Node rtn(NodeType::ExprAccess, token);
			rtn.setField(FieldTag::ExprAccess_Args, std::make_unique<FieldNodeVector>());
			rtn.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(lhs);
			rtn.getField(FieldTag::ExprAccess_Args).as<FieldNodeVector>().getValue().push_back(rhs);
			return rtn;
		}
	);

	ParserRuleID exprAccessUnary = grammar.addUnaryRight(
		"ExprAccessUnary",
		"expression",
		exprAccess,
		{
			period,
		},
		[](Token token, Node rhs, MessageContext &msgs) {
			Node rtn(NodeType::ExprAccessUnary, token);
			rtn.setField(FieldTag::ExprAccessUnary_Arg, std::make_unique<FieldNode>(rhs));
			return rtn;
		}
	);

	ParserRuleID expr = grammar.addForward();

	grammar.addConcat(
		exprGroup,
		"ExprGroup",
		"expression",
		{
			leftParen,
			expr,
			rightParen
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return nodes[1];
		}
	);

	ParserRuleID exprCallArgsNonOptional = grammar.addListBoundSeparated(
		"ExprCallArgsNonOptional",
		"call arguments",
		expr,
		leftParen,
		comma,
		rightParen,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
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

	ParserRuleID exprCallArgsEmpty = grammar.addEmpty(
		"ExprCallArgsOptional",
		[](MessageContext &msgs) {
			return Node();
		}
	);

	ParserRuleID exprCallArgs = grammar.addAny(
		"ExprCallArgs",
		"call arguments",
		{
			exprCallArgsNonOptional,
			exprCallArgsEmpty
		}
	);

	ParserRuleID exprCall = grammar.addConcat(
		"ExprCall",
		"expression",
		{
			exprAccessUnary,
			exprCallArgs
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			if (nodes[1].getType() == NodeType::List) {
				Node rtn(NodeType::ExprCall, nodes[1].getToken());
				rtn.setField(FieldTag::ExprCall_Callee, std::make_unique<FieldNode>(nodes[0]));
				rtn.setField(FieldTag::ExprCall_Args, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
				return rtn;
			} else {
				return nodes[0];
			}
		}
	);

	ParserRuleID sub = grammar.addTerm(
		"Sub",
		"-",
		TokenID::Sub,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID inc = grammar.addTerm(
		"Inc",
		"++",
		TokenID::Inc,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID dec = grammar.addTerm(
		"Dec",
		"--",
		TokenID::Dec,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitNot = grammar.addTerm(
		"BitNot",
		"~",
		TokenID::BitNot,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprUnaryRight = grammar.addUnaryRight(
		"ExprUnaryRight",
		"expression",
		exprCall,
		{
			sub,
			inc,
			dec,
			bitNot
		},
		[](Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::Sub) {
				Node rtn(NodeType::ExprNeg);
				rtn.setField(FieldTag::ExprNeg_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Inc) {
				Node rtn(NodeType::ExprIncPre);
				rtn.setField(FieldTag::ExprIncPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn(NodeType::ExprDecPre);
				rtn.setField(FieldTag::ExprDecPre_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitNot) {
				Node rtn(NodeType::ExprBitNot);
				rtn.setField(FieldTag::ExprBitNot_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID exprUnaryLeft = grammar.addUnaryLeft(
		"ExprUnaryLeft",
		"expression",
		exprUnaryRight,
		{
			sub,
			inc
		},
		[](Node lhs, Token token, MessageContext &msgs) {
			if (token.getID() == TokenID::Inc) {
				Node rtn(NodeType::ExprIncPost);
				rtn.setField(FieldTag::ExprIncPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn(NodeType::ExprDecPost);
				rtn.setField(FieldTag::ExprDecPost_Arg, std::make_unique<FieldNode>(lhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID exp = grammar.addTerm(
		"Exp",
		"**",
		TokenID::Exp,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprExp = grammar.addBinary(
		"ExprExp",
		"expression",
		exprUnaryLeft,
		exprUnaryLeft,
		{
			exp
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::Exp) {
				Node rtn(NodeType::ExprExp, token);
				rtn.setField(FieldTag::ExprExp_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprExp_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID mul = grammar.addTerm(
		"Mul",
		"*",
		TokenID::Mul,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID div = grammar.addTerm(
		"Div",
		"/",
		TokenID::Div,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID divInt = grammar.addTerm(
		"DivInt",
		"//",
		TokenID::DivInt,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID divReal = grammar.addTerm(
		"DivReal",
		"/.",
		TokenID::DivReal,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprMul = grammar.addBinary(
		"ExprMul",
		"expression",
		exprExp,
		exprExp,
		{
			mul,
			div,
			divInt,
			divReal
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::Mul) {
				Node rtn(NodeType::ExprMul, token);
				rtn.setField(FieldTag::ExprMul_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprMul_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprMul_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::Div) {
				Node rtn(NodeType::ExprDiv, token);
				rtn.setField(FieldTag::ExprDiv_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDiv_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::DivInt) {
				Node rtn(NodeType::ExprDivInt, token);
				rtn.setField(FieldTag::ExprDivInt_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDivInt_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::DivReal) {
				Node rtn(NodeType::ExprDivReal, token);
				rtn.setField(FieldTag::ExprDivReal_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDivReal_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID add = grammar.addTerm(
		"Add",
		"+",
		TokenID::Add,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprAdd = grammar.addBinary(
		"ExprAdd",
		"expression",
		exprMul,
		exprMul,
		{
			add,
			sub
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::Add) {
				Node rtn(NodeType::ExprAdd, token);
				rtn.setField(FieldTag::ExprAdd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprAdd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;	
			} else if (token.getID() == TokenID::Sub) {
				Node rtn(NodeType::ExprSub, token);
				rtn.setField(FieldTag::ExprSub_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSub_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID mod = grammar.addTerm(
		"Mod",
		"%",
		TokenID::Mod,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprMod = grammar.addBinary(
		"ExprMod",
		"expression",
		exprAdd,
		exprAdd,
		{
			mod
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::Mod) {
				Node rtn(NodeType::ExprMod, token);
				rtn.setField(FieldTag::ExprMod_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprMod_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID bitShR = grammar.addTerm(
		"BitShR",
		">>",
		TokenID::BitShR,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBitShR = grammar.addBinary(
		"ExprBitShR",
		"expression",
		exprMod,
		exprMod,
		{
			bitShR
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::BitShR) {
				Node rtn(NodeType::ExprBitShR, token);
				rtn.setField(FieldTag::ExprBitShR_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitShR_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID bitShL = grammar.addTerm(
		"BitShL",
		"<<",
		TokenID::BitShL,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBitShL = grammar.addBinary(
		"ExprBitShL",
		"expression",
		exprBitShR,
		exprBitShR,
		{
			bitShL
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::BitShL) {
				Node rtn(NodeType::ExprBitShL, token);
				rtn.setField(FieldTag::ExprBitShL_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitShL_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID bitAnd = grammar.addTerm(
		"BitAnd",
		"&",
		TokenID::BitAnd,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBitAnd = grammar.addBinary(
		"ExprBitAnd",
		"expression",
		exprBitShL,
		exprBitShL,
		{
			bitAnd
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::BitAnd) {
				Node rtn(NodeType::ExprBitAnd, token);
				rtn.setField(FieldTag::ExprBitAnd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprBitAnd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprBitAnd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID bitOr = grammar.addTerm(
		"BitOr",
		"|",
		TokenID::BitOr,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitXor = grammar.addTerm(
		"BitXor",
		"^",
		TokenID::BitXor,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBitOr = grammar.addBinary(
		"ExprBitOr",
		"expression",
		exprBitAnd,
		exprBitAnd,
		{
			bitOr,
			bitXor
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::BitOr) {
				Node rtn(NodeType::ExprBitOr, token);
				rtn.setField(FieldTag::ExprBitOr_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprBitOr_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprBitOr_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitXor) {
				Node rtn(NodeType::ExprBitXor, token);
				rtn.setField(FieldTag::ExprBitXor_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprBitXor_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprBitXor_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID lt = grammar.addTerm(
		"LT",
		"<",
		TokenID::LT,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID le = grammar.addTerm(
		"LE",
		"<=",
		TokenID::LE,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID gt = grammar.addTerm(
		"GT",
		">",
		TokenID::GT,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID ge = grammar.addTerm(
		"GE",
		">=",
		TokenID::GE,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID ne = grammar.addTerm(
		"NE",
		"!=",
		TokenID::NE,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID eq = grammar.addTerm(
		"EQ",
		"==",
		TokenID::EQ,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprCmp = grammar.addBinary(
		"ExprCmp",
		"expression",
		exprBitOr,
		exprBitOr,
		{
			lt,
			le,
			gt,
			ge,
			ne,
			eq
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::LT) {
				Node rtn(NodeType::ExprLT, token);
				rtn.setField(FieldTag::ExprLT_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprLT_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::LE) {
				Node rtn(NodeType::ExprLE, token);
				rtn.setField(FieldTag::ExprLE_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprLE_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::GT) {
				Node rtn(NodeType::ExprGT, token);
				rtn.setField(FieldTag::ExprGT_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprGT_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::GE) {
				Node rtn(NodeType::ExprGE, token);
				rtn.setField(FieldTag::ExprGE_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprGE_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::NE) {
				Node rtn(NodeType::ExprNE, token);
				rtn.setField(FieldTag::ExprNE_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprNE_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::EQ) {
				Node rtn(NodeType::ExprEQ, token);
				rtn.setField(FieldTag::ExprEQ_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprEQ_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID boolNot = grammar.addTerm(
		"BoolNot",
		"'not'",
		TokenID::KWNot,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBoolNot = grammar.addUnaryRight(
		"ExprBoolNot",
		"expression",
		exprCmp,
		{
			boolNot
		},
		[](Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::KWNot) {
				Node rtn(NodeType::ExprBoolNot);
				rtn.setField(FieldTag::ExprBoolNot_Arg, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID boolAnd = grammar.addTerm(
		"BoolAnd",
		"'and'",
		TokenID::KWAnd,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBoolAnd = grammar.addBinary(
		"ExprBoolAnd",
		"expression",
		exprBoolNot,
		exprBoolNot,
		{
			boolAnd
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::KWAnd) {
				Node rtn(NodeType::ExprBoolAnd, token);
				rtn.setField(FieldTag::ExprBoolAnd_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprBoolAnd_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID boolOr = grammar.addTerm(
		"BoolOr",
		"'or'",
		TokenID::KWOr,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBoolOr = grammar.addBinary(
		"ExprBoolOr",
		"expression",
		exprBoolAnd,
		exprBoolAnd,
		{
			boolOr
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::KWOr) {
				Node rtn(NodeType::ExprBoolOr, token);
				rtn.setField(FieldTag::ExprBoolOr_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprBoolOr_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprBoolOr_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID boolImplies = grammar.addTerm(
		"BoolImplies",
		"=>",
		TokenID::BoolImplies,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID exprBoolImplies = grammar.addBinary(
		"ExprBoolImplies",
		"expression",
		exprBoolOr,
		exprBoolOr,
		{
			boolImplies
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::BoolImplies) {
				Node rtn(NodeType::ExprBoolImplies, token);
				rtn.setField(FieldTag::ExprBoolImplies_Args, std::make_unique<FieldNodeVector>());
				rtn.getField(FieldTag::ExprBoolImplies_Args).as<FieldNodeVector>().getValue().push_back(lhs);
				rtn.getField(FieldTag::ExprBoolImplies_Args).as<FieldNodeVector>().getValue().push_back(rhs);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID addAssign = grammar.addTerm(
		"AddAssign",
		"+=",
		TokenID::AddAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID subAssign = grammar.addTerm(
		"SubAssign",
		"-=",
		TokenID::SubAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID mulAssign = grammar.addTerm(
		"MulAssign",
		"*=",
		TokenID::MulAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID divAssign = grammar.addTerm(
		"DivAssign",
		"/=",
		TokenID::DivAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID divIntAssign = grammar.addTerm(
		"DivIntAssign",
		"//=",
		TokenID::DivIntAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID divRealAssign = grammar.addTerm(
		"DivRealAssign",
		"/.=",
		TokenID::DivRealAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID modAssign = grammar.addTerm(
		"ModAssign",
		"%=",
		TokenID::ModAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitAndAssign = grammar.addTerm(
		"BitAndAssign",
		"&=",
		TokenID::BitAndAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitOrAssign = grammar.addTerm(
		"BitOrAssign",
		"|=",
		TokenID::BitAndAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitXorAssign = grammar.addTerm(
		"BitXorAssign",
		"^=",
		TokenID::BitXorAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitShLAssign = grammar.addTerm(
		"BitShLAssign",
		"<<=",
		TokenID::BitShLAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID bitShRAssign = grammar.addTerm(
		"BitShRAssign",
		">>=",
		TokenID::BitShRAssign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID assign = grammar.addTerm(
		"Assign",
		"=",
		TokenID::Assign,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	grammar.addBinary(
		expr,
		"ExprAssign",
		"expression",
		exprBoolImplies,
		exprBoolImplies,
		{
			addAssign,
			subAssign,
			mulAssign,
			divAssign,
			divIntAssign,
			divRealAssign,
			modAssign,
			bitAndAssign,
			bitOrAssign,
			bitXorAssign,
			bitShLAssign,
			bitShRAssign,
			assign
		},
		[](Node lhs, Token token, Node rhs, MessageContext &msgs) {
			if (token.getID() == TokenID::AddAssign) {
				Node rtn(NodeType::ExprAddAssign, token);
				rtn.setField(FieldTag::ExprAddAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprAddAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::SubAssign) {
				Node rtn(NodeType::ExprSubAssign, token);
				rtn.setField(FieldTag::ExprSubAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprSubAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::MulAssign) {
				Node rtn(NodeType::ExprMulAssign, token);
				rtn.setField(FieldTag::ExprMulAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprMulAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::DivIntAssign) {
				Node rtn(NodeType::ExprDivIntAssign, token);
				rtn.setField(FieldTag::ExprDivIntAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDivIntAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::DivRealAssign) {
				Node rtn(NodeType::ExprDivRealAssign, token);
				rtn.setField(FieldTag::ExprDivRealAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprDivRealAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::ModAssign) {
				Node rtn(NodeType::ExprModAssign, token);
				rtn.setField(FieldTag::ExprModAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprModAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitAndAssign) {
				Node rtn(NodeType::ExprBitAndAssign, token);
				rtn.setField(FieldTag::ExprBitAndAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitAndAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitOrAssign) {
				Node rtn(NodeType::ExprBitOrAssign, token);
				rtn.setField(FieldTag::ExprBitOrAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitOrAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitXorAssign) {
				Node rtn(NodeType::ExprBitXorAssign, token);
				rtn.setField(FieldTag::ExprBitXorAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitXorAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitShLAssign) {
				Node rtn(NodeType::ExprBitShLAssign, token);
				rtn.setField(FieldTag::ExprBitShLAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitShLAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::BitShRAssign) {
				Node rtn(NodeType::ExprBitShRAssign, token);
				rtn.setField(FieldTag::ExprBitShRAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprBitShRAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else if (token.getID() == TokenID::Assign) {
				Node rtn(NodeType::ExprAssign, token);
				rtn.setField(FieldTag::ExprAssign_LHS, std::make_unique<FieldNode>(lhs));
				rtn.setField(FieldTag::ExprAssign_RHS, std::make_unique<FieldNode>(rhs));
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID exprListRecEmpty = grammar.addEmpty(
		"ExprListRecEmpty",
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID exprListNonEmpty = grammar.addForward();

	ParserRuleID exprListRec = grammar.addAny(
		"ExprListRec",
		"expression",
		{
			exprListNonEmpty,
			exprListRecEmpty
		}
	);

	grammar.addConcat(
		exprListNonEmpty,
		"ExprListNonEmpty",
		"expression",
		{
			expr,
			comma,
			exprListRec
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[2];
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().begin(),
				nodes[0]
			);
			return rtn;
		}
	);

	ParserRuleID exprList = grammar.addAny(
		"ExprList",
		"expression",
		{
			exprListNonEmpty,
			exprListRecEmpty
		}
	);

	ParserRuleID semicolon = grammar.addTerm(
		"Semicolon",
		";",
		TokenID::Semicolon,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtEmpty = grammar.addConcat(
		"StmtEmpty",
		"statement",
		{
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return Node(NodeType::StmtEmpty, nodes[0].getToken());
		}
	);

	ParserRuleID stmtExpr = grammar.addConcat(
		"StmtExpr",
		"statement",
		{
			expr,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtExpr, nodes[1].getToken());
			rtn.setField(FieldTag::StmtExpr_Expr, std::make_unique<FieldNode>(nodes[0]));
			return rtn;
		}
	);

	ParserRuleID decl = grammar.addForward();

	ParserRuleID stmtDecl = grammar.addConcat(
		"StmtDecl",
		"statement",
		{
			decl
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtDecl, nodes[0].getToken());
			rtn.setField(FieldTag::StmtDecl_Decl, std::make_unique<FieldNode>(nodes[0]));
			return rtn;
		}
	);

	ParserRuleID return_ = grammar.addTerm(
		"Return",
		"'return'",
		TokenID::KWReturn,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtReturnVoid = grammar.addConcat(
		"StmtReturnVoid",
		"statement",
		{
			return_,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return Node(NodeType::StmtReturn, nodes[0].getToken());
		},
		2
	);

	ParserRuleID stmtReturnNonVoid = grammar.addConcat(
		"StmtReturnNonVoid",
		"statement",
		{
			return_,
			expr,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = Node(NodeType::StmtReturn, nodes[0].getToken());
			rtn.setField(FieldTag::StmtReturn_Arg, std::make_unique<FieldNode>(nodes[1]));
			return rtn;
		}
	);

	ParserRuleID stmtReturn = grammar.addAny(
		"StmtReturn",
		"statement",
		{
			stmtReturnVoid,
			stmtReturnNonVoid
		}
	);

	ParserRuleID continue_ = grammar.addTerm(
		"Continue",
		"'continue'",
		TokenID::KWContinue,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtContinueWithoutSymbol = grammar.addConcat(
		"StmtContinueWithoutSymbol",
		"statement",
		{
			continue_,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return Node(NodeType::StmtContinue, nodes[0].getToken());
		},
		2
	);

	ParserRuleID symbol = grammar.addTerm(
		"Symbol",
		"symbol",
		TokenID::Symbol,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtContinueWithSymbol = grammar.addConcat(
		"StmtContinueWithSymbol",
		"statement",
		{
			continue_,
			symbol,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = Node(NodeType::StmtContinue, nodes[0].getToken());
			rtn.setField(FieldTag::StmtContinue_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
			return rtn;
		}
	);

	ParserRuleID stmtContinue = grammar.addAny(
		"StmtContinue",
		"statement",
		{
			stmtContinueWithoutSymbol,
			stmtContinueWithSymbol
		}
	);

	ParserRuleID break_ = grammar.addTerm(
		"Break",
		"'break'",
		TokenID::KWBreak,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtBreakWithoutSymbol = grammar.addConcat(
		"StmtBreakWithoutSymbol",
		"statement",
		{
			break_,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return Node(NodeType::StmtBreak, nodes[0].getToken());
		},
		2
	);

	ParserRuleID stmtBreakWithSymbol = grammar.addConcat(
		"StmtBreakWithSymbol",
		"statement",
		{
			break_,
			symbol,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = Node(NodeType::StmtBreak, nodes[0].getToken());
			rtn.setField(FieldTag::StmtBreak_Name, std::make_unique<FieldString>(nodes[1].getToken().getText()));
			return rtn;
		}
	);

	ParserRuleID stmtBreak = grammar.addAny(
		"StmtBreak",
		"statement",
		{
			stmtBreakWithoutSymbol,
			stmtBreakWithSymbol
		}
	);

	ParserRuleID if_ = grammar.addTerm(
		"If",
		"'if'",
		TokenID::KWIf,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmt = grammar.addForward();

	ParserRuleID else_ = grammar.addTerm(
		"Else",
		"'else'",
		TokenID::KWElse,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID elseNonOptional = grammar.addConcat(
		"ElseNonOptional",
		"statement",
		{
			else_,
			stmt
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return nodes[1];
		}
	);

	ParserRuleID elseEmpty = grammar.addEmpty(
		"ElseEmpty",
		[](MessageContext &msgs) {
			return Node();
		}
	);

	ParserRuleID elseOptional = grammar.addAny(
		"ElseOptional",
		"statement",
		{
			elseNonOptional,
			elseEmpty
		}
	);

	ParserRuleID stmtIf = grammar.addConcat(
		"StmtIf",
		"statement",
		{
			if_,
			leftParen,
			expr,
			rightParen,
			stmt,
			elseOptional
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtIf, nodes[0].getToken());
			rtn.setField(FieldTag::StmtIf_Condition, std::make_unique<FieldNode>(nodes[2]));
			rtn.setField(FieldTag::StmtIf_Then, std::make_unique<FieldNode>(nodes[4]));
			if (nodes[5].getType() != NodeType::None) {
				rtn.setField(FieldTag::StmtIf_Else, std::make_unique<FieldNode>(nodes[5]));
			}
			return rtn;
		}
	);

	ParserRuleID while_ = grammar.addTerm(
		"While",
		"'while'",
		TokenID::KWWhile,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtWhile = grammar.addConcat(
		"StmtWhile",
		"statement",
		{
			while_,
			leftParen,
			expr,
			rightParen,
			stmt
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtWhile, nodes[0].getToken());
			rtn.setField(FieldTag::StmtWhile_Condition, std::make_unique<FieldNode>(nodes[2]));
			rtn.setField(FieldTag::StmtWhile_Body, std::make_unique<FieldNode>(nodes[4]));
			return rtn;
		}
	);

	ParserRuleID for_ = grammar.addTerm(
		"For",
		"'for'",
		TokenID::KWFor,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID declVariableList = grammar.addForward();

	ParserRuleID stmtFor = grammar.addConcat(
		"StmtFor",
		"statement",
		{
			for_,
			leftParen,
			declVariableList,
			semicolon,
			expr,
			semicolon,
			exprList,
			rightParen,
			stmt
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtFor, nodes[0].getToken());
			rtn.setField(FieldTag::StmtFor_Decls, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			rtn.setField(FieldTag::StmtFor_Condition, std::make_unique<FieldNode>(nodes[4]));
			rtn.setField(FieldTag::StmtFor_Steps, std::make_unique<FieldNodeVector>(nodes[6].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			rtn.setField(FieldTag::StmtFor_Body, std::make_unique<FieldNode>(nodes[8]));
			return rtn;
		}
	);

	ParserRuleID forEach = grammar.addTerm(
		"ForEach",
		"'foreach'",
		TokenID::KWForEach,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID declVariableNoSemicolon = grammar.addForward();

	ParserRuleID stmtForEach = grammar.addConcat(
		"StmtForEach",
		"statement",
		{
			forEach,
			leftParen,
			declVariableNoSemicolon,
			semicolon,
			expr,
			rightParen,
			stmt
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtForEach, nodes[0].getToken());
			rtn.setField(FieldTag::StmtForEach_Decl, std::make_unique<FieldNode>(nodes[2]));
			rtn.setField(FieldTag::StmtForEach_Sequence, std::make_unique<FieldNode>(nodes[4]));
			rtn.setField(FieldTag::StmtForEach_Body, std::make_unique<FieldNode>(nodes[6]));
			return rtn;
		}
	);

	ParserRuleID stmtListRecEmpty = grammar.addEmpty(
		"StmtListRecEmpty",
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID stmtListNonEmpty = grammar.addForward();

	ParserRuleID stmtListRec = grammar.addAny(
		"StmtListRec",
		"statement",
		{
			stmtListNonEmpty,
			stmtListRecEmpty
		}
	);

	grammar.addConcat(
		stmtListNonEmpty,
		"StmtListNonEmpty",
		"statement",
		{
			stmt,
			stmtListRec
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[1];
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().begin(),
				nodes[0]
			);
			return rtn;
		}
	);

	ParserRuleID stmtList = grammar.addAny(
		"StmtList",
		"statement",
		{
			stmtListNonEmpty,
			stmtListRecEmpty
		}
	);

	ParserRuleID leftBrace = grammar.addTerm(
		"LeftBrace",
		"'{'",
		TokenID::LBrace,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID rightBrace = grammar.addTerm(
		"RightBrace",
		"'}'",
		TokenID::RBrace,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID stmtBlock = grammar.addConcat(
		"StmtBlock",
		"statement",
		{
			leftBrace,
			stmtList,
			rightBrace
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtBlock, nodes[0].getToken());
			rtn.setField(FieldTag::StmtBlock_Stmts, std::make_unique<FieldNodeVector>(nodes[1].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			return rtn;
		}
	);

	grammar.addAny(
		stmt,
		"Stmt",
		"statement",
		{
			stmtEmpty,
			stmtReturn,
			stmtContinue,
			stmtBreak,
			stmtIf,
			stmtForEach,
			stmtFor,
			stmtWhile,
			stmtBlock,
			stmtExpr,
			stmtDecl
		}
	);

	ParserRuleID templateArgsDeclNonOptional = grammar.addListBoundSeparated(
		"TemplateArgsDeclNonOptional",
		"template arguments",
		declVariableNoSemicolon,
		leftAngleBracket,
		comma,
		rightAngleBracket,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
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

	ParserRuleID templateArgsDeclOptional = grammar.addEmpty(
		"TemplateArgsDeclOptional",
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID templateArgsDecl = grammar.addAny(
		"TemplateArgsDecl",
		"template arguments",
		{
			templateArgsDeclNonOptional,
			templateArgsDeclOptional
		}
	);

	ParserRuleID empty = grammar.addEmpty(
		"Empty",
		[](MessageContext &msgs) {
			return Node();
		}
	);

	ParserRuleID declVariableAssignmentNonOptional = grammar.addConcat(
		"DeclVariableAssignmentNonOptional",
		"=",
		{
			assign,
			expr
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return nodes[1];
		}
	);

	ParserRuleID declVariableAssignment = grammar.addAny(
		"DeclVariableAssignment",
		"=",
		{
			declVariableAssignmentNonOptional,
			empty
		}
	);

	grammar.addConcat(
		declVariableNoSemicolon,
		"DeclVariableNoSemicolon",
		"declaration",
		{
			type,
			symbol,
			templateArgsDecl,
			declVariableAssignment
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclVariable, nodes[1].getToken());
			rtn.setField(FieldTag::DeclVariable_Type, std::make_unique<FieldNode>(nodes[0]));
			rtn.setField(FieldTag::DeclVariable_TemplateDeclArgs, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			if (nodes[3].getType() != NodeType::None) {
				rtn.setField(FieldTag::DeclVariable_Initial, std::make_unique<FieldNode>(nodes[3]));
			}
			return rtn;
		}
	);

	ParserRuleID declVariableListRecEmpty = grammar.addEmpty(
		"DeclVariableListRecEmpty",
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID declVariableListNonEmpty = grammar.addForward();

	ParserRuleID declVariableListRec = grammar.addAny(
		"DeclVariableListRec",
		"declaration",
		{
			declVariableListNonEmpty,
			declVariableListRecEmpty
		}
	);

	grammar.addConcat(
		declVariableListNonEmpty,
		"ExprListNonEmpty",
		"declaration",
		{
			declVariableNoSemicolon,
			comma,
			declVariableListRec
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[2];
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().begin(),
				nodes[0]
			);
			return rtn;
		}
	);

	grammar.addAny(
		declVariableList,
		"DeclVariableList",
		"declaration",
		{
			declVariableListNonEmpty,
			declVariableListRecEmpty
		}
	);

	ParserRuleID declVariable = grammar.addConcat(
		"DeclVariable",
		"declaration",
		{
			declVariableNoSemicolon,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return nodes[0];
		}
	);

	ParserRuleID declFunctionArgs = grammar.addListBoundSeparated(
		"DeclFunctionArgs",
		"arguments",
		declVariableNoSemicolon,
		leftParen,
		comma,
		rightParen,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
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

	ParserRuleID declFunctionBodyExpr = grammar.addConcat(
		"DeclFunctionBodyExpr",
		"body",
		{
			assign,
			expr,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			return nodes[1];
		}
	);

	ParserRuleID declFunctionBody = grammar.addAny(
		"DeclFunctionBody",
		"body",
		{
			declFunctionBodyExpr,
			stmtBlock
		}
	);

	ParserRuleID declFunction = grammar.addConcat(
		"DeclFunction",
		"declaration",
		{
			type,
			symbol,
			templateArgsDecl,
			declFunctionArgs,
			declFunctionBody
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclFunction, nodes[1].getToken());
			rtn.setField(FieldTag::DeclFunction_Return, std::make_unique<FieldNode>(nodes[0]));
			rtn.setField(FieldTag::DeclFunction_TemplateDeclArgs, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			rtn.setField(FieldTag::DeclFunction_Args, std::make_unique<FieldNodeVector>(nodes[3].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			rtn.setField(FieldTag::DeclFunction_Body, std::make_unique<FieldNode>(nodes[4]));
			return rtn;
		},
		4
	);

	ParserRuleID class_ = grammar.addTerm(
		"Class",
		"'class'",
		TokenID::KWClass,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID declList = grammar.addForward();

	ParserRuleID declClass = grammar.addConcat(
		"DeclClass",
		"declaration",
		{
			class_,
			symbol,
			templateArgsDecl,
			leftBrace,
			declList,
			rightBrace
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclClass, nodes[1].getToken());
			rtn.setField(FieldTag::DeclClass_TemplateDeclArgs, std::make_unique<FieldNodeVector>(nodes[2].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			rtn.setField(FieldTag::DeclClass_Members, std::make_unique<FieldNodeVector>(nodes[4].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			return rtn;
		}
	);

	ParserRuleID namespace_ = grammar.addTerm(
		"Namespace",
		"'namespace'",
		TokenID::KWNamespace,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID declNamespace = grammar.addConcat(
		"DeclNamespace",
		"declaration",
		{
			namespace_,
			symbol,
			leftBrace,
			declList,
			rightBrace
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclNamespace, nodes[1].getToken());
			rtn.setField(FieldTag::DeclNamespace_Members, std::make_unique<FieldNodeVector>(nodes[3].getField(FieldTag::List_Children).as<FieldNodeVector>()));
			return rtn;
		}
	);

	grammar.addAny(
		decl,
		"Decl",
		"declaration",
		{
			declNamespace,
			declClass,
			declFunction,
			declVariable
		}
	);

	ParserRuleID declListRecEmpty = grammar.addEmpty(
		"DeclListRecEmpty",
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setField(FieldTag::List_Children, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID declListNonEmpty = grammar.addForward();

	ParserRuleID declListRec = grammar.addAny(
		"DeclListRec",
		"declaration",
		{
			declListNonEmpty,
			declListRecEmpty
		}
	);

	grammar.addConcat(
		declListNonEmpty,
		"DeclListNonEmpty",
		"declaration",
		{
			decl,
			declListRec
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[2];
			rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::List_Children).as<FieldNodeVector>().getValue().begin(),
				nodes[0]
			);
			return rtn;
		}
	);

	grammar.addAny(
		declList,
		"DeclList",
		"declaration",
		{
			declListNonEmpty,
			declListRecEmpty
		}
	);

	ParserRuleID import = grammar.addTerm(
		"Import",
		"'import'",
		TokenID::KWImport,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID unitMemberImportPath = grammar.addTerm(
		"UnitMemberImportPath",
		"path",
		TokenID::String,
		[](Token token, MessageContext &msgs) {
			return Node(token);
		}
	);

	ParserRuleID unitMemberImport = grammar.addConcat(
		"UnitMemberImport",
		"import",
		{
			import,
			unitMemberImportPath,
			semicolon
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			std::string tmp;
			if (evalLiteralString(nodes[1].getToken().getText(), tmp)) {
				Node rtn(NodeType::Import, nodes[0].getToken());
				rtn.setField(FieldTag::Import_Path, std::make_unique<FieldString>(tmp));
				return rtn;
			} else {
				msgs.describe() << "invalid string format";
				msgs.emit(nodes[1].getToken(), Message::Severity::Error);
				Node rtn(NodeType::Import, nodes[0].getToken());
				rtn.setField(FieldTag::Import_Path, std::make_unique<FieldString>(""));
				return rtn;
			}
		}
	);

	ParserRuleID unitMember = grammar.addAny(
		"UnitMember",
		"top-level statement",
		{
			unitMemberImport,
			decl
		}
	);

	ParserRuleID unitMemberListRecEmpty = grammar.addEmpty(
		"UnitMemberListRecEmpty",
		[](MessageContext &msgs) {
			Node rtn(NodeType::Unit);
			rtn.setField(FieldTag::Unit_Members, std::make_unique<FieldNodeVector>());
			return rtn;
		}
	);

	ParserRuleID unitMemberListNonEmpty = grammar.addForward();

	ParserRuleID unitMemberListRec = grammar.addAny(
		"UnitMemberListRec",
		"top-level statement",
		{
			unitMemberListNonEmpty,
			unitMemberListRecEmpty
		}
	);

	grammar.addConcat(
		unitMemberListNonEmpty,
		"UnitMemberListNonEmpty",
		"top-level statement",
		{
			unitMember,
			unitMemberListRec
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = nodes[2];
			rtn.getField(FieldTag::Unit_Members).as<FieldNodeVector>().getValue().insert(
				rtn.getField(FieldTag::Unit_Members).as<FieldNodeVector>().getValue().begin(),
				nodes[0]
			);
			return rtn;
		}
	);

	ParserRuleID unit = grammar.addAny(
		"Unit",
		"top-level statement",
		{
			unitMemberListNonEmpty,
			unitMemberListRecEmpty
		}
	);

	ruleType = type;
	ruleExpr = expr;
	ruleStmt = stmt;
	ruleDecl = decl;

	grammar.setStartID(unit);
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
