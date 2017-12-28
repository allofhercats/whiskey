#include "Module.inc"

#include <whiskey/Fuzzing/TokenFuzzerSimple.hpp>

#define SYMBOL_LENGTH_MIN 1
#define SYMBOL_LENGTH_MAX 1000

namespace whiskey {
void TokenFuzzerSimple::onFuzz() {
  while (getLength() < nChars) {
    int r = rand() % 65;
    int r2;
    int r3;
    int length;
    switch (r) {
    case 0: // symbol
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      length = (rand() % (SYMBOL_LENGTH_MAX - SYMBOL_LENGTH_MIN)) +
               SYMBOL_LENGTH_MIN;
      W_ASSERT_GT(length, 0, "Cannot have token with length 0.");
      for (int i = 0; i < length; i++) {
        r2 = rand() % 4;
        switch (r2) {
        case 0: // letter (lower)
          r3 = rand() % 26;
          emitChar('a' + r3);
          break;
        case 1: // letter (upper)
          r3 = rand() % 26;
          emitChar('A' + r3);
          break;
        case 2: // digit
          if (i > 0) {
            r3 = rand() % 10;
            emitChar('0' + r3);
            break;
          }
        case 3: // underscore
          emitChar('_');
          break;
        default:
          W_ASSERT_UNREACHABLE(
              "Reduce modulo bound for random case switch (got case " << r2
                                                                      << ").");
          break;
        }
      }
      emitToken(Token::Symbol);
      break;
    case 1:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('n');
      emitChar('o');
      emitChar('t');
      emitToken(Token::KWNot);
      break;
    case 2:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('a');
      emitChar('n');
      emitChar('d');
      emitToken(Token::KWAnd);
      break;
    case 3:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('o');
      emitChar('r');
      emitToken(Token::KWOr);
      break;
    case 4:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('r');
      emitChar('e');
      emitChar('t');
      emitChar('u');
      emitChar('r');
      emitChar('n');
      emitToken(Token::KWReturn);
      break;
    case 5:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('i');
      emitChar('f');
      emitToken(Token::KWIf);
      break;
    case 6:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('e');
      emitChar('l');
      emitChar('s');
      emitChar('e');
      emitToken(Token::KWElse);
      break;
    case 7:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('w');
      emitChar('h');
      emitChar('i');
      emitChar('l');
      emitChar('e');
      emitToken(Token::KWWhile);
      break;
    case 8:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('f');
      emitChar('o');
      emitChar('r');
      emitToken(Token::KWFor);
      break;
    case 9:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('f');
      emitChar('o');
      emitChar('r');
      emitChar('e');
      emitChar('a');
      emitChar('c');
      emitChar('h');
      emitToken(Token::KWForEach);
      break;
    case 10:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('c');
      emitChar('l');
      emitChar('a');
      emitChar('s');
      emitChar('s');
      emitToken(Token::KWClass);
      break;
    case 11:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('i');
      emitChar('n');
      emitChar('h');
      emitChar('e');
      emitChar('r');
      emitChar('i');
      emitChar('t');
      emitChar('s');
      emitToken(Token::KWInherits);
      break;
    case 12:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('n');
      emitChar('a');
      emitChar('m');
      emitChar('e');
      emitChar('s');
      emitChar('p');
      emitChar('a');
      emitChar('c');
      emitChar('e');
      emitToken(Token::KWNamespace);
      break;
    case 13:
      if (getLastChar() >= 'a' && getLastChar() <= 'z') {
        emitChar(' ');
      } else if (getLastChar() >= 'A' && getLastChar() <= 'Z') {
        emitChar(' ');
      } else if (getLastChar() >= '0' && getLastChar() <= '9') {
        emitChar(' ');
      } else if (getLastChar() == '_') {
        emitChar(' ');
      }

      emitChar('i');
      emitChar('m');
      emitChar('p');
      emitChar('o');
      emitChar('r');
      emitChar('t');
      emitToken(Token::KWImport);
      break;
    case 14: // int
      break;
    case 15: // float
      break;
    case 16: // char
      break;
    case 17: // string
      break;
    case 18:
      emitChar('(');
      emitToken(Token::LParen);
      break;
    case 19:
      emitChar(')');
      emitToken(Token::RParen);
      break;
    case 20:
      emitChar('[');
      emitToken(Token::LBracket);
      break;
    case 21:
      emitChar(']');
      emitToken(Token::RBracket);
      break;
    case 22:
      emitChar('{');
      emitToken(Token::LBrace);
      break;
    case 23:
      emitChar('}');
      emitToken(Token::RBrace);
      break;
    case 24:
      emitChar(',');
      emitToken(Token::Comma);
      break;
    case 25:
      emitChar(';');
      emitToken(Token::Semicolon);
      break;
    case 26:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('.');
      emitToken(Token::Period);
      break;
    case 27:
      if (getLastChar() == '+') {
        emitChar(' ');
      }

      emitChar('+');
      emitToken(Token::Add);
      break;
    case 28:
      if (getLastChar() == '+') {
        emitChar(' ');
      }

      emitChar('+');
      emitChar('+');
      emitToken(Token::Inc);
      break;
    case 29:
      if (getLastChar() == '+') {
        emitChar(' ');
      }

      emitChar('+');
      emitChar('=');
      emitToken(Token::AddAssign);
    case 30:
      if (getLastChar() == '-') {
        emitChar(' ');
      } else if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('-');
      emitToken(Token::Sub);
      break;
    case 31:
      if (getLastChar() == '-') {
        emitChar(' ');
      } else if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('-');
      emitChar('-');
      emitToken(Token::Dec);
      break;
    case 32:
      if (getLastChar() == '-') {
        emitChar(' ');
      } else if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('-');
      emitChar('=');
      emitToken(Token::SubAssign);
      break;
    case 33:
      if (getLastChar() == '*') {
        emitChar(' ');
      }

      emitChar('*');
      emitToken(Token::Mul);
      break;
    case 34:
      if (getLastChar() == '*') {
        emitChar(' ');
      }

      emitChar('*');
      emitChar('=');
      emitToken(Token::MulAssign);
      break;
    case 35:
      if (getLastChar() == '*') {
        emitChar(' ');
      }

      emitChar('*');
      emitChar('*');
      emitToken(Token::Exp);
      break;
    case 36:
      if (getLastChar() == '*') {
        emitChar(' ');
      }

      emitChar('*');
      emitChar('*');
      emitChar('=');
      emitToken(Token::ExpAssign);
      break;
    case 37:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('/');
      emitToken(Token::Div);
      break;
    case 38:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('/');
      emitChar('=');
      emitToken(Token::DivAssign);
      break;
    case 39:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('/');
      emitChar('/');
      emitToken(Token::DivInt);
      break;
    case 40:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('/');
      emitChar('/');
      emitChar('=');
      emitToken(Token::DivIntAssign);
      break;
    case 41:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('/');
      emitChar('.');
      emitToken(Token::DivReal);
      break;
    case 42:
      if (getLastChar() == '/') {
        emitChar(' ');
      }

      emitChar('/');
      emitChar('.');
      emitChar('=');
      emitToken(Token::DivRealAssign);
      break;
    case 43:
      emitChar('%');
      emitToken(Token::Mod);
      break;
    case 44:
      emitChar('%');
      emitChar('=');
      emitToken(Token::ModAssign);
      break;
    case 45:
      emitChar('~');
      emitToken(Token::BitNot);
      break;
    case 46:
      emitChar('&');
      emitToken(Token::BitAnd);
      break;
    case 47:
      emitChar('&');
      emitChar('=');
      emitToken(Token::BitAndAssign);
      break;
    case 48:
      emitChar('|');
      emitToken(Token::BitOr);
      break;
    case 49:
      emitChar('|');
      emitChar('=');
      emitToken(Token::BitOrAssign);
      break;
    case 50:
      emitChar('^');
      emitToken(Token::BitXor);
      break;
    case 51:
      emitChar('^');
      emitChar('=');
      emitToken(Token::BitXorAssign);
      break;
    case 52:
      if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('<');
      emitChar('<');
      emitToken(Token::BitShL);
      break;
    case 53:
      if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('<');
      emitChar('<');
      emitChar('=');
      emitToken(Token::BitShLAssign);
      break;
    case 54:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      }

      emitChar('>');
      emitChar('>');
      emitToken(Token::BitShR);
      break;
    case 55:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      }

      emitChar('>');
      emitChar('>');
      emitChar('=');
      emitToken(Token::BitShRAssign);
      break;
    case 56:
      if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('<');
      emitToken(Token::LT);
      break;
    case 57:
      if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('<');
      emitChar('=');
      emitToken(Token::LE);
      break;
    case 58:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      }

      emitChar('>');
      emitToken(Token::GT);
      break;
    case 59:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      }

      emitChar('>');
      emitChar('=');
      emitToken(Token::GE);
      break;
    case 60:
      emitChar('!');
      emitChar('=');
      emitToken(Token::NE);
      break;
    case 61:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '<') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      } else if (getLastChar() == '+') {
        emitChar(' ');
      } else if (getLastChar() == '-') {
        emitChar(' ');
      } else if (getLastChar() == '*') {
        emitChar(' ');
      } else if (getLastChar() == '/') {
        emitChar(' ');
      } else if (getLastChar() == '.') {
        emitChar(' ');
      } else if (getLastChar() == '%') {
        emitChar(' ');
      } else if (getLastChar() == '&') {
        emitChar(' ');
      } else if (getLastChar() == '|') {
        emitChar(' ');
      } else if (getLastChar() == '^') {
        emitChar(' ');
      }

      emitChar('=');
      emitChar('=');
      emitToken(Token::EQ);
      break;
    case 62:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '<') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      } else if (getLastChar() == '+') {
        emitChar(' ');
      } else if (getLastChar() == '-') {
        emitChar(' ');
      } else if (getLastChar() == '*') {
        emitChar(' ');
      } else if (getLastChar() == '/') {
        emitChar(' ');
      } else if (getLastChar() == '.') {
        emitChar(' ');
      } else if (getLastChar() == '%') {
        emitChar(' ');
      } else if (getLastChar() == '&') {
        emitChar(' ');
      } else if (getLastChar() == '|') {
        emitChar(' ');
      } else if (getLastChar() == '^') {
        emitChar(' ');
      }

      emitChar('=');
      emitChar('>');
      emitToken(Token::BoolImplies);
      break;
    case 63:
      if (getLastChar() == '=') {
        emitChar(' ');
      } else if (getLastChar() == '<') {
        emitChar(' ');
      } else if (getLastChar() == '>') {
        emitChar(' ');
      } else if (getLastChar() == '+') {
        emitChar(' ');
      } else if (getLastChar() == '-') {
        emitChar(' ');
      } else if (getLastChar() == '*') {
        emitChar(' ');
      } else if (getLastChar() == '/') {
        emitChar(' ');
      } else if (getLastChar() == '.') {
        emitChar(' ');
      } else if (getLastChar() == '%') {
        emitChar(' ');
      } else if (getLastChar() == '&') {
        emitChar(' ');
      } else if (getLastChar() == '|') {
        emitChar(' ');
      } else if (getLastChar() == '^') {
        emitChar(' ');
      }

      emitChar('=');
      emitToken(Token::Assign);
      break;
    case 64:
      if (getLastChar() == '<') {
        emitChar(' ');
      }

      emitChar('<');
      emitChar('-');
      emitToken(Token::LArrow);
      break;
    default:
      W_ASSERT_UNREACHABLE(
          "Reduce modulo bound for random case switch (got case " << r << ").");
    }
  }
}

TokenFuzzerSimple::TokenFuzzerSimple(unsigned int nChars) : nChars(nChars) {
}
} // namespace whiskey
