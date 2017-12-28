#include "Module.inc"

#include <whiskey/Lexing/Lexer.hpp>

namespace whiskey {
bool Lexer::isWhitespaceChar(char32_t value) {
  return value == ' ' || value == '\t' || value == '\n';
}

bool Lexer::isSymbolCharFirst(char32_t value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z') ||
         value >= '\x80' || value == '_';
}

bool Lexer::isSymbolChar(char32_t value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z') ||
         (value >= '0' && value <= '9') || value >= '\x80' || value == '_';
}

bool Lexer::isNumericCharFirst(char32_t value) {
  return (value >= '0' && value <= '9');
}

bool Lexer::isNumericChar(char32_t value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z') ||
         (value >= '0' && value <= '9') || value == '_';
}

Lexer::Lexer(Location start, std::vector<Token> &tokens, MessageBuffer &msgs)
    : ctx(start, tokens, msgs) {
}

void Lexer::lex() {
  while (ctx.areMoreChars()) {
    if (isWhitespaceChar(ctx.getChar())) {
      ctx.eatChar();
      ctx.skipToken();
    } else if (ctx.getChar() == '#') {
      ctx.eatChar();
      if (ctx.getChar() == '{') {
        char32_t last = 0;
        int level = 1;
        while (ctx.areMoreChars()) {
          if (last == '}' && ctx.getChar() == '#') {
            last = ctx.eatChar();
            level--;
            if (level <= 0) {
              break;
            }
          } else if (last == '#' && ctx.getChar() == '{') {
            last = ctx.eatChar();
            level++;
          } else {
            last = ctx.eatChar();
          }
        }
        if (level > 0) {
          ctx.getMsgs().describe() << "#{ expects closing }#";
          ctx.getMsgs().emit(ctx.getRange(), Message::MismatchedBlockComments);
          ctx.skipToken();
        }
      } else {
        while (ctx.areMoreChars()) {
          if (ctx.getChar() == '\n') {
            break;
          } else {
            ctx.eatChar();
          }
        }
      }
      ctx.skipToken();
    } else if (isSymbolCharFirst(ctx.getChar())) {
      ctx.eatChar();
      while (ctx.areMoreChars()) {
        if (!isSymbolChar(ctx.getChar())) {
          break;
        } else {
          ctx.eatChar();
        }
      }
      while (ctx.areMoreChars()) {
        if (ctx.getChar() != '\'') {
          break;
        } else {
          ctx.eatChar();
        }
      }
      if (ctx.hasText("not")) {
        ctx.emitToken(Token::KWNot);
      } else if (ctx.hasText("and")) {
        ctx.emitToken(Token::KWAnd);
      } else if (ctx.hasText("or")) {
        ctx.emitToken(Token::KWOr);
      } else if (ctx.hasText("return")) {
        ctx.emitToken(Token::KWReturn);
      } else if (ctx.hasText("continue")) {
        ctx.emitToken(Token::KWContinue);
      } else if (ctx.hasText("break")) {
        ctx.emitToken(Token::KWBreak);
      } else if (ctx.hasText("if")) {
        ctx.emitToken(Token::KWIf);
      } else if (ctx.hasText("else")) {
        ctx.emitToken(Token::KWElse);
      } else if (ctx.hasText("while")) {
        ctx.emitToken(Token::KWWhile);
      } else if (ctx.hasText("for")) {
        ctx.emitToken(Token::KWFor);
      } else if (ctx.hasText("foreach")) {
        ctx.emitToken(Token::KWForEach);
      } else if (ctx.hasText("class")) {
        ctx.emitToken(Token::KWClass);
      } else if (ctx.hasText("inherits")) {
        ctx.emitToken(Token::KWInherits);
      } else if (ctx.hasText("namespace")) {
        ctx.emitToken(Token::KWNamespace);
      } else if (ctx.hasText("import")) {
        ctx.emitToken(Token::KWImport);
      } else {
        ctx.emitToken(Token::Symbol);
      }
    } else if (isNumericCharFirst(ctx.getChar())) {
      ctx.eatChar();
      while (ctx.areMoreChars()) {
        if (!isNumericChar(ctx.getChar())) {
          break;
        } else {
          ctx.eatChar();
        }
      }
      if (ctx.getChar() == '.') {
        if (isNumericCharFirst(ctx.getChar(1))) {
          ctx.eatChar();
          while (ctx.areMoreChars()) {
            if (!isNumericChar(ctx.getChar())) {
              break;
            } else {
              ctx.eatChar();
            }
          }
          ctx.emitToken(Token::Real);
        } else {
          ctx.emitToken(Token::Int);
        }
      } else {
        ctx.emitToken(Token::Int);
      }
    } else if (ctx.getChar() == '\'') {
      ctx.eatChar();
      char32_t last[2] = {0, 0};
      bool endedCorrectly = false;
      while (ctx.areMoreChars()) {
        if (ctx.getChar() == '\'' && !(last[0] != '\\' && last[1] == '\\')) {
          ctx.eatChar();
          endedCorrectly = true;
          break;
        } else {
          last[0] = last[1];
          last[1] = ctx.eatChar();
        }
      }
      if (!endedCorrectly) {
        ctx.getMsgs().describe() << "' expects closing '";
        ctx.getMsgs().emit(ctx.getRange(), Message::MismatchedSingleQuotes);
        ctx.skipToken();
      } else {
        ctx.emitToken(Token::Char);
      }
    } else if (ctx.getChar() == '\"') {
      ctx.eatChar();
      char32_t last[2] = {0, 0};
      bool endedCorrectly = false;
      while (ctx.areMoreChars()) {
        if (ctx.getChar() == '\"' && !(last[0] != '\\' && last[1] == '\\')) {
          ctx.eatChar();
          endedCorrectly = true;
          break;
        } else {
          last[0] = last[1];
          last[1] = ctx.eatChar();
        }
      }
      if (!endedCorrectly) {
        ctx.getMsgs().describe() << "\" expects closing \"";
        ctx.getMsgs().emit(ctx.getRange(), Message::MismatchedDoubleQuotes);
        ctx.skipToken();
      } else {
        ctx.emitToken(Token::String);
      }
    } else if (ctx.getChar() == '(') {
      ctx.eatChar();
      ctx.emitToken(Token::LParen);
    } else if (ctx.getChar() == ')') {
      ctx.eatChar();
      ctx.emitToken(Token::RParen);
    } else if (ctx.getChar() == '[') {
      ctx.eatChar();
      ctx.emitToken(Token::LBracket);
    } else if (ctx.getChar() == ']') {
      ctx.eatChar();
      ctx.emitToken(Token::RBracket);
    } else if (ctx.getChar() == '{') {
      ctx.eatChar();
      ctx.emitToken(Token::LBrace);
    } else if (ctx.getChar() == '}') {
      ctx.eatChar();
      ctx.emitToken(Token::RBrace);
    } else if (ctx.getChar() == ',') {
      ctx.eatChar();
      ctx.emitToken(Token::Comma);
    } else if (ctx.getChar() == ';') {
      ctx.eatChar();
      ctx.emitToken(Token::Semicolon);
    } else if (ctx.getChar() == '.') {
      ctx.eatChar();
      if (isNumericCharFirst(ctx.getChar())) {
        ctx.eatChar();
        while (ctx.areMoreChars()) {
          if (!isNumericChar(ctx.getChar())) {
            break;
          } else {
            ctx.eatChar();
          }
        }
        ctx.emitToken(Token::Real);
      } else {
        ctx.emitToken(Token::Period);
      }
    } else if (ctx.getChar() == '+') {
      ctx.eatChar();
      if (ctx.getChar() == '+') {
        ctx.eatChar();
        ctx.emitToken(Token::Inc);
      } else if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::AddAssign);
      } else {
        ctx.emitToken(Token::Add);
      }
    } else if (ctx.getChar() == '-') {
      ctx.eatChar();
      if (ctx.getChar() == '-') {
        ctx.eatChar();
        ctx.emitToken(Token::Dec);
      } else if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::SubAssign);
      } else {
        ctx.emitToken(Token::Sub);
      }
    } else if (ctx.getChar() == '*') {
      ctx.eatChar();
      if (ctx.getChar() == '*') {
        ctx.eatChar();
        if (ctx.getChar() == '=') {
          ctx.eatChar();
          ctx.emitToken(Token::ExpAssign);
        } else {
          ctx.emitToken(Token::Exp);
        }
      } else if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::MulAssign);
      } else {
        ctx.emitToken(Token::Mul);
      }
    } else if (ctx.getChar() == '/') {
      ctx.eatChar();
      if (ctx.getChar() == '/') {
        ctx.eatChar();
        if (ctx.getChar() == '=') {
          ctx.eatChar();
          ctx.emitToken(Token::DivIntAssign);
        } else {
          ctx.emitToken(Token::DivInt);
        }
      } else if (ctx.getChar() == '.') {
        ctx.eatChar();
        if (ctx.getChar() == '=') {
          ctx.eatChar();
          ctx.emitToken(Token::DivRealAssign);
        } else {
          ctx.emitToken(Token::DivReal);
        }
      } else if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::DivAssign);
      } else {
        ctx.emitToken(Token::Div);
      }
    } else if (ctx.getChar() == '%') {
      ctx.eatChar();
      if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::ModAssign);
      } else {
        ctx.emitToken(Token::Mod);
      }
    } else if (ctx.getChar() == '~') {
      ctx.eatChar();
      ctx.emitToken(Token::BitNot);
    } else if (ctx.getChar() == '&') {
      ctx.eatChar();
      if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::BitAndAssign);
      } else {
        ctx.emitToken(Token::BitAnd);
      }
    } else if (ctx.getChar() == '|') {
      ctx.eatChar();
      if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::BitOrAssign);
      } else {
        ctx.emitToken(Token::BitOr);
      }
    } else if (ctx.getChar() == '^') {
      ctx.eatChar();
      if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::BitXorAssign);
      } else {
        ctx.emitToken(Token::BitXor);
      }
    } else if (ctx.getChar() == '<') {
      ctx.eatChar();
      if (ctx.getChar() == '<') {
        ctx.eatChar();
        if (ctx.getChar() == '=') {
          ctx.eatChar();
          ctx.emitToken(Token::BitShLAssign);
        } else {
          ctx.emitToken(Token::BitShL);
        }
      } else if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::LE);
      } else if (ctx.getChar() == '-') {
        ctx.eatChar();
        ctx.emitToken(Token::LArrow);
      } else {
        ctx.emitToken(Token::LT);
      }
    } else if (ctx.getChar() == '>') {
      ctx.eatChar();
      if (ctx.getChar() == '>') {
        ctx.eatChar();
        if (ctx.getChar() == '=') {
          ctx.eatChar();
          ctx.emitToken(Token::BitShRAssign);
        } else {
          ctx.emitToken(Token::BitShR);
        }
      } else if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::GE);
      } else {
        ctx.emitToken(Token::GT);
      }
    } else if (ctx.getChar() == '!') {
      ctx.eatChar();
      if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::NE);
      } else {
        ctx.getMsgs().describe()
            << "! can only be used in !=, use keyword not instead";
        ctx.getMsgs().emit(ctx.getRange(), Message::ExclamationPointAlone);
        ctx.skipToken();
      }
    } else if (ctx.getChar() == '=') {
      ctx.eatChar();
      if (ctx.getChar() == '=') {
        ctx.eatChar();
        ctx.emitToken(Token::EQ);
      } else if (ctx.getChar() == '>') {
        ctx.eatChar();
        ctx.emitToken(Token::BoolImplies);
      } else {
        ctx.emitToken(Token::Assign);
      }
    } else {
      ctx.getMsgs().describe() << "unexpected character ";
      printLiteralChar(ctx.getMsgs().describe(), ctx.getChar());
      ctx.getMsgs().emit(ctx.getRange(), Message::UnexpectedChar);
      ctx.eatChar();
      ctx.skipToken();
    }
  }
}
} // namespace whiskey
