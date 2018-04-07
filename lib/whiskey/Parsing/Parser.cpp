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

	ParserRuleID empty = grammar.addEmpty(
		"Empty",
		[](MessageContext &msgs) {
			return Node();
		}
	);

	ParserRuleID type = grammar.addForward();

	ParserRuleID typeVoid = grammar.addTerm(
		"TypeVoid",
		"'void'",
		TokenID::KWVoid,
		[](Token token, MessageContext &msgs) {
			return Node(NodeType::TypeVoid, token);
		}
	);

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

	ParserRuleID symbol = grammar.addTerm(
		"Symbol",
		"symbol",
		TokenID::Symbol,
		[](Token token, MessageContext &msgs) {
			return Node(token);
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
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
			return rtn;
		}
	);

	ParserRuleID templateArgsEvalOptional = grammar.addOptional(
		"TemplateArgsEval",
		"template arguments",
		templateArgsEvalNonOptional,
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setFieldNodeVector(FieldTag::List_Children);
			return rtn;
		}
	);

	ParserRuleID typeSymbol = grammar.addConcat(
		"TypeSymbol",
		"type",
		{
			symbol,
			templateArgsEvalOptional
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn = Node(NodeType::TypeSymbol, nodes[0].getToken());
			rtn.setFieldNodeVector(FieldTag::TypeSymbol_TemplateEvalArgs, nodes[1].getField(FieldTag::List_Children).getNodeVector());
			return rtn;
		}
	);

	ParserRuleID typeGroup = grammar.addForward();

	ParserRuleID typeTerm = grammar.addAny(
		"TypeAtomic",
		"type",
		{
			typeVoid,
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
			rtn.setFieldNodeVector(FieldTag::TypeAccess_Args, {lhs, rhs});
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
			rtn.setFieldNode(FieldTag::TypeAccessUnary_Arg, rhs);
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
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
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
			rtn.setFieldNode(FieldTag::TypeFunction_Return, nodes[0]);
			rtn.setFieldNodeVector(FieldTag::TypeFunction_Args, nodes[2].getField(FieldTag::List_Children).getNodeVector());
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
			rtn.setFieldUInt(FieldTag::ExprLiteralBool_Value, 0);
			return rtn;
		}
	);

	ParserRuleID exprLiteralBoolTrue = grammar.addTerm(
		"ExprLiteralBoolTrue",
		"'true'",
		TokenID::KWTrue,
		[](Token token, MessageContext &msgs) {
			Node rtn(NodeType::ExprLiteralBool, token);
			rtn.setFieldUInt(FieldTag::ExprLiteralBool_Value, 1);
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
				rtn.setFieldUInt(FieldTag::ExprLiteralUInt64_Value, tmp);
				return rtn;
			} else {
				msgs.describe() << "invalid integer format";
				msgs.emit(token, Message::Severity::Error);
				Node rtn(NodeType::ExprLiteralUInt64, token);
				rtn.setFieldUInt(FieldTag::ExprLiteralUInt64_Value, 0);
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
				rtn.setFieldUInt(FieldTag::ExprLiteralChar32_Value, tmp);
				return rtn;
			} else {
				msgs.describe() << "invalid character format";
				msgs.emit(token, Message::Severity::Error);
				Node rtn(NodeType::ExprLiteralChar32, token);
				rtn.setFieldUInt(FieldTag::ExprLiteralChar32_Value, 0);
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
				rtn.setFieldReal(FieldTag::ExprLiteralReal_Value, tmp);
				return rtn;
			} else {
				msgs.describe() << "invalid real format";
				msgs.emit(token, Message::Severity::Error);
				Node rtn(NodeType::ExprLiteralReal, token);
				rtn.setFieldReal(FieldTag::ExprLiteralReal_Value, 0);
				return rtn;
			}
		}
	);

	ParserRuleID exprSymbol = grammar.addConcat(
		"ExprSymbol",
		"expression",
		{
			symbol,
			templateArgsEvalOptional
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::ExprSymbol, nodes[0].getToken());
			rtn.setFieldNodeVector(FieldTag::ExprSymbol_TemplateEvalArgs, nodes[1].getField(FieldTag::List_Children).getNodeVector());
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
			rtn.setFieldNodeVector(FieldTag::ExprAccess_Args, {lhs, rhs});
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
			rtn.setFieldNode(FieldTag::ExprAccessUnary_Arg, rhs);
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
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
			return rtn;
		}
	);

	ParserRuleID exprCallArgsOptional = grammar.addOptional(
		"ExprCallArgsOptional",
		"call arguments",
		exprCallArgsNonOptional,
		[](MessageContext &msgs) {
			return Node();
		}
	);

	ParserRuleID exprCall = grammar.addConcat(
		"ExprCall",
		"expression",
		{
			exprAccessUnary,
			exprCallArgsOptional
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			if (nodes[1].getType() == NodeType::List) {
				Node rtn(NodeType::ExprCall, nodes[1].getToken());
				rtn.setFieldNode(FieldTag::ExprCall_Callee, nodes[0]);
				rtn.setFieldNodeVector(FieldTag::ExprCall_Args, nodes[1].getField(FieldTag::List_Children).getNodeVector());
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
				rtn.setFieldNode(FieldTag::ExprNeg_Arg, rhs);
				return rtn;
			} else if (token.getID() == TokenID::Inc) {
				Node rtn(NodeType::ExprIncPre);
				rtn.setFieldNode(FieldTag::ExprIncPre_Arg, rhs);
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn(NodeType::ExprDecPre);
				rtn.setFieldNode(FieldTag::ExprDecPre_Arg, rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitNot) {
				Node rtn(NodeType::ExprBitNot);
				rtn.setFieldNode(FieldTag::ExprBitNot_Arg, rhs);
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
				rtn.setFieldNode(FieldTag::ExprIncPost_Arg, lhs);
				return rtn;
			} else if (token.getID() == TokenID::Dec) {
				Node rtn(NodeType::ExprDecPost);
				rtn.setFieldNode(FieldTag::ExprDecPost_Arg, lhs);
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
				rtn.setFieldNode(FieldTag::ExprExp_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprExp_RHS, rhs);
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
				rtn.setFieldNodeVector(FieldTag::ExprMul_Args, {lhs, rhs});
				return rtn;
			} else if (token.getID() == TokenID::Div) {
				Node rtn(NodeType::ExprDiv, token);
				rtn.setFieldNode(FieldTag::ExprDiv_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprDiv_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::DivInt) {
				Node rtn(NodeType::ExprDivInt, token);
				rtn.setFieldNode(FieldTag::ExprDivInt_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprDivInt_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::DivReal) {
				Node rtn(NodeType::ExprDivReal, token);
				rtn.setFieldNode(FieldTag::ExprDivReal_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprDivReal_RHS, rhs);
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
				rtn.setFieldNodeVector(FieldTag::ExprAdd_Args, {lhs, rhs});
				return rtn;	
			} else if (token.getID() == TokenID::Sub) {
				Node rtn(NodeType::ExprSub, token);
				rtn.setFieldNode(FieldTag::ExprSub_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprSub_RHS, rhs);
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
				rtn.setFieldNode(FieldTag::ExprMod_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprMod_RHS, rhs);
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
				rtn.setFieldNode(FieldTag::ExprBitShR_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitShR_RHS, rhs);
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
				rtn.setFieldNode(FieldTag::ExprBitShL_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitShL_RHS, rhs);
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
				rtn.setFieldNodeVector(FieldTag::ExprBitAnd_Args, {lhs, rhs});
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
				rtn.setFieldNodeVector(FieldTag::ExprBitOr_Args, {lhs, rhs});
				return rtn;
			} else if (token.getID() == TokenID::BitXor) {
				Node rtn(NodeType::ExprBitXor, token);
				rtn.setFieldNodeVector(FieldTag::ExprBitXor_Args, {lhs, rhs});
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
				rtn.setFieldNode(FieldTag::ExprLT_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprLT_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::LE) {
				Node rtn(NodeType::ExprLE, token);
				rtn.setFieldNode(FieldTag::ExprLE_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprLE_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::GT) {
				Node rtn(NodeType::ExprGT, token);
				rtn.setFieldNode(FieldTag::ExprGT_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprGT_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::GE) {
				Node rtn(NodeType::ExprGE, token);
				rtn.setFieldNode(FieldTag::ExprGE_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprGE_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::NE) {
				Node rtn(NodeType::ExprNE, token);
				rtn.setFieldNode(FieldTag::ExprNE_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprNE_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::EQ) {
				Node rtn(NodeType::ExprEQ, token);
				rtn.setFieldNode(FieldTag::ExprEQ_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprEQ_RHS, rhs);
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
				rtn.setFieldNode(FieldTag::ExprBoolNot_Arg, rhs);
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
				rtn.setFieldNodeVector(FieldTag::ExprBoolAnd_Args, {lhs, rhs});
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
				rtn.setFieldNodeVector(FieldTag::ExprBoolOr_Args, {lhs, rhs});
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
				rtn.setFieldNodeVector(FieldTag::ExprBoolImplies_Args, {lhs, rhs});
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
				rtn.setFieldNode(FieldTag::ExprAddAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprAddAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::SubAssign) {
				Node rtn(NodeType::ExprSubAssign, token);
				rtn.setFieldNode(FieldTag::ExprSubAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprSubAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::MulAssign) {
				Node rtn(NodeType::ExprMulAssign, token);
				rtn.setFieldNode(FieldTag::ExprMulAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprMulAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::DivIntAssign) {
				Node rtn(NodeType::ExprDivIntAssign, token);
				rtn.setFieldNode(FieldTag::ExprDivIntAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprDivIntAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::DivRealAssign) {
				Node rtn(NodeType::ExprDivRealAssign, token);
				rtn.setFieldNode(FieldTag::ExprDivRealAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprDivRealAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::ModAssign) {
				Node rtn(NodeType::ExprModAssign, token);
				rtn.setFieldNode(FieldTag::ExprModAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprModAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitAndAssign) {
				Node rtn(NodeType::ExprBitAndAssign, token);
				rtn.setFieldNode(FieldTag::ExprBitAndAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitAndAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitOrAssign) {
				Node rtn(NodeType::ExprBitOrAssign, token);
				rtn.setFieldNode(FieldTag::ExprBitOrAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitOrAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitXorAssign) {
				Node rtn(NodeType::ExprBitXorAssign, token);
				rtn.setFieldNode(FieldTag::ExprBitXorAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitXorAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitShLAssign) {
				Node rtn(NodeType::ExprBitShLAssign, token);
				rtn.setFieldNode(FieldTag::ExprBitShLAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitShLAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::BitShRAssign) {
				Node rtn(NodeType::ExprBitShRAssign, token);
				rtn.setFieldNode(FieldTag::ExprBitShRAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprBitShRAssign_RHS, rhs);
				return rtn;
			} else if (token.getID() == TokenID::Assign) {
				Node rtn(NodeType::ExprAssign, token);
				rtn.setFieldNode(FieldTag::ExprAssign_LHS, lhs);
				rtn.setFieldNode(FieldTag::ExprAssign_RHS, rhs);
				return rtn;
			} else {
				W_ASSERT_UNREACHABLE("Unexpected operator.");
			}
		}
	);

	ParserRuleID exprList = grammar.addListSeparated(
		"ExprList",
		"expression",
		expr,
		comma,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
			return rtn;
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
			rtn.setFieldNode(FieldTag::StmtExpr_Expr, nodes[0]);
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
			rtn.setFieldNode(FieldTag::StmtDecl_Decl, nodes[0]);
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
			rtn.setFieldNode(FieldTag::StmtReturn_Arg, nodes[1]);
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
			rtn.setFieldString(FieldTag::StmtContinue_Name, nodes[1].getToken().getText());
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
			rtn.setFieldString(FieldTag::StmtBreak_Name, nodes[1].getToken().getText());
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

	ParserRuleID elseOptional = grammar.addOptional(
		"ElseOptional",
		"statement",
		elseNonOptional,
		[](MessageContext &msgs) {
			return Node();
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
			rtn.setFieldNode(FieldTag::StmtIf_Condition, nodes[2]);
			rtn.setFieldNode(FieldTag::StmtIf_Then, nodes[4]);
			if (nodes[5].getType() != NodeType::None) {
				rtn.setFieldNode(FieldTag::StmtIf_Else, nodes[5]);
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
			rtn.setFieldNode(FieldTag::StmtWhile_Condition, nodes[2]);
			rtn.setFieldNode(FieldTag::StmtWhile_Body, nodes[4]);
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
			rtn.setFieldNodeVector(FieldTag::StmtFor_Decls, nodes[2].getField(FieldTag::List_Children).getNodeVector());
			rtn.setFieldNode(FieldTag::StmtFor_Condition, nodes[4]);
			rtn.setFieldNodeVector(FieldTag::StmtFor_Steps, nodes[6].getField(FieldTag::List_Children).getNodeVector());
			rtn.setFieldNode(FieldTag::StmtFor_Body, nodes[8]);
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
			rtn.setFieldNode(FieldTag::StmtForEach_Decl, nodes[2]);
			rtn.setFieldNode(FieldTag::StmtForEach_Sequence, nodes[4]);
			rtn.setFieldNode(FieldTag::StmtForEach_Body, nodes[6]);
			return rtn;
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

	ParserRuleID stmtBlock = grammar.addListBound(
		"StmtBlock",
		"statement",
		stmt,
		leftBrace,
		rightBrace,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::StmtBlock);
			rtn.setFieldNodeVector(FieldTag::StmtBlock_Stmts, nodes);
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
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
			return rtn;
		}
	);

	ParserRuleID templateArgsDeclOptional = grammar.addOptional(
		"TemplateArgsDeclOptional",
		"template arguments",
		templateArgsDeclNonOptional,
		[](MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setFieldNodeVector(FieldTag::List_Children);
			return rtn;
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

	ParserRuleID declVariableAssignmentOptional = grammar.addAny(
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
			templateArgsDeclOptional,
			declVariableAssignmentOptional
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclVariable, nodes[1].getToken());
			rtn.setFieldNode(FieldTag::DeclVariable_Type, nodes[0]);
			rtn.setFieldNodeVector(FieldTag::DeclVariable_TemplateDeclArgs, nodes[2].getField(FieldTag::List_Children).getNodeVector());
			if (nodes[3].getType() != NodeType::None) {
				rtn.setFieldNode(FieldTag::DeclVariable_Initial, nodes[3]);
			}
			return rtn;
		}
	);

	grammar.addListSeparated(
		declVariableList,
		"DeclVariableList",
		"declaration",
		declVariableNoSemicolon,
		comma,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
			return rtn;
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
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
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
			templateArgsDeclOptional,
			declFunctionArgs,
			declFunctionBody
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclFunction, nodes[1].getToken());
			rtn.setFieldNode(FieldTag::DeclFunction_Return, nodes[0]);
			rtn.setFieldNodeVector(FieldTag::DeclFunction_TemplateDeclArgs, nodes[2].getField(FieldTag::List_Children).getNodeVector());
			rtn.setFieldNodeVector(FieldTag::DeclFunction_Args, nodes[3].getField(FieldTag::List_Children).getNodeVector());
			rtn.setFieldNode(FieldTag::DeclFunction_Body, nodes[4]);
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
			templateArgsDeclOptional,
			leftBrace,
			declList,
			rightBrace
		},
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::DeclClass, nodes[1].getToken());
			rtn.setFieldNodeVector(FieldTag::DeclClass_TemplateDeclArgs, nodes[2].getField(FieldTag::List_Children).getNodeVector());
			rtn.setFieldNodeVector(FieldTag::DeclClass_Members, nodes[4].getField(FieldTag::List_Children).getNodeVector());
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
			rtn.setFieldNodeVector(FieldTag::DeclNamespace_Members, nodes[3].getField(FieldTag::List_Children).getNodeVector());
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

	grammar.addList(
		declList,
		"DeclList",
		"declaration",
		decl,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::List);
			rtn.setFieldNodeVector(FieldTag::List_Children, nodes);
			return rtn;
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
				rtn.setFieldString(FieldTag::Import_Path, tmp);
				return rtn;
			} else {
				msgs.describe() << "invalid string format";
				msgs.emit(nodes[1].getToken(), Message::Severity::Error);
				Node rtn(NodeType::Import, nodes[0].getToken());
				rtn.setFieldString(FieldTag::Import_Path);
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
	
	ParserRuleID unit = grammar.addList(
		"Unit",
		"top-level statement",
		unitMember,
		[](const std::vector<Node> &nodes, MessageContext &msgs) {
			Node rtn(NodeType::Unit);
			rtn.setFieldNodeVector(FieldTag::Unit_Members, nodes);
			return rtn;
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
