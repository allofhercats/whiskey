#include <gtest/gtest.h>

#include <whiskey/Source/Range.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

TEST(Unit_Source_Range, Empty) {
  Source src;
  src.loadString("abcdefghijklmnopqrstuvwxyz");
  ASSERT_EQ(src.getText().size(), 26);

  Location loc(src);

  Range rng(loc);

  ASSERT_EQ(rng.getText().size(), 0);
  ASSERT_TRUE(rng.getText() == "");
}

TEST(Unit_Source_Range, Length5) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);

  Range rng(loc, 5);

  ASSERT_TRUE(rng.getText() == "abcde");

  delete src;
}

TEST(Unit_Source_Range, Length26) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);

  Range rng(loc, 26);

  ASSERT_TRUE(rng.getText() == "abcdefghijklmnopqrstuvwxyz");
}

TEST(Unit_Source_Range, Length100) {
  std::string str = "abcdefghijklmnopqrstuvwxyz";

  Source *src = new Source();
  src->loadString(str);

  Location loc(*src);

  Range rng(loc, 100);

  ASSERT_TRUE(rng.getText() == "abcdefghijklmnopqrstuvwxyz");
}
