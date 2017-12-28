#ifndef __WHISKEY_Fuzzing_TokenFuzzerSimple_HPP
#define __WHISKEY_Fuzzing_TokenFuzzerSimple_HPP

#include <whiskey/Fuzzing/Module.inc>

#include <whiskey/Fuzzing/TokenFuzzer.hpp>

namespace whiskey {
class TokenFuzzerSimple : public TokenFuzzer {
private:
  unsigned int nChars;

protected:
  void onFuzz();

public:
  TokenFuzzerSimple(unsigned int nChars);
};
} // namespace whiskey

#endif
