#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterChar.hpp>
#include <whiskey/Parsing/EvalLiterals.hpp>
#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Range.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

int nSamples = 10000000;

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  srand(time(nullptr));

  int c;
  while ((c = getopt(argc, argv, "s:n:")) != -1) {
    switch (c) {
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

TEST(FuzzLiteralsReflexiveChar, All) {
  ASSERT_GT(nSamples, 0);

  std::cout << "Printing and evaluating " << nSamples << " Chars.\n";

  for (int i = 0; i < nSamples; i++) {
    char32_t orig = (char32_t)rand();

    std::stringstream ss;

    LiteralPrinterChar(orig).print(ss);

    Source src;
    src.loadString(ss.str(), true);
    Location loc(src);
    Range rng(loc, src.getLength());

    ASSERT_EQ(src.getLength(), ss.str().size());
    ASSERT_EQ(rng.getLength(), ss.str().size());
    ASSERT_STREQ(rng.getText().c_str(), ss.str().c_str());

    char32_t evaled;

    bool res = evalLiteralChar(rng, evaled);
    if (!res) {
      std::cout << "Invalid format:\n";
      std::cout << "  Original: " << (uint32_t)orig << "\n";
      std::cout << "  Printed: " << ss.str() << "\n";
    }
    ASSERT_TRUE(res);
    if (orig != evaled) {
      std::cout << "Difference:\n";
      std::cout << "  Original: " << (uint32_t)orig << "\n";
      std::cout << "  Printed: " << ss.str() << "\n";
      std::cout << "  Evaluated: " << (uint32_t)evaled << "\n";
    }
    ASSERT_EQ(orig, evaled);

    if (nSamples < 100 || i % (nSamples / 100) == 0) {
      std::cout << "Completed " << i << "/" << nSamples << ".\n";
    }
  }
}
