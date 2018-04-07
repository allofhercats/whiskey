#include <whiskey/Source/TokenID.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
bool evalTokenID(const std::string &text, TokenID &value) {
  if (text == "None") {
    value = TokenID::None;
    return true;
  } else if (text == "Symbol") {
    value = TokenID::Symbol;
    return true;
  } else if (text == "KWVoid") {
    value = TokenID::KWVoid;
    return true;
  } else if (text == "KWBool") {
    value = TokenID::KWBool;
    return true;
  } else if (text == "KWInt8") {
    value = TokenID::KWInt8;
    return true;
  } else if (text == "KWInt16") {
    value = TokenID::KWInt16;
    return true;
  } else if (text == "KWInt32") {
    value = TokenID::KWInt32;
    return true;
  } else if (text == "KWInt64") {
    value = TokenID::KWInt64;
    return true;
  } else if (text == "KWUInt8") {
    value = TokenID::KWUInt8;
    return true;
  } else if (text == "KWUInt16") {
    value = TokenID::KWUInt16;
    return true;
  } else if (text == "KWUInt32") {
    value = TokenID::KWUInt32;
    return true;
  } else if (text == "KWUInt64") {
    value = TokenID::KWUInt64;
    return true;
  } else if (text == "KWFloat32") {
    value = TokenID::KWFloat32;
    return true;
  } else if (text == "KWFloat64") {
    value = TokenID::KWFloat64;
    return true;
  } else if (text == "KWReal") {
    value = TokenID::KWReal;
    return true;
  } else if (text == "KWTrue") {
    value = TokenID::KWTrue;
    return true;
  } else if (text == "KWFalse") {
    value = TokenID::KWFalse;
    return true;
  } else if (text == "KWNot") {
    value = TokenID::KWNot;
    return true;
  } else if (text == "KWAnd") {
    value = TokenID::KWAnd;
    return true;
  } else if (text == "KWOr") {
    value = TokenID::KWOr;
    return true;
  } else if (text == "KWReturn") {
    value = TokenID::KWReturn;
    return true;
  } else if (text == "KWContinue") {
    value = TokenID::KWContinue;
    return true;
  } else if (text == "KWBreak") {
    value = TokenID::KWBreak;
    return true;
  } else if (text == "KWIf") {
    value = TokenID::KWIf;
    return true;
  } else if (text == "KWElse") {
    value = TokenID::KWElse;
    return true;
  } else if (text == "KWWhile") {
    value = TokenID::KWWhile;
    return true;
  } else if (text == "KWFor") {
    value = TokenID::KWFor;
    return true;
  } else if (text == "KWForEach") {
    value = TokenID::KWForEach;
    return true;
  } else if (text == "KWClass") {
    value = TokenID::KWClass;
    return true;
  } else if (text == "KWInherits") {
    value = TokenID::KWInherits;
    return true;
  } else if (text == "KWNamespace") {
    value = TokenID::KWNamespace;
    return true;
  } else if (text == "KWImport") {
    value = TokenID::KWImport;
    return true;
  } else if (text == "Int") {
    value = TokenID::Int;
    return true;
  } else if (text == "Real") {
    value = TokenID::Real;
    return true;
  } else if (text == "Char") {
    value = TokenID::Char;
    return true;
  } else if (text == "String") {
    value = TokenID::String;
    return true;
  } else if (text == "LParen") {
    value = TokenID::LParen;
    return true;
  } else if (text == "RParen") {
    value = TokenID::RParen;
    return true;
  } else if (text == "LBracket") {
    value = TokenID::LBracket;
    return true;
  } else if (text == "RBracket") {
    value = TokenID::RBracket;
    return true;
  } else if (text == "LBrace") {
    value = TokenID::LBrace;
    return true;
  } else if (text == "RBrace") {
    value = TokenID::RBrace;
    return true;
  } else if (text == "Comma") {
    value = TokenID::Comma;
    return true;
  } else if (text == "Semicolon") {
    value = TokenID::Semicolon;
    return true;
  } else if (text == "Period") {
    value = TokenID::Period;
    return true;
  } else if (text == "Add") {
    value = TokenID::Add;
    return true;
  } else if (text == "Inc") {
    value = TokenID::Inc;
    return true;
  } else if (text == "AddAssign") {
    value = TokenID::AddAssign;
    return true;
  } else if (text == "Sub") {
    value = TokenID::Sub;
    return true;
  } else if (text == "Dec") {
    value = TokenID::Dec;
    return true;
  } else if (text == "SubAssign") {
    value = TokenID::SubAssign;
    return true;
  } else if (text == "Mul") {
    value = TokenID::Mul;
    return true;
  } else if (text == "MulAssign") {
    value = TokenID::MulAssign;
    return true;
  } else if (text == "Exp") {
    value = TokenID::Exp;
    return true;
  } else if (text == "ExpAssign") {
    value = TokenID::ExpAssign;
    return true;
  } else if (text == "Div") {
    value = TokenID::Div;
    return true;
  } else if (text == "DivAssign") {
    value = TokenID::DivAssign;
    return true;
  } else if (text == "DivInt") {
    value = TokenID::DivInt;
    return true;
  } else if (text == "DivIntAssign") {
    value = TokenID::DivIntAssign;
    return true;
  } else if (text == "DivReal") {
    value = TokenID::DivReal;
    return true;
  } else if (text == "DivRealAssign") {
    value = TokenID::DivRealAssign;
    return true;
  } else if (text == "Mod") {
    value = TokenID::Mod;
    return true;
  } else if (text == "ModAssign") {
    value = TokenID::ModAssign;
    return true;
  } else if (text == "BitNot") {
    value = TokenID::BitNot;
    return true;
  } else if (text == "BitAnd") {
    value = TokenID::BitAnd;
    return true;
  } else if (text == "BitAndAssign") {
    value = TokenID::BitAndAssign;
    return true;
  } else if (text == "BitOr") {
    value = TokenID::BitOr;
    return true;
  } else if (text == "BitOrAssign") {
    value = TokenID::BitOrAssign;
    return true;
  } else if (text == "BitXor") {
    value = TokenID::BitXor;
    return true;
  } else if (text == "BitXorAssign") {
    value = TokenID::BitXorAssign;
    return true;
  } else if (text == "BitShL") {
    value = TokenID::BitShL;
    return true;
  } else if (text == "BitShLAssign") {
    value = TokenID::BitShLAssign;
    return true;
  } else if (text == "BitShR") {
    value = TokenID::BitShR;
    return true;
  } else if (text == "BitShRAssign") {
    value = TokenID::BitShRAssign;
    return true;
  } else if (text == "LT") {
    value = TokenID::LT;
    return true;
  } else if (text == "LE") {
    value = TokenID::LE;
    return true;
  } else if (text == "GT") {
    value = TokenID::GT;
    return true;
  } else if (text == "GE") {
    value = TokenID::GE;
    return true;
  } else if (text == "NE") {
    value = TokenID::NE;
    return true;
  } else if (text == "EQ") {
    value = TokenID::EQ;
    return true;
  } else if (text == "BoolImplies") {
    value = TokenID::BoolImplies;
    return true;
  } else if (text == "Assign") {
    value = TokenID::Assign;
    return true;
  } else if (text == "LArrow") {
    value = TokenID::LArrow;
    return true;
  } else {
    return false;
  }
}

void printTokenIDDebug(std::ostream &os, TokenID value) {
  switch (value) {
  case TokenID::None:
    os << "None";
    break;
  case TokenID::Symbol:
    os << "Symbol";
    break;
  case TokenID::KWVoid:
    os << "KWVoid";
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
  case TokenID::KWVoid:
    os << "'void'";
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
