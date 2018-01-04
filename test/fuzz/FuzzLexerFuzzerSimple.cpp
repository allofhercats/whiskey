#include <gtest/gtest.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Source/Source.hpp>
#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Token.hpp>
#include <whiskey/Messages/MessageBuffer.hpp>
#include <whiskey/Lexing/Lexer.hpp>
#include <whiskey/Fuzzing/TokenFuzzerSimple.hpp>

using namespace whiskey;

int sampleSize = 131072;
int nSamples = 128;

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  srand(time(nullptr));

  int c;
  while ((c = getopt(argc, argv, "s:n:")) != -1) {
    switch (c) {
    case 's':
      if (sscanf(optarg, "%i", &sampleSize) != 1) {
        std::cerr << "error: expected integer for -s\n";
        return 1;
      }
      break;
    case 'n':
      if (sscanf(optarg, "%i", &nSamples) != 1) {
        std::cerr << "error: expected integer for -n\n";
        return 1;
      }
      break;
    case '?':
      std::cerr << "error: unknown option -" << (char)optopt << "\n";
      return 1;
    default:
      W_ASSERT_UNREACHABLE("getopt(...) failed.");
      break;
    }
  }

  return RUN_ALL_TESTS();
}

TEST(FuzzLexerFuzzerSimple, All) {
  ASSERT_GT(sampleSize, 1);
  ASSERT_GT(nSamples, 0);

  for (int i = 0; i < nSamples; i++) {
    std::cout << "Running sample " << (i + 1) << "/" << nSamples << "... ("
              << sampleSize << " chars)\n";

    TokenFuzzer *fuzzer = new TokenFuzzerSimple(sampleSize);

    fuzzer->fuzz();

    Source src;
    src.loadString(fuzzer->getText(), true);

    Location loc(src);

    std::vector<Token> toks;
    MessageBuffer msgs;

    Lexer lexer(loc, toks, msgs);
    lexer.lex();

    for (int i = 0; i < fuzzer->getTokenIDs().size() && i < toks.size(); i++) {
      if (fuzzer->getTokenIDs()[i] != toks[i].getID()) {
        std::cout << "Expected token:\n";
        if (i > 0) {
          std::cout << "  Previous: ";
          Token::printTokenIDDebug(std::cout, fuzzer->getTokenIDs()[i - 1]);
          std::cout << "\n";
        }
        std::cout << "  Expected: ";
        Token::printTokenIDDebug(std::cout, fuzzer->getTokenIDs()[i]);
        std::cout << "\n";
        if (i + 1 < fuzzer->getTokenIDs().size()) {
          std::cout << "  Next: ";
          Token::printTokenIDDebug(std::cout, fuzzer->getTokenIDs()[i + 1]);
          std::cout << "\n";
        }

        std::cout << "\nActual token:\n";
        if (i > 0) {
          std::cout << "  Previous:";
          toks[i - 1].printDebug(std::cout);
          std::cout << "\n";
        }
        std::cout << "  Actual:";
        toks[i].printDebug(std::cout);
        std::cout << "\n";
        if (i + 1 < toks.size()) {
          std::cout << "  Next:";
          toks[i + 1].printDebug(std::cout);
          std::cout << "\n";
        }
        std::cout << "\n";

        ASSERT_EQ(fuzzer->getTokenIDs()[i], toks[i].getID());
      }
    }

    ASSERT_EQ(fuzzer->getTokenIDs().size(), toks.size());

    std::cout << "  " << toks.size() << " token(s), " << msgs.getNMessages()
              << " message(s).\n";

    delete fuzzer;
  }
}
