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
  ASSERT_NE(&getAssertOStream(AssertMode::Internal), nullptr);
  ASSERT_NE(&getAssertOStream(AssertMode::Test), nullptr);

  std::stringstream ss0;
  setAssertOStream(AssertMode::Internal, ss0);

  std::stringstream ss1;
  setAssertOStream(AssertMode::Test, ss1);

  ASSERT_EQ(&getAssertOStream(AssertMode::Internal), &ss0);
  ASSERT_STREQ(ss0.str().c_str(), "");

  ASSERT_EQ(&getAssertOStream(AssertMode::Test), &ss1);
  ASSERT_STREQ(ss1.str().c_str(), "");

  getAssertOStream(AssertMode::Internal) << "hello, world\n";
  ASSERT_EQ(&getAssertOStream(AssertMode::Internal), &ss0);
  ASSERT_STREQ(ss0.str().c_str(), "hello, world\n");

  getAssertOStream(AssertMode::Test) << "goodbye, world\n";
  ASSERT_EQ(&getAssertOStream(AssertMode::Test), &ss1);
  ASSERT_STREQ(ss1.str().c_str(), "goodbye, world\n");
}

TEST(Unit_Core_Assert, Die) {
  ASSERT_DEATH({ failAssertDie(); }, "");
}

TEST(Unit_Core_Assert, Unreachable) {
  setAssertOStream(AssertMode::Internal, std::cerr);

  ASSERT_DEATH({ W_ASSERT_UNREACHABLE("Hey, now."); }, "Hey, now.");
}

TEST(Unit_Core_Assert, True) {
  setAssertOStream(AssertMode::Internal, std::cerr);

  W_ASSERT_TRUE(true, "");

  ASSERT_DEATH({ W_ASSERT_TRUE(false, "You're an all star."); },
               "You're an all star.");
}

TEST(Unit_Core_Assert, False) {
  setAssertOStream(AssertMode::Internal, std::cerr);

  W_ASSERT_FALSE(false, "");

  ASSERT_DEATH({ W_ASSERT_FALSE(true, "Get your game on,"); },
               "Get your game on,");
}

TEST(Unit_Core_Assert, Null) {
  setAssertOStream(AssertMode::Internal, std::cerr);

  W_ASSERT_NULL(static_cast<void *>(nullptr), "");

  int x;

  ASSERT_DEATH({ W_ASSERT_NULL(&x, "Go play!"); }, "Go play!");
}

TEST(Unit_Core_Assert, NonNull) {
  setAssertOStream(AssertMode::Internal, std::cerr);

  int x;

  W_ASSERT_NONNULL(&x, "");

  ASSERT_DEATH({ W_ASSERT_NONNULL(static_cast<void *>(nullptr), "Hey, now."); }, "Hey, now.");
}

TEST(Unit_Core_Assert, LT) {
  setAssertOStream(AssertMode::Internal, std::cerr);

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
  setAssertOStream(AssertMode::Internal, std::cerr);

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
  setAssertOStream(AssertMode::Internal, std::cerr);

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
  setAssertOStream(AssertMode::Internal, std::cerr);

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
  setAssertOStream(AssertMode::Internal, std::cerr);

  W_ASSERT_NE(0, 1, "");

  W_ASSERT_NE(0, -1, "");

  W_ASSERT_NE(-1, 1, "");

  ASSERT_DEATH({ W_ASSERT_NE(0, 0, "And I never get bored."); },
               "And I never get bored.");
}

TEST(Unit_Core_Assert, EQ) {
  setAssertOStream(AssertMode::Internal, std::cerr);

  W_ASSERT_EQ(0, 0, "");

  ASSERT_DEATH({ W_ASSERT_EQ(0, 1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");

  ASSERT_DEATH({ W_ASSERT_EQ(0, -1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");

  ASSERT_DEATH({ W_ASSERT_EQ(1, -1, "Do the chorus again lol xD"); },
               "Do the chorus again lol xD");
}

TEST(Unit_Core_Assert, Test_Unreachable) {
  setAssertOStream(AssertMode::Test, std::cerr);

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_UNREACHABLE("Hey, now.");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_True) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_TRUE(true, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_TRUE(false, "You're an all star.");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_False) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_FALSE(false, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_FALSE(true, "Get your game on,");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_LT) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_LT(0, 1, "");

  W_TEST_ASSERT_LT(-1, 1, "");

  W_TEST_ASSERT_LT(-1, 0, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_LT(0, 0, "You're a rock star.");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_LT(1, 0, "Get your game on,");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_LT(1, -1, "Go play!");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_LE) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_LE(0, 1, "");

  W_TEST_ASSERT_LE(-1, 1, "");

  W_TEST_ASSERT_LE(-1, 0, "");

  W_TEST_ASSERT_LE(0, 0, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_LE(1, 0, "It's a cool place,");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_LE(1, -1, "And they say it gets colder.");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_GT) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_GT(1, 0, "");

  W_TEST_ASSERT_GT(1, -1, "");

  W_TEST_ASSERT_GT(0, -1, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_GT(0, 0, "Bundled up now,");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_GT(0, 1, "Wait till you get older.");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_GT(-1, 1, "It's the medium back the big dipper,");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_GE) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_GE(1, 0, "");

  W_TEST_ASSERT_GE(1, -1, "");

  W_TEST_ASSERT_GE(0, -1, "");

  W_TEST_ASSERT_GE(0, 0, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_GE(0, 1, "Wonder why it's not the bad the big flipper.");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_GE(-1, 1, "The ice we skate");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_NE) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_NE(0, 1, "");

  W_TEST_ASSERT_NE(0, -1, "");

  W_TEST_ASSERT_NE(-1, 1, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_NE(0, 0, "And I never get bored.");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}

TEST(Unit_Core_Assert, Test_EQ) {
  setAssertOStream(AssertMode::Test, std::cerr);

  W_TEST_ASSERT_EQ(0, 0, "");

  size_t before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_EQ(0, 1, "Do the chorus again lol xD");
  size_t after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_EQ(0, -1, "Do the chorus again lol xD");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);

  before = getNAssertFailures(AssertMode::Test);
  W_TEST_ASSERT_EQ(1, -1, "Do the chorus again lol xD");
  after = getNAssertFailures(AssertMode::Test);

  ASSERT_EQ(after - before, 1);
}
