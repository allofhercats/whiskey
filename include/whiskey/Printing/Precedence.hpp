#ifndef __WHISKEY_Printing_Precedence_HPP
#define __WHISKEY_Printing_Precedence_HPP

#include <whiskey/AST/NodeType.hpp>

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
  ExprAccessUnary,
  ExprAccess,
  ExprTerm,
  TypeFunction,
  TypeAccessUnary,
  TypeAccess,
  TypeTerm
};

Precedence getPrecedence(NodeType type);
bool needsParenthesis(Precedence inner, Precedence outer);
} // namespace whiskey

#endif
