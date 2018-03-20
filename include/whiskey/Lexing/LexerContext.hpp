#ifndef __WHISKEY_Lexing_LexerContext_HPP
#define __WHISKEY_Lexing_LexerContext_HPP

#include <list>
#include <vector>
#include <sstream>

#include <whiskey/Source/Token.hpp>

namespace whiskey {
class Source;
class MessageContext;

class LexerContext {
private:
  Source *source;
  std::string path;
  Token::LinenoType firstLineno;
  Token::ColumnnoType firstColumnno;
  Token::LinenoType lastLineno;
  Token::ColumnnoType lastColumnno;
  Token::LengthType length;
  std::stringstream _buffer;
  std::vector<Token> *tokens;

public:
  LexerContext(Source &source, std::vector<Token> &tokens);
  LexerContext(const LexerContext &other) = delete;

  bool hasPath() const;
  std::string &getPath();
  const std::string &getPath() const;
  void setPath(std::string value);

  bool more() const;
  char get() const;
  char eat();

  void buffer(char chr);
  std::string getBuffer() const;

  void emit(TokenID id);
  void skip();

  std::vector<Token>::size_type getNTokens() const;
  const Token &getLastToken() const;

  Token createErrorToken() const;
};
} // namespace whiskey

#endif
