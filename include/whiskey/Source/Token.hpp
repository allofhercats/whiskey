#ifndef __WHISKEY_Source_Token_HPP
#define __WHISKEY_Source_Token_HPP

#include <string>
#include <vector>

#include <whiskey/Source/TokenID.hpp>

namespace whiskey {
class Token {
public:
  typedef uint32_t LinenoType;
  typedef uint32_t ColumnnoType;
  typedef uint32_t LengthType;

private:
  std::string path;
  LinenoType lineno;
  ColumnnoType columnno;
  LengthType length;
  TokenID id;
  std::string text;

public:
  static const LinenoType linenoNone;
  static const ColumnnoType columnnoNone;

  Token();
  Token(TokenID id);
  Token(LinenoType lineno, ColumnnoType columnno, LengthType length, TokenID id);
  Token(std::string path, LinenoType lineno, ColumnnoType columnno, LengthType length, TokenID id);
  Token(LinenoType lineno, ColumnnoType columnno, LengthType length, TokenID id, std::string text);
  Token(std::string path, LinenoType lineno, ColumnnoType columnno, LengthType length, TokenID id, std::string text);

  bool hasPath() const;
  std::string &getPath();
  const std::string &getPath() const;
  void setPath(std::string value = "");

  bool hasLineno() const;
  LinenoType getLineno() const;
  void setLineno(LinenoType value = linenoNone);

  bool hasColumnno() const;
  ColumnnoType getColumnno() const;
  void setColumnno(ColumnnoType value = columnnoNone);

  LengthType getLength() const;
  void setLength(LengthType value = 0);

  bool isGood() const;

  TokenID getID() const;
  void setID(TokenID value = TokenID::None);

  bool hasText() const;
  std::string &getText();
  const std::string &getText() const;
  void setText(std::string value = "");
};

std::ostream &operator<<(std::ostream &os, const Token &value);
bool operator<(const Token &lhs, const Token &rhs);
bool operator<=(const Token &lhs, const Token &rhs);
bool operator>(const Token &lhs, const Token &rhs);
bool operator>=(const Token &lhs, const Token &rhs);
bool operator!=(const Token &lhs, const Token &rhs);
bool operator==(const Token &lhs, const Token &rhs);
} // namespace whiskey

#endif
