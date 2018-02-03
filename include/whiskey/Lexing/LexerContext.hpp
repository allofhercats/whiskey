#ifndef __WHISKEY_Lexing_LexerContext_HPP
#define __WHISKEY_Lexing_LexerContext_HPP

#include <vector>

#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Token.hpp>

namespace whiskey {
class MessageBuffer;

class LexerContext {
private:
  Source *source;
  Token::LinenoType firstLineno;
  Token::ColumnnoType firstColumnno;
  Token::LinenoType lastLineno;
  Token::ColumnnoType lastColumnno;
  Token::LengthType length;
  std::stringstream buffer;
  std::vector<Token> *tokens;
  MessageBuffer *msgs;

public:
  LexerContext(Source &source, std::vector<Token> &tokens, MessageBuffer &msgs);

  bool areMoreChars(size_t lookahead = 0) const;
  char32_t getChar(size_t lookahead = 0) const;
  char32_t eatChar();

  bool hasText() const;
  bool hasText(const std::string &value) const;

  void emitToken(Token::ID id);
  void skipToken();

  MessageBuffer &getMsgs();
};
} // namespace whiskey

#endif
