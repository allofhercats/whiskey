#include <whiskey/Parsing/ParserContext.hpp>

#include <whiskey/Core/Verbose.hpp>

namespace whiskey {
ParserContext::ParserContext(const std::vector<Token> &tokens,
                             std::vector<Token>::size_type offset)
    : tokens(&tokens), offset(offset) {
}

bool ParserContext::more() const {
  return !injected.empty() || offset < tokens->size();
}

const Token &ParserContext::get() const {
  if (injected.empty()) {
    if (offset < tokens->size()) {
      return (*tokens)[offset];
    } else {
      return Token::eof;
    }
  } else {
    return injected.top();
  }
}

const Token &ParserContext::last() const {
  return _last;
}

Token ParserContext::eat() {
  Token rtn;
  if (injected.empty()) {
    if (offset < tokens->size()) {
      rtn = (*tokens)[offset++];
    } else {
      rtn = Token::eof;
    }
  } else {
    Token tmp = injected.top();
    injected.pop();
    rtn = tmp;
  }

  _last = rtn;

  W_VERBOSE("eat " << rtn);

  return rtn;
}

void ParserContext::inject(TokenID tokenID) {
  W_VERBOSE("inject " << tokenID);

  Token tmp = get();
  tmp.setID(tokenID);
  injected.push(tmp);
}
} // namespace whiskey
