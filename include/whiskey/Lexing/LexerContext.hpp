#ifndef __WHISKEY_Lexing_LexerContext_HPP
#define __WHISKEY_Lexing_LexerContext_HPP

#include <whiskey/Lexing/Module.inc>

namespace whiskey {
class LexerContext {
private:
  Location first;
  Location last;
  std::vector<Token> *tokens;
  MessageBuffer *msgs;

public:
  LexerContext(Location start, std::vector<Token> &tokens, MessageBuffer &msgs);

  const Location &getFirst() const;
  const Location &getLast() const;
  Range getRange() const;

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
