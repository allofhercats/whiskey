#include <whiskey/Lexing/LexerContext.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Source/Source.hpp>

namespace whiskey {
LexerContext::LexerContext(Source &source, std::vector<Token> &tokens) : source(&source), firstLineno(1), firstColumnno(1), lastLineno(1), lastColumnno(1), length(0), tokens(&tokens) {}

bool LexerContext::more() const {
  return source->more();
}

char LexerContext::get() const {
  return source->get();
}

char LexerContext::eat() {
  char chr = source->eat();
  
  W_ASSERT_NE(chr, '\r', "Cannot handle non-UNIX newlines.");

  if (chr == '\n') {
    lastLineno++;
    lastColumnno = 1;
  } else {
    lastColumnno++;
  }

  length++;

  return chr;
}

void LexerContext::buffer(char chr) {
  _buffer << chr;
}

std::string LexerContext::getBuffer() const {
  return _buffer.str();
}

void LexerContext::emit(TokenID id) {
  Token tmp(path.empty() ? source->getDefaultPath() : path, firstLineno, firstColumnno, length, id, _buffer.str());
  skip();
  tokens->push_back(tmp);
}

void LexerContext::skip() {
  firstLineno = lastLineno;
  firstColumnno = lastColumnno;
  length = 0;
  _buffer.str("");
}

std::vector<Token>::size_type LexerContext::getNTokens() const {
  return tokens->size();
}

const Token &LexerContext::getLastToken() const {
  return tokens->back();
}

Token LexerContext::createErrorToken() const {
  return Token(path, firstLineno, firstColumnno, length, TokenID::None, _buffer.str());
}
} // namespace whiskey
