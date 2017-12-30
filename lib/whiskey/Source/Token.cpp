#include "Module.inc"

#include <whiskey/Source/Token.hpp>

namespace whiskey {
void Token::printTokenIDDebug(std::ostream &os, Token::ID value) {
  switch (value) {
  case None:
    os << "None";
    break;
  case Symbol:
    os << "Symbol";
    break;
  case KWBool:
    os << "KWBool";
    break;
  case KWInt8:
    os << "KWInt8";
    break;
  case KWInt16:
    os << "KWInt16";
    break;
  case KWInt32:
    os << "KWInt32";
    break;
  case KWInt64:
    os << "KWInt64";
    break;
  case KWUInt8:
    os << "KWUInt8";
    break;
  case KWUInt16:
    os << "KWUInt16";
    break;
  case KWUInt32:
    os << "KWUInt32";
    break;
  case KWUInt64:
    os << "KWUInt64";
    break;
  case KWFloat32:
    os << "KWFloat32";
    break;
  case KWFloat64:
    os << "KWFloat64";
    break;
  case KWReal:
    os << "KWReal";
    break;
  case KWNot:
    os << "KWNot";
    break;
  case KWAnd:
    os << "KWAnd";
    break;
  case KWOr:
    os << "KWOr";
    break;
  case KWReturn:
    os << "KWReturn";
    break;
  case KWContinue:
    os << "KWContinue";
    break;
  case KWBreak:
    os << "KWBreak";
    break;
  case KWIf:
    os << "KWIf";
    break;
  case KWElse:
    os << "KWElse";
    break;
  case KWWhile:
    os << "KWWhile";
    break;
  case KWFor:
    os << "KWFor";
    break;
  case KWForEach:
    os << "KWForEach";
    break;
  case KWClass:
    os << "KWClass";
    break;
  case KWInherits:
    os << "KWInherits";
    break;
  case KWNamespace:
    os << "KWNamespace";
    break;
  case KWImport:
    os << "KWImport";
    break;
  case Int:
    os << "Int";
    break;
  case Real:
    os << "Real";
    break;
  case Char:
    os << "Char";
    break;
  case String:
    os << "String";
    break;
  case LParen:
    os << "LParen";
    break;
  case RParen:
    os << "RParen";
    break;
  case LBracket:
    os << "LBracket";
    break;
  case RBracket:
    os << "RBracket";
    break;
  case LBrace:
    os << "LBrace";
    break;
  case RBrace:
    os << "RBrace";
    break;
  case Comma:
    os << "Comma";
    break;
  case Semicolon:
    os << "Semicolon";
    break;
  case Period:
    os << "Period";
    break;
  case Add:
    os << "Add";
    break;
  case Inc:
    os << "Inc";
    break;
  case AddAssign:
    os << "AddAssign";
    break;
  case Sub:
    os << "Sub";
    break;
  case Dec:
    os << "Dec";
    break;
  case SubAssign:
    os << "SubAssign";
    break;
  case Mul:
    os << "Mul";
    break;
  case MulAssign:
    os << "MulAssign";
    break;
  case Exp:
    os << "Exp";
    break;
  case ExpAssign:
    os << "ExpAssign";
    break;
  case Div:
    os << "Div";
    break;
  case DivAssign:
    os << "DivAssign";
    break;
  case DivInt:
    os << "DivInt";
    break;
  case DivIntAssign:
    os << "DivIntAssign";
    break;
  case DivReal:
    os << "DivReal";
    break;
  case DivRealAssign:
    os << "DivRealAssign";
    break;
  case Mod:
    os << "Mod";
    break;
  case ModAssign:
    os << "ModAssign";
    break;
  case BitNot:
    os << "BitNot";
    break;
  case BitAnd:
    os << "BitAnd";
    break;
  case BitAndAssign:
    os << "BitAndAssign";
    break;
  case BitOr:
    os << "BitOr";
    break;
  case BitOrAssign:
    os << "BitOrAssign";
    break;
  case BitXor:
    os << "BitXor";
    break;
  case BitXorAssign:
    os << "BitXorAssign";
    break;
  case BitShL:
    os << "BitShL";
    break;
  case BitShLAssign:
    os << "BitShLAssign";
    break;
  case BitShR:
    os << "BitShR";
    break;
  case BitShRAssign:
    os << "BitShRAssign";
    break;
  case LT:
    os << "LT";
    break;
  case LE:
    os << "LE";
    break;
  case GT:
    os << "GT";
    break;
  case GE:
    os << "GE";
    break;
  case NE:
    os << "NE";
    break;
  case EQ:
    os << "EQ";
    break;
  case BoolImplies:
    os << "BoolImplies";
    break;
  case Assign:
    os << "Assign";
    break;
  case LArrow:
    os << "LArrow";
    break;
  default:
    W_ASSERT_UNREACHABLE("Unsupported token ID " << (int)value << ".");
  }
}

void Token::printTokenID(std::ostream &os, Token::ID value) {
  switch (value) {
  case None:
    os << "end-of-stream";
    break;
  case Symbol:
    os << "symbol";
    break;
  case KWBool:
    os << "'bool'";
    break;
  case KWInt8:
    os << "'int8'";
    break;
  case KWInt16:
    os << "'int16'";
    break;
  case KWInt32:
    os << "'int32'";
    break;
  case KWInt64:
    os << "'int64'";
    break;
  case KWUInt8:
    os << "'uint8'";
    break;
  case KWUInt16:
    os << "'uint16'";
    break;
  case KWUInt32:
    os << "'uint32'";
    break;
  case KWUInt64:
    os << "'uint64'";
    break;
  case KWFloat32:
    os << "'float32'";
    break;
  case KWFloat64:
    os << "'float64'";
    break;
  case KWReal:
    os << "'real'";
    break;
  case KWNot:
    os << "'not'";
    break;
  case KWAnd:
    os << "'and'";
    break;
  case KWOr:
    os << "'or'";
    break;
  case KWReturn:
    os << "'return'";
    break;
  case KWContinue:
    os << "'continue'";
    break;
  case KWBreak:
    os << "'break'";
    break;
  case KWIf:
    os << "'if'";
    break;
  case KWElse:
    os << "'else'";
    break;
  case KWWhile:
    os << "'while'";
    break;
  case KWFor:
    os << "'for'";
    break;
  case KWForEach:
    os << "'foreach'";
    break;
  case KWClass:
    os << "'class'";
    break;
  case KWInherits:
    os << "'inherits'";
    break;
  case KWNamespace:
    os << "'namespace'";
    break;
  case KWImport:
    os << "'import'";
    break;
  case Int:
    os << "int";
    break;
  case Real:
    os << "real";
    break;
  case Char:
    os << "char";
    break;
  case String:
    os << "string";
    break;
  case LParen:
    os << "(";
    break;
  case RParen:
    os << ")";
    break;
  case LBracket:
    os << "[";
    break;
  case RBracket:
    os << "]";
    break;
  case LBrace:
    os << "{";
    break;
  case RBrace:
    os << "}";
    break;
  case Comma:
    os << ",";
    break;
  case Semicolon:
    os << ";";
    break;
  case Period:
    os << ".";
    break;
  case Add:
    os << "+";
    break;
  case Inc:
    os << "++";
    break;
  case AddAssign:
    os << "+=";
    break;
  case Sub:
    os << "-";
    break;
  case Dec:
    os << "--";
    break;
  case SubAssign:
    os << "-=";
    break;
  case Mul:
    os << "*";
    break;
  case MulAssign:
    os << "*=";
    break;
  case Exp:
    os << "**";
    break;
  case ExpAssign:
    os << "**=";
    break;
  case Div:
    os << "/";
    break;
  case DivAssign:
    os << "/=";
    break;
  case DivInt:
    os << "//";
    break;
  case DivIntAssign:
    os << "//=";
    break;
  case DivReal:
    os << "/.";
    break;
  case DivRealAssign:
    os << "/.=";
    break;
  case Mod:
    os << "%";
    break;
  case ModAssign:
    os << "%=";
    break;
  case BitNot:
    os << "~";
    break;
  case BitAnd:
    os << "&";
    break;
  case BitAndAssign:
    os << "&=";
    break;
  case BitOr:
    os << "|";
    break;
  case BitOrAssign:
    os << "|=";
    break;
  case BitXor:
    os << "^";
    break;
  case BitXorAssign:
    os << "^=";
    break;
  case BitShL:
    os << "<<";
    break;
  case BitShLAssign:
    os << "<<=";
    break;
  case BitShR:
    os << ">>";
    break;
  case BitShRAssign:
    os << ">>=";
    break;
  case LT:
    os << "<";
    break;
  case LE:
    os << "<=";
    break;
  case GT:
    os << ">";
    break;
  case GE:
    os << ">=";
    break;
  case NE:
    os << "!=";
    break;
  case EQ:
    os << "==";
    break;
  case BoolImplies:
    os << "=>";
    break;
  case Assign:
    os << "=";
    break;
  case LArrow:
    os << "<-";
    break;
  default:
    W_ASSERT_UNREACHABLE("Unsupported token ID " << (int)value << ".");
  }
}

void Token::printDebug(std::ostream &os, const Token &token) {
  token.printDebug(os);
}

void Token::printDebug(std::ostream &os, const std::vector<Token> &tokens) {
  for (const Token &i : tokens) {
    i.printDebug(os);
    os << "\n";
  }
}

Token::Token(Token::ID id) : id(id) {
}

Token::Token(Range range, Token::ID id) : range(range), id(id) {
}

bool Token::isGood() const {
  return id != None;
}

Range &Token::getRange() {
  return range;
}

const Range &Token::getRange() const {
  return range;
}

void Token::setRange(Range value) {
  range = value;
}

Token::ID Token::getID() const {
  return id;
}

void Token::setID(Token::ID value) {
  id = value;
}

void Token::printDebug(std::ostream &os) const {
  if (range.getStart().hasPath()) {
    os << range.getStart().getPath() << ":";
    if (range.getStart().hasLine()) {
      os << range.getStart().getLine() << ":";
      if (range.getStart().hasColumn()) {
        os << range.getStart().getColumn() << ":";
      }
    }
    os << " ";
  }

  printTokenIDDebug(os, id);

  os << " ";

  printLiteralString(os, range.getText());
}
} // namespace whiskey
