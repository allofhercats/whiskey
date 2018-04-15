#include <whiskey/Lexing/UnLexUtils.hpp>

#include <sstream>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
namespace {
bool isJoinConflict(char left, char right) {
  if ((left >= 'a' && left <= 'z') || (left >= 'A' && left <= 'Z') || (left >= '0' && left <= '9') || left >= '\x80' || left == '_') {
    return (right >= 'a' && right <= 'z') || (right >= 'A' && right <= 'Z') || (right >= '0' && right <= '9') || right >= '\x80' || right == '_';
  } else if (left == '%' || left == '^' || left == '&' || left == '*' || left == '-' || left == '+' || left == '=' || left == '<' || left == '.' || left == '>' || left == '/') {
    return right == '%' || right == '^' || right == '&' || right == '*' || right == '-' || right == '+' || right == '=' || right == '<' || right == '.' || right == '>' || right == '/';
  } else {
    return false;
  }
}
}

std::string getSourceFromTokens(const std::vector<Token> &tokens) {
	std::stringstream ss;
  char last = 0;

  for (const Token &i : tokens) {
    W_ASSERT_NE(i.getID(), TokenID::None, "Cannot join token of ID 'None'.");

    std::string text;
    if (i.getID() == TokenID::Symbol
      || i.getID() == TokenID::KWVoid
      || i.getID() == TokenID::KWBool
      || i.getID() == TokenID::KWInt8
      || i.getID() == TokenID::KWInt16
      || i.getID() == TokenID::KWInt32
      || i.getID() == TokenID::KWInt64
      || i.getID() == TokenID::KWUInt8
      || i.getID() == TokenID::KWUInt16
      || i.getID() == TokenID::KWUInt32
      || i.getID() == TokenID::KWUInt64
      || i.getID() == TokenID::KWFloat32
      || i.getID() == TokenID::KWFloat64
      || i.getID() == TokenID::KWReal
      || i.getID() == TokenID::KWTrue
      || i.getID() == TokenID::KWFalse
      || i.getID() == TokenID::KWNot
      || i.getID() == TokenID::KWAnd
      || i.getID() == TokenID::KWOr
      || i.getID() == TokenID::KWReturn
      || i.getID() == TokenID::KWContinue
      || i.getID() == TokenID::KWBreak
      || i.getID() == TokenID::KWIf
      || i.getID() == TokenID::KWElse
      || i.getID() == TokenID::KWWhile
      || i.getID() == TokenID::KWFor
      || i.getID() == TokenID::KWForEach
      || i.getID() == TokenID::KWClass
      || i.getID() == TokenID::KWInherits
      || i.getID() == TokenID::KWNamespace
      || i.getID() == TokenID::KWImport
      || i.getID() == TokenID::Int
      || i.getID() == TokenID::Real
      || i.getID() == TokenID::Char
      || i.getID() == TokenID::String) {
      text = i.getText();
    } else {
      std::stringstream ss2;
      printTokenID(ss2, i.getID());
      text = ss2.str();
    }

    W_ASSERT_GT(text.size(), 0u, "Cannot join token with empty text.");

    if (last != 0 && isJoinConflict(last, text.front())) {
      ss << ' ';
    }

    last = text.back();

    ss << text;
  }

  return ss.str();
}

// std::string stripUneededFromSource(const std::string &text, bool stripComments) {
// 	std::stringstream ss;
// 	std::string::const_iterator pos = text.cbegin();
// 	char last = 0;

// 	while (pos != text.cend()) {
// 		if (stripComments && *pos == '#') {
// 			while (*pos != '\n' && pos != text.cend()) {
// 				last = *pos++;
// 			}
// 		} else if (stripComments && (last == '#' && *pos == '{')) {
// 			while (pos != text.cend()) {
// 				if (last == '}' && *pos == '#') {
// 					last = *pos++;
// 					break;
// 				}
// 				*pos++;
// 			}
// 		}

// 		if (*pos != ' ' && *pos != '\t' && *pos != '\n' && *pos != '\r') {
// 			if (last != 0 && isJoinConflict(last, *pos)) {
// 				ss << ' ';
// 			} else {
// 				ss << *pos;
// 				last = *pos++;
// 			}
// 		} else {
// 			pos++;
// 		}
// 	}

// 	return ss.str();
// }
}
