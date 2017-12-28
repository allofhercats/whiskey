#include "Module.inc"

#include <whiskey/Fuzzing/TokenFuzzer.hpp>

namespace whiskey {
void TokenFuzzer::emitChar(char value) {
  textStream << value;
  lastChar = value;
  length++;
}

void TokenFuzzer::emitToken(Token::ID id) {
  tokenIDs.push_back(id);
}

char TokenFuzzer::getLastChar() const {
  return lastChar;
}

size_t TokenFuzzer::getLength() const {
  return length;
}

Token::ID TokenFuzzer::getLastTokenID() const {
  return tokenIDs.back();
}

TokenFuzzer::TokenFuzzer() : lastChar(0), length(0) {
}

TokenFuzzer::~TokenFuzzer() {
}

std::string TokenFuzzer::getText() const {
  return textStream.str();
}

const std::vector<Token::ID> &TokenFuzzer::getTokenIDs() const {
  return tokenIDs;
}

void TokenFuzzer::fuzz() {
  onFuzz();
}
} // namespace whiskey
