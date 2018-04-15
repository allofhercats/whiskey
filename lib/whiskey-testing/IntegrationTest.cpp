#include <whiskey-testing/IntegrationTest.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <chrono>

#include <whiskey/Source/Source.hpp>
#include <whiskey/Messages/MessageContext.hpp>
#include <whiskey/Lexing/LexerContext.hpp>
#include <whiskey/Lexing/Lexer.hpp>
#include <whiskey/Lexing/UnLexUtils.hpp>
#include <whiskey/Parsing/ParserContext.hpp>
#include <whiskey/Parsing/Parser.hpp>
#include <whiskey/CodeGen/LLVMGenerator.hpp>
#include <whiskey/CodeGen/LLVMJIT.hpp>

namespace whiskey {
bool IntegrationTest::compareTokenVectors(const std::vector<Token> &expectedTokens, const std::vector<Token> &actualTokens, bool isReLex) {
  bool ok = true;
  std::vector<Token>::const_iterator ie = expectedTokens.cbegin();
  std::vector<Token>::const_iterator ia = actualTokens.cbegin();
  std::vector<Token>::const_iterator ee = expectedTokens.cend();
  std::vector<Token>::const_iterator ea = actualTokens.cend();
  for (; ie != ee && ia != ea; ++ie, ++ia) {
    bool matching = true;
    if (!isReLex && (ie->hasLineno() && ie->getLineno() != ia->getLineno())) {
      matching = false;
    } else if (!isReLex && (ie->hasColumnno() && ie->getColumnno() != ia->getColumnno())) {
      matching = false;
    } else if (ie->getLength() > 0 && ie->getLength() != ia->getLength()) {
      matching = false;
    } else if (ie->getID() != TokenID::None && ie->getID() != ia->getID()) {
      matching = false;
    } else if (ie->hasText() && ie->getText() != ia->getText()) {
      matching = false;
    }

    if (!matching) {
      std::cerr << "[" << name << "] error: expected token " << *ie << ", got " << *ia << " instead" << (isReLex ? " (in re-lexing)" : "") << "\n";
      ok = false;
    }
  }

  if (expectedTokens.size() < actualTokens.size()) {
    std::cerr << "[" << name << "] error: expected " << expectedTokens.size() << " token" << (expectedTokens.size() == 1 ? "" : "s") << ", got " << actualTokens.size() << (isReLex ? " (in re-lexing)" : "") << "\n";
    for (; ia != ea; ++ia) {
      std::cerr << "[" << name << "] note: got extra " << *ia << "\n";
    }
    ok = false;
  } else if (expectedTokens.size() > actualTokens.size()) {
    std::cerr << "[" << name << "] error: expected " << expectedTokens.size() << " token" << (expectedTokens.size() == 1 ? "" : "s") << ", got " << actualTokens.size() << (isReLex ? " (in re-lexing)" : "") << "\n";
    for (; ie != ee; ++ie) {
      std::cerr << "[" << name << "] note: missing " << *ia << "\n";
    }
    ok = false;
  }

  return ok;
}

IntegrationTest::IntegrationTest(std::string name) : name(name), sourceMode(SourceMode::Memory), checkTokens(false), reLexTokens(true), checkAST(false) {}

std::string &IntegrationTest::getName() {
  return name;
}

const std::string &IntegrationTest::getName() const {
  return name;
}

void IntegrationTest::setName(std::string value) {
  name = value;
}

IntegrationTest::SourceMode IntegrationTest::getSourceMode() const {
  return sourceMode;
}

void IntegrationTest::setSourceMode(IntegrationTest::SourceMode value) {
  sourceMode = value;
}

std::string &IntegrationTest::getSourceText() {
  return sourceText;
}

const std::string &IntegrationTest::getSourceText() const {
  return sourceText;
}

void IntegrationTest::setSourceText(std::string value) {
  sourceText = value;
}

std::string &IntegrationTest::getSourcePath() {
  return sourcePath;
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

bool IntegrationTest::getReLexTokens() const {
  return reLexTokens;
}

void IntegrationTest::setReLexTokens(bool value) {
  reLexTokens = value;
}

std::vector<Token> &IntegrationTest::getExpectedTokens() {
  return expectedTokens;
}

const std::vector<Token> &IntegrationTest::getExpectedTokens() const {
  return expectedTokens;
}

void IntegrationTest::setExpectedTokens(std::vector<Token> value) {
  expectedTokens = value;
}

bool IntegrationTest::getCheckAST() const {
  return checkAST;
}

void IntegrationTest::setCheckAST(bool value) {
  checkAST = value;
}

Node &IntegrationTest::getExpectedAST() {
  return expectedAST;
}

const Node &IntegrationTest::getExpectedAST() const {
  return expectedAST;
}

void IntegrationTest::setExpectedAST(Node value) {
  expectedAST = value;
}

const std::function<void(JIT &)> &IntegrationTest::getExecutionTest() const {
  return executionTest;
}

void IntegrationTest::setExecutionTest(std::function<void(JIT &)> value) {
  executionTest = value;
}

bool IntegrationTest::run() {
  std::cout << "[" << name << "] Running...\n";

  std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

  bool ok = true;

  std::unique_ptr<std::istream> stream;

  if (sourceMode == SourceMode::Memory) {
    if (!sourcePath.empty()) {
      std::cerr << "[" << name << "] warning: test with source mode 'Memory' has non-empty source path\n";
    }

    stream = std::make_unique<std::istringstream>(sourceText);
  } else if (sourceMode == SourceMode::File) {
    if (!sourceText.empty()) {
      std::cerr << "[" << name << "] warning: test with source mode 'File' has non-empty source text\n";
    }

    stream = std::make_unique<std::ifstream>(sourcePath.c_str());
    if (!stream->good()) {
      std::cerr << "[" << name << "] error: unable to open '" << sourcePath << "' for reading\n";
      return false;
    }
  } else {
    W_ASSERT_UNREACHABLE("Unsupported source mode.");
  }

  W_ASSERT_TRUE(stream, "Must have initialized source stream.");

  Source source(*stream, sourceMode == SourceMode::File ? sourcePath : W_SOURCE_DEFAULT_PATH);
  MessageContext msgs;
  std::vector<Token> actualTokens;
  LexerContext lexerCtx(source, actualTokens);
  Lexer lexer;
  lexer.lex(lexerCtx, msgs);

  msgs.print(std::cerr, source);

  if (msgs.getMessageCount() > 0) {
    ok = false;
  }

  if (checkTokens) {
    if (!compareTokenVectors(expectedTokens, actualTokens, false)) {
      ok = false;
    } else if (reLexTokens) {
      std::string sourceTextReLex = getSourceFromTokens(actualTokens);
      std::istringstream streamReLex(sourceTextReLex);
      Source sourceReLex(streamReLex);
      std::vector<Token> reLexTokens;
      LexerContext lexerCtxReLex(sourceReLex, reLexTokens);
      Lexer lexerReLex;
      lexerReLex.lex(lexerCtxReLex, msgs);

      msgs.print(std::cerr, source);

      if (msgs.getMessageCount() > 0) {
        ok = false;
      }

      if (!compareTokenVectors(actualTokens, reLexTokens, true)) {
        ok = false;
      }
    }
  }

  ParserContext parserCtx(actualTokens);
  Parser parser;
  parser.initGrammar();
  Node actualAST = parser.parse(parserCtx, msgs);

  msgs.print(std::cerr, source);

  if (msgs.getMessageCount() > 0) {
    ok = false;
  }

  if (checkAST) {
    if (expectedAST != actualAST) {
      std::cerr << "[" << name << "] error: expected AST does not match actual AST\n";
      std::cerr << "[" << name << "] note: expected:\n  ";
      expectedAST.print(std::cerr, 2);
      std::cerr << "\n[" << name << "] note: actual:\n  ";
      actualAST.print(std::cerr, 2);
      std::cerr << "\n";
      ok = false;
    }
  }

  LLVMGenerator llvmGen;
  llvmGen.generateUnit(actualAST);

  LLVMJIT llvmJIT;
  llvmJIT.addModule(std::move(llvmGen.getLLVMModule()));

  if (executionTest) {
    size_t nFailsBefore = getNAssertFailures(AssertMode::Test);
    executionTest(llvmJIT);
    size_t nFailsAfter = getNAssertFailures(AssertMode::Test);

    if (nFailsAfter > nFailsBefore) {
      std::cerr << "[" << name << "] error: assertion failures while executing function(s)\n";
      ok = false;
    }
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
  double diff = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>((end - start)).count();

  if (ok) {
    std::cout << "[" << name << "] Passed (" << std::fixed << std::setw(3) << std::setprecision(3) << diff << "s).\n";
  } else {
    std::cout << "[" << name << "] Failed (" << std::fixed << std::setw(3) << std::setprecision(3) << diff << "s)!\n";
  }

  return ok;
}
}
