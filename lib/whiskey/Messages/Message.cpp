#include <whiskey/Messages/Message.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Color.hpp>
#include <whiskey/Source/Source.hpp>

namespace whiskey {
Message::Message(Token token, Message::Severity severity, std::string description)
    : token(token), severity(severity), description(description) {
}

Token &Message::getToken() {
  return token;
}

const Token &Message::getToken() const {
  return token;
}

void Message::setToken(Token value) {
  token = value;
}

Message::Severity Message::getSeverity() const {
  return severity;
}

void Message::setSeverity(Message::Severity value) {
  severity = value;
}

const std::string &Message::getDescription() const {
  return description;
}

void Message::setDescription(std::string value) {
  description = value;
}

std::list<Message> &Message::getChildren() {
  return children;
}

const std::list<Message> &Message::getChildren() const {
  return children;
}

void Message::print(std::ostream &os, const Source &source) const {
  if (token.hasPath()) {
    os << token.getPath() << ":";
  } else {
    os << source.getDefaultPath() << ":";
  }

  if (token.hasLineno()) {
    os << token.getLineno() << ":";
    if (token.hasColumnno()) {
      os << token.getColumnno() << ":";
    }
  }

  os << " ";

  switch (severity) {
  case Message::Note:
    os << Color::greyDark << "note: ";
    break;
  case Message::Warning:
    os << Color::yellowLight << "warning: ";
    break;
  case Message::Error:
    os << Color::redLight << "error: ";
    break;
  case Message::FatalError:
    os << Color::redLight << "fatal error: ";
    break;
  case Message::InternalCompilerError:
    os << Color::magentaLight << "internal compiler error: ";
    break;
  }

  os << Color::reset << description;
}

void Message::print(std::ostream &os) const {
  if (token.hasPath()) {
    os << token.getPath() << ":";

    if (token.hasLineno()) {
      os << token.getLineno() << ":";
      if (token.hasColumnno()) {
        os << token.getColumnno() << ":";
      }
    }

    os << " ";
  }

  switch (severity) {
  case Message::Note:
    os << Color::greyDark << "note: ";
    break;
  case Message::Warning:
    os << Color::yellowLight << "warning: ";
    break;
  case Message::Error:
    os << Color::redLight << "error: ";
    break;
  case Message::FatalError:
    os << Color::redLight << "fatal error: ";
    break;
  case Message::InternalCompilerError:
    os << Color::magentaLight << "internal compiler error: ";
    break;
  }

  os << Color::reset << description;
}

bool operator<(const Message &lhs, const Message &rhs) {
  return lhs.getToken() < rhs.getToken();
}

bool operator<=(const Message &lhs, const Message &rhs) {
  return lhs.getToken() <= rhs.getToken();
}

bool operator>(const Message &lhs, const Message &rhs) {
  return lhs.getToken() > rhs.getToken();
}

bool operator>=(const Message &lhs, const Message &rhs) {
  return lhs.getToken() >= rhs.getToken();
}

bool operator!=(const Message &lhs, const Message &rhs) {
  return !(lhs == rhs);
}

bool operator==(const Message &lhs, const Message &rhs) {
  if (lhs.getToken() != rhs.getToken()) {
    return false;
  }

  if (lhs.getSeverity() != rhs.getSeverity()) {
    return false;
  }

  if (lhs.getDescription() != rhs.getDescription()) {
    return false;
  }

  return true;
}
} // namespace whiskey
