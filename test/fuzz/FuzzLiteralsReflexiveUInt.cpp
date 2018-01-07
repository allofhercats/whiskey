#include <gtest/gtest.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterUInt.hpp>
#include <whiskey/Parsing/EvalLiterals.hpp>
#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Range.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

int nSamples = 100000;

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

TEST(FuzzLiteralsReflexiveUInt, All) {
  ASSERT_GT(nSamples, 0);

  const int nFormats = 10;

  std::cout << "Printing and evaluating " << nSamples << " UInts.\n";

  for (int i = 0; i < nSamples; i++) {
    uint32_t origBase[4] = {
        (uint32_t)rand(), (uint32_t)rand(), (uint32_t)rand(), (uint32_t)rand()};
    uint64_t orig = (origBase[3] << 24) ^ (origBase[2] << 16) ^
                    (origBase[1] << 8) ^ origBase[0];

    std::stringstream ss[nFormats];

    LiteralPrinterUInt(orig, 2, true, 0).print(ss[0]);
    LiteralPrinterUInt(orig, 2, true, 32).print(ss[1]);
    LiteralPrinterUInt(orig, 2, true, 64).print(ss[2]);
    LiteralPrinterUInt(orig, 8, true, 0).print(ss[3]);
    LiteralPrinterUInt(orig, 8, true, 32).print(ss[4]);
    LiteralPrinterUInt(orig, 8, true, 64).print(ss[5]);
    LiteralPrinterUInt(orig, 10, true, 0).print(ss[6]);
    LiteralPrinterUInt(orig, 16, true, 0).print(ss[7]);
    LiteralPrinterUInt(orig, 16, true, 32).print(ss[8]);
    LiteralPrinterUInt(orig, 16, true, 64).print(ss[9]);

    for (int j = 0; j < nFormats; j++) {
      Source src;
      src.loadString(ss[j].str(), true);
      Location loc(src);
      Range rng(loc, src.getLength());

      ASSERT_EQ(src.getLength(), ss[j].str().size());
      ASSERT_EQ(rng.getLength(), ss[j].str().size());
      ASSERT_STREQ(rng.getText().c_str(), ss[j].str().c_str());

      uint64_t evaled;

      bool res = evalLiteralUInt(rng, evaled);
      if (!res) {
        std::cout << "Invalid format:\n";
        std::cout << "  Original: " << orig << "\n";
        std::cout << "  Printed: " << ss[j].str() << "\n";
      }
      ASSERT_TRUE(res);
      if (orig != evaled) {
        std::cout << "Difference:\n";
        std::cout << "  Original: " << orig << "\n";
        std::cout << "  Printed: " << ss[j].str() << "\n";
        std::cout << "  Evaluated: " << evaled << "\n";
      }
      ASSERT_EQ(orig, evaled);
    }

    if (nSamples < 100 || i % (nSamples / 100) == 0) {
      std::cout << "Completed " << i << "/" << nSamples << ".\n";
    }
  }
}
