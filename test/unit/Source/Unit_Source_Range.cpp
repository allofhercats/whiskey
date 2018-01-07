#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Source/Range.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

TEST(Unit_Source_Range, Empty) {
  Source src;
  src.loadString("abcdefghijklmnopqrstuvwxyz");

  Location loc(src);

  Range rng(loc);

  ASSERT_STREQ(rng.getText().c_str(), "");
}

TEST(Unit_Source_Range, Length5) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);

  Range rng(loc, 5);

  ASSERT_STREQ(rng.getText().c_str(), "abcde");

  delete src;
}

TEST(Unit_Source_Range, Length26) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);

  Range rng(loc, 26);

  ASSERT_STREQ(rng.getText().c_str(), "abcdefghijklmnopqrstuvwxyz");
}

TEST(Unit_Source_Range, Length100) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);

  Range rng(loc, 100);

  ASSERT_STREQ(rng.getText().c_str(), "abcdefghijklmnopqrstuvwxyz");
}