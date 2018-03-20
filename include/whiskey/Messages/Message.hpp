#ifndef __WHISKEY_Messages_Message_HPP
#define __WHISKEY_Messages_Message_HPP

#include <list>

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
  std::list<Message> children;

public:
  Message(Token token, Severity severity, std::string desc);

  Token &getToken();
  const Token &getToken() const;
  void setToken(Token value);

  Severity getSeverity() const;
  void setSeverity(Severity value);

  const std::string &getDescription() const;
  void setDescription(std::string value);

  std::list<Message> &getChildren();
  const std::list<Message> &getChildren() const;

  void print(std::ostream &os, const Source &source) const;
  void print(std::ostream &os) const;
};

bool operator<(const Message &lhs, const Message &rhs);
bool operator<=(const Message &lhs, const Message &rhs);
bool operator>(const Message &lhs, const Message &rhs);
bool operator>=(const Message &lhs, const Message &rhs);
bool operator!=(const Message &lhs, const Message &rhs);
bool operator==(const Message &lhs, const Message &rhs);
} // namespace whiskey

#endif
