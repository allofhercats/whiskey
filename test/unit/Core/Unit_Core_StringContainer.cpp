#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Core/StringContainer.hpp>

using namespace whiskey;

TEST(Unit_Core_StringContainer, Mutable) {
  StringContainer s0 = "hello, world.\n";

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");

  s0.getData8()[0] = 'm';

  ASSERT_STREQ(s0.getData8(), "mello, world.\n");
}

TEST(Unit_Core_StringContainer, Copy) {
  StringContainer s0 = "hello, world.\n";
  StringContainer s1 = s0;

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");
  ASSERT_STREQ(s1.getData8(), "hello, world.\n");

  s0.getData8()[4] = 'a';

  ASSERT_STREQ(s0.getData8(), "hella, world.\n");
  ASSERT_STREQ(s1.getData8(), "hello, world.\n");
}

TEST(Unit_Core_StringContainer, Move) {
  StringContainer s0 = "hello, world.\n";
  StringContainer s1 = std::move(s0);

  ASSERT_FALSE(s0.isGood());
  ASSERT_EQ(s0.size(), 0);
  ASSERT_STREQ(s1.getData8(), "hello, world.\n");
}

TEST(Unit_Core_StringContainer, DecreaseCapacity) {
  StringContainer s0 = "hello, world.\n";

  ASSERT_DEATH({ s0.reserve(5); }, "");

  s0.resize(5);

  ASSERT_EQ(s0.size(), 5);

  ASSERT_DEATH({ s0.reserve(4); }, "");

  s0.reserve(5);

  ASSERT_EQ(s0.size(), 5);
}

TEST(Unit_Core_StringContainer, IncreaseCapacity) {
  StringContainer s0 = "hello, world.\n";

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");

  s0.reserve(1024);

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld8_Null) {
  StringContainer s0 = "hello, world.\n";

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");
  ASSERT_EQ(s0.size(), 14);

  s0.push_back(0);

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");
  ASSERT_EQ(s0.size(), 15);
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld8_A) {
  StringContainer s0 = "hello, world.\n";

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");
  ASSERT_EQ(s0.size(), 14);

  s0.push_back('A');

  ASSERT_STREQ(s0.getData8(), "hello, world.\nA");
  ASSERT_EQ(s0.size(), 15);
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld8_A100000) {
  StringContainer s0 = "hello, world.\n";

  ASSERT_STREQ(s0.getData8(), "hello, world.\n");
  ASSERT_EQ(s0.size(), 14);

  for (int i = 0; i < 100000; i++) {
    s0.push_back('A');
  }

  ASSERT_EQ(s0.size(), 100014);
  for (int i = 0; i < 100000; i++) {
    ASSERT_EQ(s0.getData8()[i + 14], 'A');
  }
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld16_Null) {
  StringContainer s0 = u"hello, world.\n";

  ASSERT_EQ(s0.size(), 14);

  s0.push_back(0);

  ASSERT_EQ(s0.size(), 15);
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld16_A) {
  StringContainer s0 = u"hello, world.\n";

  ASSERT_EQ(s0.size(), 14);

  s0.push_back('A');

  ASSERT_EQ(s0.size(), 15);
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld16_A100000) {
  StringContainer s0 = u"hello, world.\n";

  ASSERT_EQ(s0.size(), 14);

  for (int i = 0; i < 100000; i++) {
    s0.push_back('A');
  }

  ASSERT_EQ(s0.size(), 100014);
  for (int i = 0; i < 100000; i++) {
    ASSERT_EQ(s0.getData16()[i + 14], 'A');
  }
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld32_Null) {
  StringContainer s0 = U"hello, world.\n";

  ASSERT_EQ(s0.size(), 14);

  s0.push_back(0);

  ASSERT_EQ(s0.size(), 15);
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld32_A) {
  StringContainer s0 = U"hello, world.\n";

  ASSERT_EQ(s0.size(), 14);

  s0.push_back('A');

  ASSERT_EQ(s0.size(), 15);
}

TEST(Unit_Core_StringContainer, Append_ToHelloWorld32_A100000) {
  StringContainer s0 = U"hello, world.\n";

  ASSERT_EQ(s0.size(), 14);

  for (int i = 0; i < 100000; i++) {
    s0.push_back('A');
  }

  ASSERT_EQ(s0.size(), 100014);
  for (int i = 0; i < 100000; i++) {
    ASSERT_EQ(s0.getData32()[i + 14], 'A');
  }
}
