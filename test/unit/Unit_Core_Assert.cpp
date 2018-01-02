#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Unit_Core_Assert, Stream) {
  ASSERT_NE(&getAssertStream(), nullptr);

  std::stringstream ss;
  setAssertStream(ss);

  ASSERT_EQ(&getAssertStream(), &ss);
  ASSERT_STREQ(ss.str().c_str(), "");

  getAssertStream() << "hello, world\n";
  ASSERT_EQ(&getAssertStream(), &ss);
  ASSERT_STREQ(ss.str().c_str(), "hello, world\n");
}

TEST(Unit_Core_Assert, Die) {
  ASSERT_DEATH({
    _W_ASSERT_DIE();
  }, "");
}

TEST(Unit_Core_Assert, Unreachable) {
  setAssertStream(std::cerr);

  ASSERT_DEATH({ W_ASSERT_UNREACHABLE("Hey, now."); }, "Hey, now.");
}

TEST(Unit_Core_Assert, True) {
  setAssertStream(std::cerr);

  W_ASSERT_TRUE(true, "");

  ASSERT_DEATH({ W_ASSERT_TRUE(false, "You're an all star."); },
               "You're an all star.");
}

TEST(Unit_Core_Assert, False) {
  setAssertStream(std::cerr);

  W_ASSERT_FALSE(false, "");

  ASSERT_DEATH({ W_ASSERT_FALSE(true, "Get your game on,"); },
               "Get your game on,");
}

TEST(Unit_Core_Assert, Null) {
  setAssertStream(std::cerr);

  W_ASSERT_NULL(nullptr, "");

  int x;

  ASSERT_DEATH({ W_ASSERT_NULL(&x, "Go play!"); }, "Go play!");
}

TEST(Unit_Core_Assert, NonNull) {
  setAssertStream(std::cerr);

  int x;

  W_ASSERT_NONNULL(&x, "");

  ASSERT_DEATH({ W_ASSERT_NONNULL(nullptr, "Hey, now."); }, "Hey, now.");
}

TEST(Unit_Core_Assert, LT) {
  setAssertStream(std::cerr);

  W_ASSERT_LT(0, 1, "");

  W_ASSERT_LT(-1, 1, "");

  W_ASSERT_LT(-1, 0, "");

  ASSERT_DEATH({ W_ASSERT_LT(0, 0, "You're a rock star."); },
               "You're a rock star.");

  ASSERT_DEATH({ W_ASSERT_LT(1, 0, "Get your game on,"); },
               "Get your game on,");

  ASSERT_DEATH({ W_ASSERT_LT(1, -1, "Go play!"); }, "Go play!");
}

TEST(Unit_Core_Assert, LE) {
  setAssertStream(std::cerr);

  W_ASSERT_LE(0, 1, "");

  W_ASSERT_LE(-1, 1, "");

  W_ASSERT_LE(-1, 0, "");

  W_ASSERT_LE(0, 0, "");

  ASSERT_DEATH({ W_ASSERT_LE(1, 0, "It's a cool place,"); },
               "It's a cool place,");

  ASSERT_DEATH({ W_ASSERT_LE(1, -1, "And they say it gets colder."); },
               "And they say it gets colder.");
}

TEST(Unit_Core_Assert, GT) {
  setAssertStream(std::cerr);

  W_ASSERT_GT(1, 0, "");

  W_ASSERT_GT(1, -1, "");

  W_ASSERT_GT(0, -1, "");

  ASSERT_DEATH({ W_ASSERT_GT(0, 0, "Bundled up now,"); }, "Bundled up now,");

  ASSERT_DEATH({ W_ASSERT_GT(0, 1, "Wait till you get older."); },
               "Wait till you get older.");

  ASSERT_DEATH({ W_ASSERT_GT(-1, 1, "It's the medium back the big dipper,"); },
               "It's the medium back the big dipper,");
}

TEST(Unit_Core_Assert, GE) {
  setAssertStream(std::cerr);

  W_ASSERT_GE(1, 0, "");

  W_ASSERT_GE(1, -1, "");

  W_ASSERT_GE(0, -1, "");

  W_ASSERT_GE(0, 0, "");

  ASSERT_DEATH(
      { W_ASSERT_GE(0, 1, "Wonder why it's not the bad the big flipper."); },
      "Wonder why it's not the bad the big flipper.");

  ASSERT_DEATH({ W_ASSERT_GE(-1, 1, "The ice we skate"); }, "The ice we skate");
}

TEST(Unit_Core_Assert, ULT) {
  setAssertStream(std::cerr);

  W_ASSERT_ULT(0, 1, "");

  W_ASSERT_ULT(0, -1, "");

  ASSERT_DEATH({ W_ASSERT_ULT(0, 0, "Is getting pretty thin."); },
               "Is getting pretty thin.");

  ASSERT_DEATH({ W_ASSERT_ULT(1, 0, "Waters gettin' warm,"); },
               "Waters gettin' warm,");

  ASSERT_DEATH({ W_ASSERT_ULT(-1, 0, "Waters gettin' warm,"); },
               "Waters gettin' warm,");
}

TEST(Unit_Core_Assert, ULE) {
  setAssertStream(std::cerr);

  W_ASSERT_ULE(0, 1, "");

  W_ASSERT_ULE(0, -1, "");

  W_ASSERT_ULE(0, 0, "");

  ASSERT_DEATH({ W_ASSERT_ULE(1, 0, "Yeah, we might as well swim."); },
               "Yeah, we might as well swim.");

  ASSERT_DEATH({ W_ASSERT_ULE(-1, 0, "Yeah, we might as well swim."); },
               "Yeah, we might as well swim.");
}

TEST(Unit_Core_Assert, UGT) {
  setAssertStream(std::cerr);

  W_ASSERT_UGT(1, 0, "");

  W_ASSERT_UGT(-1, 0, "");

  ASSERT_DEATH({ W_ASSERT_UGT(0, 0, "World's on fire,"); }, "World's on fire,");

  ASSERT_DEATH({ W_ASSERT_UGT(0, 1, "How 'bout jaws."); }, "How 'bout jaws.");

  ASSERT_DEATH({ W_ASSERT_UGT(0, -1, "How 'bout jaws."); }, "How 'bout jaws.");
}

TEST(Unit_Core_Assert, UGE) {
  setAssertStream(std::cerr);

  W_ASSERT_UGE(1, 0, "");

  W_ASSERT_UGE(-1, 0, "");

  W_ASSERT_UGE(0, 0, "");

  ASSERT_DEATH({ W_ASSERT_UGE(0, 1, "That's the way I like it"); },
               "That's the way I like it");

  ASSERT_DEATH({ W_ASSERT_UGE(0, -1, "That's the way I like it"); },
               "That's the way I like it");
}

TEST(Unit_Core_Assert, NE) {
  setAssertStream(std::cerr);

  W_ASSERT_NE(0, 1, "");

  W_ASSERT_NE(0, -1, "");

  W_ASSERT_NE(-1, 1, "");

  ASSERT_DEATH({ W_ASSERT_NE(0, 0, "And I never get bored."); },
               "And I never get bored.");
}

TEST(Unit_Core_Assert, EQ) {
  setAssertStream(std::cerr);

  W_ASSERT_EQ(0, 0, "");

  ASSERT_DEATH({ W_ASSERT_EQ(0, 1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");

  ASSERT_DEATH({ W_ASSERT_EQ(0, -1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");

  ASSERT_DEATH({ W_ASSERT_EQ(1, -1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");
}
