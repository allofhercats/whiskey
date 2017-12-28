#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

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

TEST(FuzzLexerRandom, All) {
  ASSERT_GT(sampleSize, 1);
  ASSERT_GT(nSamples, 0);

  for (int i = 0; i < nSamples; i++) {
    std::cout << "Running sample " << (i + 1) << "/" << nSamples << "... ("
              << sampleSize << " chars)\n";
    char *buffer = new char[sampleSize];

    for (int j = 0; j < sampleSize - 1; j++) {
      while (true) {
        buffer[j] = (char)rand();
        if (buffer[j] != 0) {
          break;
        }
      }
    }

    buffer[sampleSize - 1] = 0;

    Source src;
    src.loadCString(buffer);

    Location loc(src);

    std::vector<Token> toks;
    MessageBuffer msgs;

    Lexer lexer(loc, toks, msgs);
    lexer.lex();

    std::cout << "  " << toks.size() << " token(s), " << msgs.getNMessages()
              << " message(s).\n";

    delete[] buffer;
  }
}
