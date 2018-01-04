#ifndef __WHISKEY_Lexing_LexerContext_HPP
#define __WHISKEY_Lexing_LexerContext_HPP

#include <vector>

#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Token.hpp>

namespace whiskey {
class MessageBuffer;

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
