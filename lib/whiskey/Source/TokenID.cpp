#include <whiskey/Source/TokenID.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void printTokenIDDebug(std::ostream &os, TokenID value) {
  switch (value) {
  case TokenID::None:
    os << "None";
    break;
  case TokenID::Symbol:
    os << "Symbol";
    break;
  case TokenID::KWBool:
    os << "KWBool";
    break;
  case TokenID::KWInt8:
    os << "KWInt8";
    break;
  case TokenID::KWInt16:
    os << "KWInt16";
    break;
  case TokenID::KWInt32:
    os << "KWInt32";
    break;
  case TokenID::KWInt64:
    os << "KWInt64";
    break;
  case TokenID::KWUInt8:
    os << "KWUInt8";
    break;
  case TokenID::KWUInt16:
    os << "KWUInt16";
    break;
  case TokenID::KWUInt32:
    os << "KWUInt32";
    break;
  case TokenID::KWUInt64:
    os << "KWUInt64";
    break;
  case TokenID::KWFloat32:
    os << "KWFloat32";
    break;
  case TokenID::KWFloat64:
    os << "KWFloat64";
    break;
  case TokenID::KWReal:
    os << "KWReal";
    break;
  case TokenID::KWTrue:
    os << "KWTrue";
    break;
  case TokenID::KWFalse:
    os << "KWFalse";
    break;
  case TokenID::KWNot:
    os << "KWNot";
    break;
  case TokenID::KWAnd:
    os << "KWAnd";
    break;
  case TokenID::KWOr:
    os << "KWOr";
    break;
  case TokenID::KWReturn:
    os << "KWReturn";
    break;
  case TokenID::KWContinue:
    os << "KWContinue";
    break;
  case TokenID::KWBreak:
    os << "KWBreak";
    break;
  case TokenID::KWIf:
    os << "KWIf";
    break;
  case TokenID::KWElse:
    os << "KWElse";
    break;
  case TokenID::KWWhile:
    os << "KWWhile";
    break;
  case TokenID::KWFor:
    os << "KWFor";
    break;
  case TokenID::KWForEach:
    os << "KWForEach";
    break;
  case TokenID::KWClass:
    os << "KWClass";
    break;
  case TokenID::KWInherits:
    os << "KWInherits";
    break;
  case TokenID::KWNamespace:
    os << "KWNamespace";
    break;
  case TokenID::KWImport:
    os << "KWImport";
    break;
  case TokenID::Int:
    os << "Int";
    break;
  case TokenID::Real:
    os << "Real";
    break;
  case TokenID::Char:
    os << "Char";
    break;
  case TokenID::String:
    os << "String";
    break;
  case TokenID::LParen:
    os << "LParen";
    break;
  case TokenID::RParen:
    os << "RParen";
    break;
  case TokenID::LBracket:
    os << "LBracket";
    break;
  case TokenID::RBracket:
    os << "RBracket";
    break;
  case TokenID::LBrace:
    os << "LBrace";
    break;
  case TokenID::RBrace:
    os << "RBrace";
    break;
  case TokenID::Comma:
    os << "Comma";
    break;
  case TokenID::Semicolon:
    os << "Semicolon";
    break;
  case TokenID::Period:
    os << "Period";
    break;
  case TokenID::Add:
    os << "Add";
    break;
  case TokenID::Inc:
    os << "Inc";
    break;
  case TokenID::AddAssign:
    os << "AddAssign";
    break;
  case TokenID::Sub:
    os << "Sub";
    break;
  case TokenID::Dec:
    os << "Dec";
    break;
  case TokenID::SubAssign:
    os << "SubAssign";
    break;
  case TokenID::Mul:
    os << "Mul";
    break;
  case TokenID::MulAssign:
    os << "MulAssign";
    break;
  case TokenID::Exp:
    os << "Exp";
    break;
  case TokenID::ExpAssign:
    os << "ExpAssign";
    break;
  case TokenID::Div:
    os << "Div";
    break;
  case TokenID::DivAssign:
    os << "DivAssign";
    break;
  case TokenID::DivInt:
    os << "DivInt";
    break;
  case TokenID::DivIntAssign:
    os << "DivIntAssign";
    break;
  case TokenID::DivReal:
    os << "DivReal";
    break;
  case TokenID::DivRealAssign:
    os << "DivRealAssign";
    break;
  case TokenID::Mod:
    os << "Mod";
    break;
  case TokenID::ModAssign:
    os << "ModAssign";
    break;
  case TokenID::BitNot:
    os << "BitNot";
    break;
  case TokenID::BitAnd:
    os << "BitAnd";
    break;
  case TokenID::BitAndAssign:
    os << "BitAndAssign";
    break;
  case TokenID::BitOr:
    os << "BitOr";
    break;
  case TokenID::BitOrAssign:
    os << "BitOrAssign";
    break;
  case TokenID::BitXor:
    os << "BitXor";
    break;
  case TokenID::BitXorAssign:
    os << "BitXorAssign";
    break;
  case TokenID::BitShL:
    os << "BitShL";
    break;
  case TokenID::BitShLAssign:
    os << "BitShLAssign";
    break;
  case TokenID::BitShR:
    os << "BitShR";
    break;
  case TokenID::BitShRAssign:
    os << "BitShRAssign";
    break;
  case TokenID::LT:
    os << "LT";
    break;
  case TokenID::LE:
    os << "LE";
    break;
  case TokenID::GT:
    os << "GT";
    break;
  case TokenID::GE:
    os << "GE";
    break;
  case TokenID::NE:
    os << "NE";
    break;
  case TokenID::EQ:
    os << "EQ";
    break;
  case TokenID::BoolImplies:
    os << "BoolImplies";
    break;
  case TokenID::Assign:
    os << "Assign";
    break;
  case TokenID::LArrow:
    os << "LArrow";
    break;
  }
}

void printTokenID(std::ostream &os, TokenID value) {
  switch (value) {
  case TokenID::None:
    os << "end-of-stream";
    break;
  case TokenID::Symbol:
    os << "symbol";
    break;
  case TokenID::KWBool:
    os << "'bool'";
    break;
  case TokenID::KWInt8:
    os << "'int8'";
    break;
  case TokenID::KWInt16:
    os << "'int16'";
    break;
  case TokenID::KWInt32:
    os << "'int32'";
    break;
  case TokenID::KWInt64:
    os << "'int64'";
    break;
  case TokenID::KWUInt8:
    os << "'uint8'";
    break;
  case TokenID::KWUInt16:
    os << "'uint16'";
    break;
  case TokenID::KWUInt32:
    os << "'uint32'";
    break;
  case TokenID::KWUInt64:
    os << "'uint64'";
    break;
  case TokenID::KWFloat32:
    os << "'float32'";
    break;
  case TokenID::KWFloat64:
    os << "'float64'";
    break;
  case TokenID::KWReal:
    os << "'real'";
    break;
  case TokenID::KWTrue:
    os << "'true'";
    break;
  case TokenID::KWFalse:
    os << "'false'";
    break;
  case TokenID::KWNot:
    os << "'not'";
    break;
  case TokenID::KWAnd:
    os << "'and'";
    break;
  case TokenID::KWOr:
    os << "'or'";
    break;
  case TokenID::KWReturn:
    os << "'return'";
    break;
  case TokenID::KWContinue:
    os << "'continue'";
    break;
  case TokenID::KWBreak:
    os << "'break'";
    break;
  case TokenID::KWIf:
    os << "'if'";
    break;
  case TokenID::KWElse:
    os << "'else'";
    break;
  case TokenID::KWWhile:
    os << "'while'";
    break;
  case TokenID::KWFor:
    os << "'for'";
    break;
  case TokenID::KWForEach:
    os << "'foreach'";
    break;
  case TokenID::KWClass:
    os << "'class'";
    break;
  case TokenID::KWInherits:
    os << "'inherits'";
    break;
  case TokenID::KWNamespace:
    os << "'namespace'";
    break;
  case TokenID::KWImport:
    os << "'import'";
    break;
  case TokenID::Int:
    os << "int";
    break;
  case TokenID::Real:
    os << "real";
    break;
  case TokenID::Char:
    os << "char";
    break;
  case TokenID::String:
    os << "string";
    break;
  case TokenID::LParen:
    os << "(";
    break;
  case TokenID::RParen:
    os << ")";
    break;
  case TokenID::LBracket:
    os << "[";
    break;
  case TokenID::RBracket:
    os << "]";
    break;
  case TokenID::LBrace:
    os << "{";
    break;
  case TokenID::RBrace:
    os << "}";
    break;
  case TokenID::Comma:
    os << ",";
    break;
  case TokenID::Semicolon:
    os << ";";
    break;
  case TokenID::Period:
    os << ".";
    break;
  case TokenID::Add:
    os << "+";
    break;
  case TokenID::Inc:
    os << "++";
    break;
  case TokenID::AddAssign:
    os << "+=";
    break;
  case TokenID::Sub:
    os << "-";
    break;
  case TokenID::Dec:
    os << "--";
    break;
  case TokenID::SubAssign:
    os << "-=";
    break;
  case TokenID::Mul:
    os << "*";
    break;
  case TokenID::MulAssign:
    os << "*=";
    break;
  case TokenID::Exp:
    os << "**";
    break;
  case TokenID::ExpAssign:
    os << "**=";
    break;
  case TokenID::Div:
    os << "/";
    break;
  case TokenID::DivAssign:
    os << "/=";
    break;
  case TokenID::DivInt:
    os << "//";
    break;
  case TokenID::DivIntAssign:
    os << "//=";
    break;
  case TokenID::DivReal:
    os << "/.";
    break;
  case TokenID::DivRealAssign:
    os << "/.=";
    break;
  case TokenID::Mod:
    os << "%";
    break;
  case TokenID::ModAssign:
    os << "%=";
    break;
  case TokenID::BitNot:
    os << "~";
    break;
  case TokenID::BitAnd:
    os << "&";
    break;
  case TokenID::BitAndAssign:
    os << "&=";
    break;
  case TokenID::BitOr:
    os << "|";
    break;
  case TokenID::BitOrAssign:
    os << "|=";
    break;
  case TokenID::BitXor:
    os << "^";
    break;
  case TokenID::BitXorAssign:
    os << "^=";
    break;
  case TokenID::BitShL:
    os << "<<";
    break;
  case TokenID::BitShLAssign:
    os << "<<=";
    break;
  case TokenID::BitShR:
    os << ">>";
    break;
  case TokenID::BitShRAssign:
    os << ">>=";
    break;
  case TokenID::LT:
    os << "<";
    break;
  case TokenID::LE:
    os << "<=";
    break;
  case TokenID::GT:
    os << ">";
    break;
  case TokenID::GE:
    os << ">=";
    break;
  case TokenID::NE:
    os << "!=";
    break;
  case TokenID::EQ:
    os << "==";
    break;
  case TokenID::BoolImplies:
    os << "=>";
    break;
  case TokenID::Assign:
    os << "=";
    break;
  case TokenID::LArrow:
    os << "<-";
    break;
  }
}
}
