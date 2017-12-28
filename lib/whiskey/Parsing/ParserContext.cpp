#include "Module.inc"

#include <whiskey/Parsing/ParserContext.hpp>

namespace whiskey {
ParserContext::ParserContext(const std::vector<Token> &tokens,
                             MessageBuffer &msgs,
                             unsigned int offset)
    : tokens(&tokens), offset(0), msgs(&msgs) {
}

bool ParserContext::areMoreTokens() const {
  return !injected.empty() || offset < tokens->size();
}

Token ParserContext::getToken() const {
  if (injected.empty()) {
    if (offset < tokens->size()) {
      return (*tokens)[offset];
    } else {
      return Token();
    }
  } else {
    return injected.top();
  }
}

Token ParserContext::eatToken() {
  if (injected.empty()) {
    if (offset < tokens->size()) {
      return (*tokens)[offset++];
    } else {
      return Token();
    }
  } else {
    Token rtn = injected.top();
    injected.pop();
    return rtn;
  }
}

void ParserContext::injectToken(Token token) {
  injected.push(token);
}

MessageBuffer &ParserContext::getMsgs() const {
  return *msgs;
}

void ParserContext::errorUnexpectedToken(const std::string &expected) const {
  msgs->describe() << "expected " << expected << ", not ";
  Token::printTokenID(msgs->describe(), getToken().getID());
  msgs->emit(getToken().getRange(), Message::UnexpectedToken);
}

ParserResult ParserContext::parse(ParserContext::Rule rule) {
  ParserContext save = *this;
  ParserResult res = rule(save);
  if (res.isGood()) {
    *this = save;
  } else {
    return ParserResult();
  }
  return res;
}

ParserResult
ParserContext::parseAny(std::initializer_list<ParserContext::Rule> rules) {
  ParserResult res;
  for (const Rule &rule : rules) {
    res = parse(rule);
    if (res.isGood()) {
      return res;
    }
  }

  return ParserResult();
}
} // namespace whiskey
