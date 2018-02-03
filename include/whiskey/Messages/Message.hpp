#ifndef __WHISKEY_Messages_Message_HPP
#define __WHISKEY_Messages_Message_HPP

#include <whiskey/Source/Token.hpp>

namespace whiskey {
class Source;

class Message {
public:
  enum Severity { Note, Warning, Error, FatalError, InternalCompilerError };

private:
  Token token;
  Severity severity;
  std::string description;

public:
  Message(Token token, Severity severity, std::string desc);

  Token &getToken();
  const Token &getToken() const;
  void setToken(Token value);

  Severity getSeverity() const;
  void setSeverity(Severity value);

  const std::string &getDescription() const;
  void setDescription(std::string value);

  void print(std::ostream &os, const Source &source) const;
};

bool operator<(const Message &lhs, const Message &rhs);
bool operator<=(const Message &lhs, const Message &rhs);
bool operator>(const Message &lhs, const Message &rhs);
bool operator>=(const Message &lhs, const Message &rhs);
bool operator!=(const Message &lhs, const Message &rhs);
bool operator==(const Message &lhs, const Message &rhs);
} // namespace whiskey

#endif
