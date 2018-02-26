#ifndef __WHISKEY_Source_TokenID_HPP
#define __WHISKEY_Source_TokenID_HPP

#include <ostream>

namespace whiskey {
enum class TokenID {
  None,
  Symbol,
  Int,
  Real,
  Char,
  String,
  LParen,
  RParen,
  LBracket,
  RBracket,
  LBrace,
  RBrace,
  Comma,
  Semicolon,
  Period,
  Add,
  Inc,
  AddAssign,
  Sub,
  Dec,
  SubAssign,
  Mul,
  MulAssign,
  Exp,
  ExpAssign,
  Div,
  DivAssign,
  DivInt,
  DivIntAssign,
  DivReal,
  DivRealAssign,
  Mod,
  ModAssign,
  BitNot,
  BitAnd,
  BitAndAssign,
  BitOr,
  BitOrAssign,
  BitXor,
  BitXorAssign,
  BitShL,
  BitShLAssign,
  BitShR,
  BitShRAssign,
  LT,
  LE,
  GT,
  GE,
  NE,
  EQ,
  BoolImplies,
  Assign,
  LArrow
};

void printTokenIDDebug(std::ostream &os, TokenID value);
void printTokenID(std::ostream &os, TokenID value);
}

#endif
