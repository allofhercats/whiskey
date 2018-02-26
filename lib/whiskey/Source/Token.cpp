#include <whiskey/Source/Token.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Literals.hpp>

namespace whiskey {
const Token::LinenoType Token::linenoNone = 0;
const Token::ColumnnoType Token::columnnoNone = 0;

const Token Token::eof;

Token::Token() : lineno(Token::linenoNone), columnno(Token::columnnoNone), length(0), id(TokenID::None) {}

Token::Token(TokenID id) : lineno(Token::linenoNone), columnno(Token::columnnoNone), length(0), id(id) {}

Token::Token(TokenID id, std::string text) : lineno(Token::linenoNone), columnno(Token::columnnoNone), length(0), id(id), text(text) {}

Token::Token(Token::LinenoType lineno, Token::ColumnnoType columnno, Token::LengthType length, TokenID id) : lineno(lineno), columnno(columnno), length(length), id(id) {}

Token::Token(std::string path, Token::LinenoType lineno, Token::ColumnnoType columnno, Token::LengthType length, TokenID id) : path(path), lineno(lineno), columnno(columnno), length(length), id(id) {}

Token::Token(Token::LinenoType lineno, Token::ColumnnoType columnno, Token::LengthType length, TokenID id, std::string text) : lineno(lineno), columnno(columnno), length(length), id(id), text(text) {}

Token::Token(std::string path, Token::LinenoType lineno, Token::ColumnnoType columnno, Token::LengthType length, TokenID id, std::string text) : path(path), lineno(lineno), columnno(columnno), length(length), id(id), text(text) {}

bool Token::hasPath() const {
  return !path.empty();
}

std::string &Token::getPath() {
  return path;
}

const std::string &Token::getPath() const {
  return path;
}

void Token::setPath(std::string value) {
  path = value;
}

bool Token::hasLineno() const {
  return lineno > 0;
}

Token::LinenoType Token::getLineno() const {
  return lineno;
}

void Token::setLineno(Token::LinenoType value) {
  lineno = value;
}

bool Token::hasColumnno() const {
  return columnno > 0;
}

Token::ColumnnoType Token::getColumnno() const {
  return columnno;
}

void Token::setColumnno(Token::ColumnnoType value) {
  columnno = value;
}

Token::LengthType Token::getLength() const {
  return length;
}

void Token::setLength(Token::LengthType value) {
  length = value;
}

bool Token::isGood() const {
  return id != TokenID::None;
}

TokenID Token::getID() const {
  return id;
}

void Token::setID(TokenID value) {
  id = value;
}

bool Token::hasText() const {
  return !text.empty();
}

std::string &Token::getText() {
  return text;
}

const std::string &Token::getText() const {
  return text;
}

void Token::setText(std::string value) {
  text = value;
}

std::ostream &operator<<(std::ostream &os, const Token &value) {
  os << "<";
  if (value.hasPath()) {
    os << value.getPath() << ":";
  }
  os << value.getLineno() << ":" << value.getColumnno() << "+" << value.getLength() << " ";
  printTokenIDDebug(os, value.getID());
  if (value.hasText()) {
    os << " ";
    printLiteralString(os, value.getText());
  }
  os << ">";
  return os;
}

bool operator<(const Token &lhs, const Token &rhs) {
  if (lhs.getLineno() < rhs.getLineno()) {
    return true;
  } else if (lhs.getLineno() == rhs.getLineno()) {
    if (lhs.getColumnno() < rhs.getColumnno()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool operator<=(const Token &lhs, const Token &rhs) {
  if (lhs.getLineno() < rhs.getLineno()) {
    return true;
  } else if (lhs.getLineno() == rhs.getLineno()) {
    if (lhs.getColumnno() <= rhs.getColumnno()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool operator>(const Token &lhs, const Token &rhs) {
  if (lhs.getLineno() < rhs.getLineno()) {
    return false;
  } else if (lhs.getLineno() == rhs.getLineno()) {
    if (lhs.getColumnno() <= rhs.getColumnno()) {
      return false;
    } else {
      return true;
    }
  } else {
    return true;
  }
}

bool operator>=(const Token &lhs, const Token &rhs) {
  if (lhs.getLineno() < rhs.getLineno()) {
    return false;
  } else if (lhs.getLineno() == rhs.getLineno()) {
    if (lhs.getColumnno() < rhs.getColumnno()) {
      return false;
    } else {
      return true;
    }
  } else {
    return true;
  }
}

bool operator!=(const Token &lhs, const Token &rhs) {
  return !(lhs == rhs);
}

bool operator==(const Token &lhs, const Token &rhs) {
  if (lhs.getPath() != rhs.getPath()) {
    return false;
  }

  if (lhs.getLineno() != rhs.getLineno()) {
    return false;
  }

  if (lhs.getColumnno() != rhs.getColumnno()) {
    return false;
  }

  if (lhs.getLength() != rhs.getLength()) {
    return false;
  }

  if (lhs.getID() != rhs.getID()) {
    return false;
  }

  if (lhs.getText() != rhs.getText()) {
    return false;
  }

  return true;
}
} // namespace whiskey
