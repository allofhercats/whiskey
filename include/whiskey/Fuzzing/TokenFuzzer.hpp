#ifndef __WHISKEY_Fuzzing_TokenFuzzer_HPP
#define __WHISKEY_Fuzzing_TokenFuzzer_HPP

#include <whiskey/Fuzzing/Module.inc>

namespace whiskey {
class TokenFuzzer {
private:
  std::stringstream textStream;
  char lastChar;
  size_t length;
  std::vector<Token::ID> tokenIDs;

protected:
  void emitChar(char value);
  void emitToken(Token::ID id);
  char getLastChar() const;
  size_t getLength() const;
  Token::ID getLastTokenID() const;

  virtual void onFuzz() = 0;

public:
  TokenFuzzer();
  TokenFuzzer(const TokenFuzzer &) = delete;
  virtual ~TokenFuzzer();

  std::string getText() const;
  const std::vector<Token::ID> &getTokenIDs() const;

  void fuzz();
};
} // namespace whiskey

#endif
