#ifndef __WHISKEY_Printing_Precedence_HPP
#define __WHISKEY_Printing_Precedence_HPP

#include <whiskey/Printing/Module.inc>

namespace whiskey {
enum class Precedence {
	None = -1,
	ExprAssign = 0,
	ExprBoolImplies,
	ExprBoolOr,
	ExprBoolAnd,
	ExprBoolNot,
	ExprCompare,
	ExprBitOr,
	ExprBitAnd,
	ExprBitShL,
	ExprBitShR,
	ExprMod,
	ExprAdd,
	ExprMul,
	ExprExp,
	ExprUnaryLeft,
	ExprUnaryRight,
	ExprCall,
	ExprAccess,
	ExprTerm,
	TypeFunction,
	TypeBinary,
	TypeUnary,
	TypeTerm
};

Precedence getPrecedence(AST::ID astID);
bool needsParenthesis(Precedence inner, Precedence outer);
}

#endif
