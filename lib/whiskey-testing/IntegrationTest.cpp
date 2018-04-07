#include <whiskey-testing/IntegrationTest.hpp>

#include <fstream>
#include <iostream>

#include <whiskey/Core/Verbose.hpp>
#include <whiskey/Source/Source.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Lexing/LexerContext.hpp>
#include <whiskey/Lexing/Lexer.hpp>

#include <whiskey-testing/PathUtils.hpp>

namespace whiskey {
IntegrationTest::IntegrationTest() : checkTokens(false), passed(false) {}

IntegrationTest::IntegrationTest(std::string name) : IntegrationTest() {
  this->name = name;
}

const std::string &IntegrationTest::getName() const {
	return name;
}

void IntegrationTest::setName(std::string value) {
	name = value;
}

const std::string &IntegrationTest::getWorkingPath() const {
  return workingPath;
}

void IntegrationTest::setWorkingPath(std::string value) {
  workingPath = value;
}

const std::string &IntegrationTest::getSourcePath() const {
	return sourcePath;
}

void IntegrationTest::setSourcePath(std::string value) {
	sourcePath = value;
}

bool IntegrationTest::getCheckTokens() const {
  return checkTokens;
}

void IntegrationTest::setCheckTokens(bool value) {
  checkTokens = value;
}

std::vector<Token> &IntegrationTest::getExpectedTokens() {
	return expectedTokens;
}

const std::vector<Token> &IntegrationTest::getExpectedTokens() const {
	return expectedTokens;
}

bool IntegrationTest::run() {
  // Reset passed
  passed = true;

  // Print prefix
  std::cout << "[" << name << "] Running...\n";

  // Initialize messages
	MessageContext messageCtx;

	// Load source
  std::ifstream handle(sourcePath.c_str());
  if (!handle.good()) {
    std::cout << "[" << name << "] error: could not open " << sourcePath << "\n";
    return false;
  }

  Source source(handle);

	// Lex
	std::vector<Token> actualTokens;
	LexerContext lexerCtx(source, actualTokens);
	Lexer lexer;
	lexer.lex(lexerCtx, messageCtx);
  
  messageCtx.print(std::cerr, source);
  if (messageCtx.getMessageCount() > 0) {
    passed = false;
  }

  if (checkTokens) {
    for (std::vector<Token>::const_iterator ie = expectedTokens.cbegin(), ia = actualTokens.cbegin(); ie != expectedTokens.cend() && ia != actualTokens.cend(); ++ie, ++ia) {
      if (ie->hasLineno() && ie->getLineno() != ia->getLineno()) {
        std::cerr << "[" << name << "] failed: expected token " << *ie << ", actually " << *ia << "\n";
        passed = false;
      } else if (ie->hasColumnno() && ie->getColumnno() != ia->getColumnno()) {
        std::cerr << "[" << name << "] failed: expected token " << *ie << ", actually " << *ia << "\n";
        passed = false;
      } else if (ie->getLength() > 0 && ie->getLength() != ia->getLength()) {
        std::cerr << "[" << name << "] failed: expected token " << *ie << ", actually " << *ia << "\n";
        passed = false;
      } else if (ie->getID() != ia->getID()) {
        std::cerr << "[" << name << "] failed: expected token " << *ie << ", actually " << *ia << "\n";
        passed = false;
      } else if (ie->hasText() && ie->getText() != ia->getText()) {
        std::cerr << "[" << name << "] failed: expected token " << *ie << ", actually " << *ia << "\n";
        passed = false;
      }
    }

    if (expectedTokens.size() < actualTokens.size()) {
      std::cerr << "[" << name << "] failed: expected " << expectedTokens.size() << " token" << (expectedTokens.size() == 1 ? "" : "s") << ", got " << actualTokens.size() << "\n";
      for (size_t i = expectedTokens.size(); i < actualTokens.size(); ++i) {
        std::cerr << "[" << name << "] info: extra " << actualTokens[i] << "\n";
      }
      passed = false;
    } else if (expectedTokens.size() > actualTokens.size()) {
      std::cerr << "[" << name << "] failed: expected " << expectedTokens.size() << " token" << (expectedTokens.size() == 1 ? "" : "s") << ", got " << actualTokens.size() << "\n";
      for (size_t i = actualTokens.size(); i < expectedTokens.size(); ++i) {
        std::cerr << "[" << name << "] info: missing " << expectedTokens[i] << "\n";
      }
      passed = false;
    }
  }

  // Clean up
  handle.close();

  // Return results
  if (passed) {
    std::cout << "[" << name << "] Passed.\n";
  }
  
  return passed;
}

bool IntegrationTest::hasPassed() const {
  return passed;
}
}