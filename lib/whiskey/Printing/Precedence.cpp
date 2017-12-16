#include "Module.inc"

#include <whiskey/Printing/Precedence.hpp>

namespace whiskey {
Precedence getPrecedence(AST::ID astID) {
	switch (astID) {
		case AST::ID::TypeAtomicBool: return Precedence::None;
		case AST::ID::TypeAtomicInt8: return Precedence::None;
		case AST::ID::TypeAtomicInt16: return Precedence::None;
		case AST::ID::TypeAtomicInt32: return Precedence::None;
		case AST::ID::TypeAtomicInt64: return Precedence::None;
		case AST::ID::TypeAtomicUInt8: return Precedence::None;
		case AST::ID::TypeAtomicUInt16: return Precedence::None;
		case AST::ID::TypeAtomicUInt32: return Precedence::None;
		case AST::ID::TypeAtomicUInt64: return Precedence::None;
		case AST::ID::TypeAtomicFloat32: return Precedence::None;
		case AST::ID::TypeAtomicFloat64: return Precedence::None;
		case AST::ID::TypeAtomicReal: return Precedence::None;
		case AST::ID::TypeSymbol: return Precedence::None;
		case AST::ID::TypeAccessUnary: return Precedence::None;
		case AST::ID::TypeAccessBinary: return Precedence::None;
		case AST::ID::TypeFunction: return Precedence::None;
		case AST::ID::ExprLiteralInt: return Precedence::ExprTerm;
		case AST::ID::ExprLiteralFloat: return Precedence::ExprTerm;
		case AST::ID::ExprSymbol: return Precedence::ExprTerm;
		case AST::ID::ExprCall: return Precedence::ExprCall;
		case AST::ID::ExprAccessUnary: return Precedence::ExprAccess;
		case AST::ID::ExprAccessBinary: return Precedence::ExprAccess;
		case AST::ID::ExprIncPre: return Precedence::ExprUnaryRight;
		case AST::ID::ExprIncPost: return Precedence::ExprUnaryLeft;
		case AST::ID::ExprDecPre: return Precedence::ExprUnaryRight;
		case AST::ID::ExprDecPost: return Precedence::ExprUnaryLeft;
		case AST::ID::ExprNegate: return Precedence::ExprUnaryRight;
		case AST::ID::ExprBitNot: return Precedence::ExprUnaryRight;
		case AST::ID::ExprExp: return Precedence::ExprExp;
		case AST::ID::ExprMul: return Precedence::ExprMul;
		case AST::ID::ExprDiv: return Precedence::ExprMul;
		case AST::ID::ExprDivInt: return Precedence::ExprMul;
		case AST::ID::ExprDivReal: return Precedence::ExprMul;
		case AST::ID::ExprAdd: return Precedence::ExprAdd;
		case AST::ID::ExprSub: return Precedence::ExprAdd;
		case AST::ID::ExprMod: return Precedence::ExprMod;
		case AST::ID::ExprBitShR: return Precedence::ExprBitShR;
		case AST::ID::ExprBitShL: return Precedence::ExprBitShL;
		case AST::ID::ExprBitAnd: return Precedence::ExprBitAnd;
		case AST::ID::ExprBitOr: return Precedence::ExprBitOr;
		case AST::ID::ExprBitXor: return Precedence::ExprBitOr;
		case AST::ID::ExprLT: return Precedence::ExprCompare;
		case AST::ID::ExprLE: return Precedence::ExprCompare;
		case AST::ID::ExprGT: return Precedence::ExprCompare;
		case AST::ID::ExprGE: return Precedence::ExprCompare;
		case AST::ID::ExprNE: return Precedence::ExprCompare;
		case AST::ID::ExprEQ: return Precedence::ExprCompare;
		case AST::ID::ExprBoolNot: return Precedence::ExprBoolNot;
		case AST::ID::ExprBoolAnd: return Precedence::ExprBoolAnd;
		case AST::ID::ExprBoolOr: return Precedence::ExprBoolOr;
		case AST::ID::ExprBoolImplies: return Precedence::ExprBoolImplies;
		case AST::ID::ExprGroup: return Precedence::ExprTerm;
		case AST::ID::StmtEmpty: return Precedence::None;
		case AST::ID::StmtExpr: return Precedence::None;
		case AST::ID::StmtExprReturn: return Precedence::None;
		case AST::ID::StmtIf: return Precedence::None;
		case AST::ID::StmtWhile: return Precedence::None;
		case AST::ID::StmtFor: return Precedence::None;
		case AST::ID::StmtForEach: return Precedence::None;
		case AST::ID::StmtBlock: return Precedence::None;
		case AST::ID::DeclVariable: return Precedence::None;
		case AST::ID::DeclFunction: return Precedence::None;
		case AST::ID::DeclClass: return Precedence::None;
		case AST::ID::DeclNamespace: return Precedence::None;
		case AST::ID::Import: return Precedence::None;
	}
}

bool needsParenthesis(Precedence inner, Precedence outer) {
	if (inner == Precedence::None || outer == Precedence::None) {
		return false;
	} else {
		return inner < outer;
	}
}
}
