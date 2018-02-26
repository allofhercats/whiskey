#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Core/Assert.hpp>

using namespace whiskey;

TEST(Unit_Core_Assert, Stream) {
  ASSERT_NE(&getAssertOStream(), nullptr);

  std::stringstream ss;
  setAssertOStream(ss);

  ASSERT_EQ(&getAssertOStream(), &ss);
  ASSERT_STREQ(ss.str().c_str(), "");

  getAssertOStream() << "hello, world\n";
  ASSERT_EQ(&getAssertOStream(), &ss);
  ASSERT_STREQ(ss.str().c_str(), "hello, world\n");
}

TEST(Unit_Core_Assert, Die) {
  ASSERT_DEATH({ dieOnAssertFail(); }, "");
}

TEST(Unit_Core_Assert, Unreachable) {
  setAssertOStream(std::cerr);

  ASSERT_DEATH({ W_ASSERT_UNREACHABLE("Hey, now."); }, "Hey, now.");
}

TEST(Unit_Core_Assert, True) {
  setAssertOStream(std::cerr);

  W_ASSERT_TRUE(true, "");

  ASSERT_DEATH({ W_ASSERT_TRUE(false, "You're an all star."); },
               "You're an all star.");
}

TEST(Unit_Core_Assert, False) {
  setAssertOStream(std::cerr);

  W_ASSERT_FALSE(false, "");

  ASSERT_DEATH({ W_ASSERT_FALSE(true, "Get your game on,"); },
               "Get your game on,");
}

TEST(Unit_Core_Assert, Null) {
  setAssertOStream(std::cerr);

  W_ASSERT_NULL(static_cast<void *>(nullptr), "");

  int x;

  ASSERT_DEATH({ W_ASSERT_NULL(&x, "Go play!"); }, "Go play!");
}

TEST(Unit_Core_Assert, NonNull) {
  setAssertOStream(std::cerr);

  int x;

  W_ASSERT_NONNULL(&x, "");

  ASSERT_DEATH({ W_ASSERT_NONNULL(static_cast<void *>(nullptr), "Hey, now."); }, "Hey, now.");
}

TEST(Unit_Core_Assert, LT) {
  setAssertOStream(std::cerr);

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
  setAssertOStream(std::cerr);

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
  setAssertOStream(std::cerr);

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
  setAssertOStream(std::cerr);

  W_ASSERT_GE(1, 0, "");

  W_ASSERT_GE(1, -1, "");

  W_ASSERT_GE(0, -1, "");

  W_ASSERT_GE(0, 0, "");

  ASSERT_DEATH(
      { W_ASSERT_GE(0, 1, "Wonder why it's not the bad the big flipper."); },
      "Wonder why it's not the bad the big flipper.");

  ASSERT_DEATH({ W_ASSERT_GE(-1, 1, "The ice we skate"); }, "The ice we skate");
}

TEST(Unit_Core_Assert, NE) {
  setAssertOStream(std::cerr);

  W_ASSERT_NE(0, 1, "");

  W_ASSERT_NE(0, -1, "");

  W_ASSERT_NE(-1, 1, "");

  ASSERT_DEATH({ W_ASSERT_NE(0, 0, "And I never get bored."); },
               "And I never get bored.");
}

TEST(Unit_Core_Assert, EQ) {
  setAssertOStream(std::cerr);

  W_ASSERT_EQ(0, 0, "");

  ASSERT_DEATH({ W_ASSERT_EQ(0, 1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");

  ASSERT_DEATH({ W_ASSERT_EQ(0, -1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");

  ASSERT_DEATH({ W_ASSERT_EQ(1, -1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");
}
