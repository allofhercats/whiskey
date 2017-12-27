#include "Module.inc"

#include <whiskey/Printing/Precedence.hpp>

namespace whiskey {
Precedence getPrecedence(Node::Kind kind) {
	switch (kind) {
		case Node::Kind::TypeAtomicBool: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicInt8: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicInt16: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicInt32: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicInt64: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicUInt8: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicUInt16: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicUInt32: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicUInt64: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicFloat32: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicFloat64: return Precedence::TypeTerm;
		case Node::Kind::TypeAtomicReal: return Precedence::TypeTerm;
		case Node::Kind::TypeSymbol: return Precedence::TypeTerm;
		case Node::Kind::TypeGroup: return Precedence::TypeTerm;
		case Node::Kind::TypeAccessUnary: return Precedence::TypeAccessUnary;
		case Node::Kind::TypeAccess: return Precedence::TypeAccess;
		case Node::Kind::TypeFunction: return Precedence::TypeFunction;
		case Node::Kind::ExprLiteralInt: return Precedence::ExprTerm;
		case Node::Kind::ExprLiteralReal: return Precedence::ExprTerm;
		case Node::Kind::ExprSymbol: return Precedence::ExprTerm;
		case Node::Kind::ExprCall: return Precedence::ExprCall;
		case Node::Kind::ExprAccessUnary: return Precedence::ExprAccess;
		case Node::Kind::ExprAccess: return Precedence::ExprAccess;
		case Node::Kind::ExprIncPre: return Precedence::ExprUnaryRight;
		case Node::Kind::ExprIncPost: return Precedence::ExprUnaryLeft;
		case Node::Kind::ExprDecPre: return Precedence::ExprUnaryRight;
		case Node::Kind::ExprDecPost: return Precedence::ExprUnaryLeft;
		case Node::Kind::ExprNeg: return Precedence::ExprUnaryRight;
		case Node::Kind::ExprBitNot: return Precedence::ExprUnaryRight;
		case Node::Kind::ExprExp: return Precedence::ExprExp;
		case Node::Kind::ExprMul: return Precedence::ExprMul;
		case Node::Kind::ExprDiv: return Precedence::ExprMul;
		case Node::Kind::ExprDivInt: return Precedence::ExprMul;
		case Node::Kind::ExprDivReal: return Precedence::ExprMul;
		case Node::Kind::ExprAdd: return Precedence::ExprAdd;
		case Node::Kind::ExprSub: return Precedence::ExprAdd;
		case Node::Kind::ExprMod: return Precedence::ExprMod;
		case Node::Kind::ExprBitShR: return Precedence::ExprBitShR;
		case Node::Kind::ExprBitShL: return Precedence::ExprBitShL;
		case Node::Kind::ExprBitAnd: return Precedence::ExprBitAnd;
		case Node::Kind::ExprBitOr: return Precedence::ExprBitOr;
		case Node::Kind::ExprBitXor: return Precedence::ExprBitOr;
		case Node::Kind::ExprLT: return Precedence::ExprCompare;
		case Node::Kind::ExprLE: return Precedence::ExprCompare;
		case Node::Kind::ExprGT: return Precedence::ExprCompare;
		case Node::Kind::ExprGE: return Precedence::ExprCompare;
		case Node::Kind::ExprNE: return Precedence::ExprCompare;
		case Node::Kind::ExprEQ: return Precedence::ExprCompare;
		case Node::Kind::ExprBoolNot: return Precedence::ExprBoolNot;
		case Node::Kind::ExprBoolAnd: return Precedence::ExprBoolAnd;
		case Node::Kind::ExprBoolOr: return Precedence::ExprBoolOr;
		case Node::Kind::ExprBoolImplies: return Precedence::ExprBoolImplies;
		case Node::Kind::ExprExpAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprMulAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprDivAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprDivIntAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprDivRealAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprAddAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprSubAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprModAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprBitShRAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprBitShLAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprBitAndAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprBitOrAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprBitXorAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprAssign: return Precedence::ExprAssign;
		case Node::Kind::ExprGroup: return Precedence::ExprTerm;
		case Node::Kind::StmtEmpty: return Precedence::None;
		case Node::Kind::StmtExpr: return Precedence::None;
		case Node::Kind::StmtDecl: return Precedence::None;
		case Node::Kind::StmtReturn: return Precedence::None;
		case Node::Kind::StmtContinue: return Precedence::None;
		case Node::Kind::StmtBreak: return Precedence::None;
		case Node::Kind::StmtIf: return Precedence::None;
		case Node::Kind::StmtWhile: return Precedence::None;
		case Node::Kind::StmtFor: return Precedence::None;
		case Node::Kind::StmtForEach: return Precedence::None;
		case Node::Kind::StmtBlock: return Precedence::None;
		case Node::Kind::DeclVariable: return Precedence::None;
		case Node::Kind::DeclFunction: return Precedence::None;
		case Node::Kind::DeclClass: return Precedence::None;
		case Node::Kind::DeclNamespace: return Precedence::None;
		case Node::Kind::Import: return Precedence::None;
		case Node::Kind::Unit: return Precedence::None;
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
