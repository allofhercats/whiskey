#include <whiskey/AST/Predicates.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
bool isAtomicType(NodeType type) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (type) {
		case NodeType::TypeAtomicBool:
			return true;
		case NodeType::TypeAtomicInt8:
			return true;
		case NodeType::TypeAtomicInt16:
			return true;
		case NodeType::TypeAtomicInt32:
			return true;
		case NodeType::TypeAtomicInt64:
			return true;
		case NodeType::TypeAtomicUInt8:
			return true;
		case NodeType::TypeAtomicUInt16:
			return true;
		case NodeType::TypeAtomicUInt32:
			return true;
		case NodeType::TypeAtomicUInt64:
			return true;
		case NodeType::TypeAtomicFloat32:
			return true;
		case NodeType::TypeAtomicFloat64:
			return true;
		case NodeType::TypeAtomicReal:
			return true;
		default:
			return false;
	}
#pragma clang diagnostic pop
}

bool isLiteralExpr(NodeType type) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (type) {
		case NodeType::ExprLiteralBool:
			return true;
		case NodeType::ExprLiteralInt8:
			return true;
		case NodeType::ExprLiteralInt16:
			return true;
		case NodeType::ExprLiteralInt32:
			return true;
		case NodeType::ExprLiteralInt64:
			return true;
		case NodeType::ExprLiteralUInt8:
			return true;
		case NodeType::ExprLiteralUInt16:
			return true;
		case NodeType::ExprLiteralUInt32:
			return true;
		case NodeType::ExprLiteralUInt64:
			return true;
		case NodeType::ExprLiteralChar8:
			return true;
		case NodeType::ExprLiteralChar16:
			return true;
		case NodeType::ExprLiteralChar32:
			return true;
		case NodeType::ExprLiteralFloat32:
			return true;
		case NodeType::ExprLiteralFloat64:
			return true;
		case NodeType::ExprLiteralReal:
			return true;
		default:
			return false;
	}
#pragma clang diagnostic pop
}

bool isOpExpr(NodeType type) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (type) {
		case NodeType::ExprAccessUnary:
			return true;
		case NodeType::ExprAccess:
			return true;
		case NodeType::ExprGroup:
			return true;
		case NodeType::ExprAdd:
			return true;
		case NodeType::ExprIncPre:
			return true;
		case NodeType::ExprIncPost:
			return true;
		case NodeType::ExprSub:
			return true;
		case NodeType::ExprNeg:
			return true;
		case NodeType::ExprDecPre:
			return true;
		case NodeType::ExprDecPost:
			return true;
		case NodeType::ExprMul:
			return true;
		case NodeType::ExprExp:
			return true;
		case NodeType::ExprDiv:
			return true;
		case NodeType::ExprDivInt:
			return true;
		case NodeType::ExprDivReal:
			return true;
		case NodeType::ExprMod:
			return true;
		case NodeType::ExprBitNot:
			return true;
		case NodeType::ExprBitAnd:
			return true;
		case NodeType::ExprBitOr:
			return true;
		case NodeType::ExprBitXor:
			return true;
		case NodeType::ExprBitShL:
			return true;
		case NodeType::ExprBitShR:
			return true;
		case NodeType::ExprLT:
			return true;
		case NodeType::ExprLE:
			return true;
		case NodeType::ExprGT:
			return true;
		case NodeType::ExprGE:
			return true;
		case NodeType::ExprNE:
			return true;
		case NodeType::ExprEQ:
			return true;
		case NodeType::ExprBoolNot:
			return true;
		case NodeType::ExprBoolAnd:
			return true;
		case NodeType::ExprBoolOr:
			return true;
		case NodeType::ExprBoolImplies:
			return true;
		case NodeType::ExprAddAssign:
			return true;
		case NodeType::ExprSubAssign:
			return true;
		case NodeType::ExprMulAssign:
			return true;
		case NodeType::ExprExpAssign:
			return true;
		case NodeType::ExprDivAssign:
			return true;
		case NodeType::ExprDivIntAssign:
			return true;
		case NodeType::ExprDivRealAssign:
			return true;
		case NodeType::ExprModAssign:
			return true;
		case NodeType::ExprBitAndAssign:
			return true;
		case NodeType::ExprBitOrAssign:
			return true;
		case NodeType::ExprBitXorAssign:
			return true;
		case NodeType::ExprBitShLAssign:
			return true;
		case NodeType::ExprBitShRAssign:
			return true;
		case NodeType::ExprAssign:
			return true;
		default:
			return false;
	}
#pragma clang diagnostic pop
}

Arity getExprArity(NodeType type) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch (type) {
		case NodeType::ExprAccessUnary:
			return Arity::Unary;
		case NodeType::ExprAccess:
			return Arity::NAry;
		case NodeType::ExprGroup:
			return Arity::Unary;
		case NodeType::ExprAdd:
			return Arity::NAry;
		case NodeType::ExprIncPre:
			return Arity::Unary;
		case NodeType::ExprIncPost:
			return Arity::Unary;
		case NodeType::ExprSub:
			return Arity::Binary;
		case NodeType::ExprNeg:
			return Arity::Unary;
		case NodeType::ExprDecPre:
			return Arity::Unary;
		case NodeType::ExprDecPost:
			return Arity::Unary;
		case NodeType::ExprMul:
			return Arity::NAry;
		case NodeType::ExprExp:
			return Arity::Binary;
		case NodeType::ExprDiv:
			return Arity::Binary;
		case NodeType::ExprDivInt:
			return Arity::Binary;
		case NodeType::ExprDivReal:
			return Arity::Binary;
		case NodeType::ExprMod:
			return Arity::Binary;
		case NodeType::ExprBitNot:
			return Arity::Unary;
		case NodeType::ExprBitAnd:
			return Arity::NAry;
		case NodeType::ExprBitOr:
			return Arity::NAry;
		case NodeType::ExprBitXor:
			return Arity::NAry;
		case NodeType::ExprBitShL:
			return Arity::Binary;
		case NodeType::ExprBitShR:
			return Arity::Binary;
		case NodeType::ExprLT:
			return Arity::Binary;
		case NodeType::ExprLE:
			return Arity::Binary;
		case NodeType::ExprGT:
			return Arity::Binary;
		case NodeType::ExprGE:
			return Arity::Binary;
		case NodeType::ExprNE:
			return Arity::Binary;
		case NodeType::ExprEQ:
			return Arity::Binary;
		case NodeType::ExprBoolNot:
			return Arity::Unary;
		case NodeType::ExprBoolAnd:
			return Arity::NAry;
		case NodeType::ExprBoolOr:
			return Arity::NAry;
		case NodeType::ExprBoolImplies:
			return Arity::NAry;
		case NodeType::ExprAddAssign:
			return Arity::Binary;
		case NodeType::ExprSubAssign:
			return Arity::Binary;
		case NodeType::ExprMulAssign:
			return Arity::Binary;
		case NodeType::ExprExpAssign:
			return Arity::Binary;
		case NodeType::ExprDivAssign:
			return Arity::Binary;
		case NodeType::ExprDivIntAssign:
			return Arity::Binary;
		case NodeType::ExprDivRealAssign:
			return Arity::Binary;
		case NodeType::ExprModAssign:
			return Arity::Binary;
		case NodeType::ExprBitAndAssign:
			return Arity::Binary;
		case NodeType::ExprBitOrAssign:
			return Arity::Binary;
		case NodeType::ExprBitXorAssign:
			return Arity::Binary;
		case NodeType::ExprBitShLAssign:
			return Arity::Binary;
		case NodeType::ExprBitShRAssign:
			return Arity::Binary;
		case NodeType::ExprAssign:
			return Arity::Binary;
		default:
			W_ASSERT_UNREACHABLE("node type has no arity");
	}
#pragma clang diagnostic pop
}
}
