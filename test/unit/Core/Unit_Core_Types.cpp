#include <gtest/gtest.h>

#include <whiskey/Core/Types.hpp>

using namespace whiskey;

TEST(Unit_Core_Types, GetNDigits_Base2) {
  ASSERT_EQ(getNDigits(0, 2), 1);
  ASSERT_EQ(getNDigits(1, 2), 1);
  ASSERT_EQ(getNDigits(2, 2), 2);
  ASSERT_EQ(getNDigits(3, 2), 2);
  ASSERT_EQ(getNDigits(4, 2), 3);
  ASSERT_EQ(getNDigits(7, 2), 3);
}

TEST(Unit_Core_Types, GetNDigits_Base8) {
  ASSERT_EQ(getNDigits(0, 8), 1);
  ASSERT_EQ(getNDigits(7, 8), 1);
  ASSERT_EQ(getNDigits(8, 8), 2);
  ASSERT_EQ(getNDigits(63, 8), 2);
  ASSERT_EQ(getNDigits(64, 8), 3);
  ASSERT_EQ(getNDigits(511, 8), 3);
}

TEST(Unit_Core_Types, GetNDigits_Base10) {
  ASSERT_EQ(getNDigits(0, 10), 1);
  ASSERT_EQ(getNDigits(9, 10), 1);
  ASSERT_EQ(getNDigits(10, 10), 2);
  ASSERT_EQ(getNDigits(99, 10), 2);
  ASSERT_EQ(getNDigits(100, 10), 3);
  ASSERT_EQ(getNDigits(999, 10), 3);
}

TEST(Unit_Core_Types, GetNDigits_Base16) {
  ASSERT_EQ(getNDigits(0, 16), 1);
  ASSERT_EQ(getNDigits(15, 16), 1);
  ASSERT_EQ(getNDigits(16, 16), 2);
  ASSERT_EQ(getNDigits(255, 16), 2);
  ASSERT_EQ(getNDigits(256, 16), 3);
  ASSERT_EQ(getNDigits(4095, 16), 3);
}
