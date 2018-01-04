#ifndef __WHISKEY_Source_Token_HPP
#define __WHISKEY_Source_Token_HPP

#include <vector>

#include <whiskey/Source/Range.hpp>

namespace whiskey {
class Token {
public:
  enum ID {
    None,
    Symbol,
    KWBool,
    KWInt8,
    KWInt16,
    KWInt32,
    KWInt64,
    KWUInt8,
    KWUInt16,
    KWUInt32,
    KWUInt64,
    KWFloat32,
    KWFloat64,
    KWReal,
    KWNot,
    KWAnd,
    KWOr,
    KWReturn,
    KWContinue,
    KWBreak,
    KWIf,
    KWElse,
    KWWhile,
    KWFor,
    KWForEach,
    KWClass,
    KWInherits,
    KWNamespace,
    KWImport,
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

  static void printTokenIDDebug(std::ostream &os, ID value);
  static void printTokenID(std::ostream &os, ID value);

private:
  Range range;
  ID id;

public:
  static void printDebug(std::ostream &os, const Token &token);
  static void printDebug(std::ostream &os, const std::vector<Token> &tokens);

  Token(ID id = None);
  Token(Range range, ID id = None);

  bool isGood() const;

  Range &getRange();
  const Range &getRange() const;
  void setRange(Range value);

  ID getID() const;
  void setID(ID value);

  void printDebug(std::ostream &os) const;
};
} // namespace whiskey

#endif
