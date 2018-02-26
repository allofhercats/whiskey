#ifndef __WHISKEY_Parsing_ParserContext_HPP
#define __WHISKEY_Parsing_ParserContext_HPP

#include <functional>
#include <stack>
#include <vector>

#include <whiskey/Source/Token.hpp>

namespace whiskey {
class ParserContext {
private:
  const std::vector<Token> *tokens;
  std::stack<Token> injected;
  std::vector<Token>::size_type offset;
  Token _last;

public:
  ParserContext(const std::vector<Token> &tokens,
                std::vector<Token>::size_type offset = 0);

  bool more() const;
  const Token &get() const;
  const Token &last() const;
  Token eat();

  void inject(TokenID tokenID);
};
} // namespace whiskey

#endif
