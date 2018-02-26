#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Core/Literals.hpp>

using namespace whiskey;

TEST(Unit_Core_Literals, Bool) {
  std::stringstream ss;

  ss.str("");
  printLiteralBool(ss, true);
  ASSERT_STREQ("true", ss.str().c_str());

  ss.str("");
  printLiteralBool(ss, false);
  ASSERT_STREQ("false", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base2_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, 0, false);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, 0, false);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, 0, false);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, 0, false);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, 0, false);
  ASSERT_STREQ("111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, 0, false);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 2, 0, false);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base2_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, 5, false);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, 5, false);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, 5, false);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, 5, false);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, 5, false);
  ASSERT_STREQ("00111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, 5, false);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 2, 5, false);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base2_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, 0, true);
  ASSERT_STREQ("0b0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, 0, true);
  ASSERT_STREQ("0b1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, 0, true);
  ASSERT_STREQ("0b10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, 0, true);
  ASSERT_STREQ("0b11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, 0, true);
  ASSERT_STREQ("0b111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, 0, true);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 2, 0, true);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base2_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, 5, true);
  ASSERT_STREQ("0b00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, 5, true);
  ASSERT_STREQ("0b00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, 5, true);
  ASSERT_STREQ("0b00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, 5, true);
  ASSERT_STREQ("0b00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, 5, true);
  ASSERT_STREQ("0b00111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, 5, true);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 2, 5, true);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base8_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, 0, false);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, 0, false);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, 0, false);
  ASSERT_STREQ("7", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, 0, false);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, 0, false);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, 0, false);
  ASSERT_STREQ("20", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 8, 0, false);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base8_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, 5, false);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, 5, false);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, 5, false);
  ASSERT_STREQ("00007", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, 5, false);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, 5, false);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, 5, false);
  ASSERT_STREQ("00020", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 8, 5, false);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base8_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, 0, true);
  ASSERT_STREQ("00", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, 0, true);
  ASSERT_STREQ("01", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, 0, true);
  ASSERT_STREQ("07", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, 0, true);
  ASSERT_STREQ("010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, 0, true);
  ASSERT_STREQ("011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, 0, true);
  ASSERT_STREQ("020", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 8, 0, true);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base8_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, 5, true);
  ASSERT_STREQ("000000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, 5, true);
  ASSERT_STREQ("000001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, 5, true);
  ASSERT_STREQ("000007", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, 5, true);
  ASSERT_STREQ("000010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, 5, true);
  ASSERT_STREQ("000011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, 5, true);
  ASSERT_STREQ("000020", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 8, 5, true);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base10_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, 0, false);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, 0, false);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, 0, false);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, 0, false);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, 0, false);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, 0, false);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 10, 0, false);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base10_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, 5, false);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, 5, false);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, 5, false);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, 5, false);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, 5, false);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, 5, false);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 10, 5, false);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base10_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, 0, true);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, 0, true);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, 0, true);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, 0, true);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, 0, true);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, 0, true);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 10, 0, true);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base10_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, 5, true);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, 5, true);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, 5, true);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, 5, true);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, 5, true);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, 5, true);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 10, 5, true);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base16_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, 0, false);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, 0, false);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, 0, false);
  ASSERT_STREQ("f", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, 0, false);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, 0, false);
  ASSERT_STREQ("fe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, 0, false);
  ASSERT_STREQ("ff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 16, 0, false);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base16_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, 5, false);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, 5, false);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, 5, false);
  ASSERT_STREQ("0000f", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, 5, false);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, 5, false);
  ASSERT_STREQ("000fe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, 5, false);
  ASSERT_STREQ("000ff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 16, 5, false);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base16_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, 0, true);
  ASSERT_STREQ("0x0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, 0, true);
  ASSERT_STREQ("0x1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, 0, true);
  ASSERT_STREQ("0xf", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, 0, true);
  ASSERT_STREQ("0x10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, 0, true);
  ASSERT_STREQ("0xfe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, 0, true);
  ASSERT_STREQ("0xff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 16, 0, true);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_Literals, UInt_Base16_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, 5, true);
  ASSERT_STREQ("0x00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, 5, true);
  ASSERT_STREQ("0x00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, 5, true);
  ASSERT_STREQ("0x0000f", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, 5, true);
  ASSERT_STREQ("0x00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, 5, true);
  ASSERT_STREQ("0x000fe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, 5, true);
  ASSERT_STREQ("0x000ff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, static_cast<UInt64>(-1), 16, 5, true);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_Literals, Real_Precision1_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0L, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0L, 1, false);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0L, 1, false);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0L, 1, false);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0L, 1, false);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0L, 1, false);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1L, 1, false);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9L, 1, false);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5L, 1, false);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01L, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09L, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05L, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());
}

TEST(Unit_Core_Literals, Real_Precision1_Truncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0L, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0L, 1, true);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0L, 1, true);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0L, 1, true);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0L, 1, true);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0L, 1, true);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1L, 1, true);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9L, 1, true);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5L, 1, true);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01L, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09L, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05L, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());
}

TEST(Unit_Core_Literals, Real_Precision2_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0L, 2, false);
  ASSERT_STREQ("0.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0L, 2, false);
  ASSERT_STREQ("1.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0L, 2, false);
  ASSERT_STREQ("9.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0L, 2, false);
  ASSERT_STREQ("10.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0L, 2, false);
  ASSERT_STREQ("11.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0L, 2, false);
  ASSERT_STREQ("69420.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1L, 2, false);
  ASSERT_STREQ("0.10", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9L, 2, false);
  ASSERT_STREQ("0.90", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5L, 2, false);
  ASSERT_STREQ("0.50", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01L, 2, false);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09L, 2, false);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05L, 2, false);
  ASSERT_STREQ("0.05", ss.str().c_str());
}

TEST(Unit_Core_Literals, Real_Precision2_Truncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0L, 2, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0L, 2, true);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0L, 2, true);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0L, 2, true);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0L, 2, true);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0L, 2, true);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1L, 2, true);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9L, 2, true);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5L, 2, true);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01L, 2, true);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09L, 2, true);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05L, 2, true);
  ASSERT_STREQ("0.05", ss.str().c_str());
}

TEST(Unit_Core_Literals, Real_Precision5_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0L, 5, false);
  ASSERT_STREQ("0.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0L, 5, false);
  ASSERT_STREQ("1.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0L, 5, false);
  ASSERT_STREQ("9.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0L, 5, false);
  ASSERT_STREQ("10.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0L, 5, false);
  ASSERT_STREQ("11.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0L, 5, false);
  ASSERT_STREQ("69420.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1L, 5, false);
  ASSERT_STREQ("0.10000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9L, 5, false);
  ASSERT_STREQ("0.90000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5L, 5, false);
  ASSERT_STREQ("0.50000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01L, 5, false);
  ASSERT_STREQ("0.01000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09L, 5, false);
  ASSERT_STREQ("0.09000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05L, 5, false);
  ASSERT_STREQ("0.05000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.001L, 5, false);
  ASSERT_STREQ("0.00100", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.009L, 5, false);
  ASSERT_STREQ("0.00900", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.005L, 5, false);
  ASSERT_STREQ("0.00500", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0001L, 5, false);
  ASSERT_STREQ("0.00010", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0009L, 5, false);
  ASSERT_STREQ("0.00090", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0005L, 5, false);
  ASSERT_STREQ("0.00050", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00001L, 5, false);
  ASSERT_STREQ("0.00001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00009L, 5, false);
  ASSERT_STREQ("0.00009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00005L, 5, false);
  ASSERT_STREQ("0.00005", ss.str().c_str());
}

TEST(Unit_Core_Literals, Real_Precision5_Truncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0L, 5, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0L, 5, true);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0L, 5, true);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0L, 5, true);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0L, 5, true);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0L, 5, true);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1L, 5, true);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9L, 5, true);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5L, 5, true);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01L, 5, true);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09L, 5, true);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05L, 5, true);
  ASSERT_STREQ("0.05", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.001L, 5, true);
  ASSERT_STREQ("0.001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.009L, 5, true);
  ASSERT_STREQ("0.009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.005L, 5, true);
  ASSERT_STREQ("0.005", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0001L, 5, true);
  ASSERT_STREQ("0.0001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0009L, 5, true);
  ASSERT_STREQ("0.0009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0005L, 5, true);
  ASSERT_STREQ("0.0005", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00001L, 5, true);
  ASSERT_STREQ("0.00001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00009L, 5, true);
  ASSERT_STREQ("0.00009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00005L, 5, true);
  ASSERT_STREQ("0.00005", ss.str().c_str());
}

TEST(Unit_Core_Literals, Char) {
  std::stringstream ss;

  ss.str("");
  printLiteralChar(ss, '\0');
  ASSERT_STREQ("'\\0'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, 'a');
  ASSERT_STREQ("'a'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, '\a');
  ASSERT_STREQ("'\\a'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, '\033');
  ASSERT_STREQ("'\\e'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, 0xff & '\x80');
  ASSERT_STREQ("'\\x80'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, '\'');
  ASSERT_STREQ("'\\''", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, '\"');
  ASSERT_STREQ("'\"'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, '\\');
  ASSERT_STREQ("'\\\\'", ss.str().c_str());
}

TEST(Unit_Core_Literals, String) {
  std::stringstream ss;

  ss.str("");
  printLiteralString(ss, "");
  ASSERT_STREQ("\"\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\0");
  ASSERT_STREQ("\"\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "a");
  ASSERT_STREQ("\"a\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\a");
  ASSERT_STREQ("\"\\a\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\033");
  ASSERT_STREQ("\"\\e\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\x80");
  ASSERT_STREQ("\"\\x80\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\'");
  ASSERT_STREQ("\"'\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\"");
  ASSERT_STREQ("\"\\\"\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "\\");
  ASSERT_STREQ("\"\\\\\"", ss.str().c_str());

  ss.str("");
  printLiteralString(ss, "Hello, world.\n");
  ASSERT_STREQ("\"Hello, world.\\n\"", ss.str().c_str());
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_0) {
  uint64_t value;

  std::string str = "0b";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_1) {
  uint64_t value;

  std::string str = "0b0";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_2) {
  uint64_t value;

  std::string str = "0b1";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 1);
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_3) {
  uint64_t value;

  std::string str = "0b2";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_4) {
  uint64_t value;

  std::string str = "0b10";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 2);
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_5) {
  uint64_t value;

  std::string str = "0b11";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 3);
}

TEST(Unit_Core_Literals, Eval_UInt_Base2_6) {
  uint64_t value;

  std::string str = "0b10011011";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 155);
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_0) {
  uint64_t value;

  std::string str = "0";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_1) {
  uint64_t value;

  std::string str = "00";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_2) {
  uint64_t value;

  std::string str = "01";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 1);
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_3) {
  uint64_t value;

  std::string str = "07";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 7);
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_4) {
  uint64_t value;

  std::string str = "08";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_5) {
  uint64_t value;

  std::string str = "033";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 27);
}

TEST(Unit_Core_Literals, Eval_UInt_Base8_6) {
  uint64_t value;

  std::string str = "07777";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 4095);
}

TEST(Unit_Core_Literals, Eval_UInt_Base10_0) {
  uint64_t value;

  std::string str = "1";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 1);
}

TEST(Unit_Core_Literals, Eval_UInt_Base10_1) {
  uint64_t value;

  std::string str = "9";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 9);
}

TEST(Unit_Core_Literals, Eval_UInt_Base10_2) {
  uint64_t value;

  std::string str = "19";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 19);
}

TEST(Unit_Core_Literals, Eval_UInt_Base10_3) {
  uint64_t value;

  std::string str = "123456789";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 123456789);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_0) {
  uint64_t value;

  std::string str = "0x";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_1) {
  uint64_t value;

  std::string str = "0x0";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_2) {
  uint64_t value;

  std::string str = "0x9";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 9);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_3) {
  uint64_t value;

  std::string str = "0xa";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 10);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_4) {
  uint64_t value;

  std::string str = "0xA";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 10);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_5) {
  uint64_t value;

  std::string str = "0xf";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 15);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_6) {
  uint64_t value;

  std::string str = "0xF";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 15);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_7) {
  uint64_t value;

  std::string str = "0xdeadbeef";

  ASSERT_TRUE(evalLiteralUInt(str, value));
  ASSERT_EQ(value, 0xdeadbeef);
}

TEST(Unit_Core_Literals, Eval_UInt_Base16_8) {
  uint64_t value;

  std::string str = "0xgeadbeef";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_UInt_NoBase_0) {
  uint64_t value;

  std::string str = "a";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_UInt_NoBase_1) {
  uint64_t value;

  std::string str = "5a";

  ASSERT_FALSE(evalLiteralUInt(str, value));
}

TEST(Unit_Core_Literals, Eval_Real_0) {
  long double value;

  std::string str = "0.0";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Core_Literals, Eval_Real_1) {
  long double value;

  std::string str = ".0";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Core_Literals, Eval_Real_2) {
  long double value;

  std::string str = "0.";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Core_Literals, Eval_Real_3) {
  long double value;

  std::string str = ".";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Core_Literals, Eval_Real_4) {
  long double value;

  std::string str = "69.";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 69.0);
}

TEST(Unit_Core_Literals, Eval_Real_5) {
  long double value;

  std::string str = ".420";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 0.420);
}

TEST(Unit_Core_Literals, Eval_Real_6) {
  long double value;

  std::string str = "69.420";

  ASSERT_TRUE(evalLiteralReal(str, value));
  ASSERT_DOUBLE_EQ(value, 69.420);
}

TEST(Unit_Core_Literals, Eval_Char_0) {
  char32_t value;

  std::string str = "'a'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, 'a');
}

TEST(Unit_Core_Literals, Eval_Char_1) {
  char32_t value;

  std::string str = "'a";

  ASSERT_FALSE(evalLiteralChar(str, value));
}

TEST(Unit_Core_Literals, Eval_Char_2) {
  char32_t value;

  std::string str = "a'";

  ASSERT_FALSE(evalLiteralChar(str, value));
}

TEST(Unit_Core_Literals, Eval_Char_3) {
  char32_t value;

  std::string str = "''";

  ASSERT_FALSE(evalLiteralChar(str, value));
}

TEST(Unit_Core_Literals, Eval_Char_4) {
  char32_t value;

  std::string str = "'";

  ASSERT_FALSE(evalLiteralChar(str, value));
}

TEST(Unit_Core_Literals, Eval_Char_5) {
  char32_t value;

  std::string str = "'\\a'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\a');
}

TEST(Unit_Core_Literals, Eval_Char_6) {
  char32_t value;

  std::string str = "'\\0'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Core_Literals, Eval_Char_7) {
  char32_t value;

  std::string str = "'\\7'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\7');
}

TEST(Unit_Core_Literals, Eval_Char_8) {
  char32_t value;

  std::string str = "'\\00'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Core_Literals, Eval_Char_9) {
  char32_t value;

  std::string str = "'\\000'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Core_Literals, Eval_Char_10) {
  char32_t value;

  std::string str = "'\\177'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\177');
}

TEST(Unit_Core_Literals, Eval_Char_11) {
  char32_t value;

  std::string str = "'\\x00'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Core_Literals, Eval_Char_12) {
  char32_t value;

  std::string str = "'\\x0'";

  ASSERT_FALSE(evalLiteralChar(str, value));
}

TEST(Unit_Core_Literals, Eval_Char_13) {
  char32_t value;

  std::string str = "'\\x'";

  ASSERT_FALSE(evalLiteralChar(str, value));
}

TEST(Unit_Core_Literals, Eval_Char_25) {
  char32_t value;

  std::string str = "'\\\\'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\\');
}

TEST(Unit_Core_Literals, Eval_Char_26) {
  char32_t value;

  std::string str = "'\\''";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '\'');
}

TEST(Unit_Core_Literals, Eval_Char_27) {
  char32_t value;

  std::string str = "'\"'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '"');
}

TEST(Unit_Core_Literals, Eval_Char_28) {
  char32_t value;

  std::string str = "'\\?'";

  ASSERT_TRUE(evalLiteralChar(str, value));
  ASSERT_EQ(value, '?');
}

TEST(Unit_Core_Literals, Eval_String_0) {
  std::string value;

  std::string str = "\"a\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "a");
}

TEST(Unit_Core_Literals, Eval_String_1) {
  std::string value;

  std::string str = "\"a";

  ASSERT_FALSE(evalLiteralString(str, value));
}

TEST(Unit_Core_Literals, Eval_String_2) {
  std::string value;

  std::string str = "a\"";

  ASSERT_FALSE(evalLiteralString(str, value));
}

TEST(Unit_Core_Literals, Eval_String_3) {
  std::string value;

  std::string str = "\"\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "");
}

TEST(Unit_Core_Literals, Eval_String_4) {
  std::string value;

  std::string str = "\"";

  ASSERT_FALSE(evalLiteralString(str, value));
}

TEST(Unit_Core_Literals, Eval_String_5) {
  std::string value;

  std::string str = "\"\\a\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\a");
}

TEST(Unit_Core_Literals, Eval_String_6) {
  std::string value;

  std::string str = "\"\\0\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Core_Literals, Eval_String_7) {
  std::string value;

  std::string str = "\"\\7\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\7");
}

TEST(Unit_Core_Literals, Eval_String_8) {
  std::string value;

  std::string str = "\"\\00\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Core_Literals, Eval_String_9) {
  std::string value;

  std::string str = "\"\\000\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Core_Literals, Eval_String_10) {
  std::string value;

  std::string str = "\"\\177\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\177");
}

TEST(Unit_Core_Literals, Eval_String_11) {
  std::string value;

  std::string str = "\"\\x00\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Core_Literals, Eval_String_12) {
  std::string value;

  std::string str = "\"\\x0\"";

  ASSERT_FALSE(evalLiteralString(str, value));
}

TEST(Unit_Core_Literals, Eval_String_13) {
  std::string value;

  std::string str = "\"\\x\"";

  ASSERT_FALSE(evalLiteralString(str, value));
}

TEST(Unit_Core_Literals, Eval_String_25) {
  std::string value;

  std::string str = "\"\\\\\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\\");
}

TEST(Unit_Core_Literals, Eval_String_26) {
  std::string value;

  std::string str = "\"\\'\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\'");
}

TEST(Unit_Core_Literals, Eval_String_27) {
  std::string value;

  std::string str = "\"\\\"\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "\"");
}

TEST(Unit_Core_Literals, Eval_String_28) {
  std::string value;

  std::string str = "\"\\?\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "?");
}

TEST(Unit_Core_Literals, Eval_String_29) {
  std::string value;

  std::string str = "\"Hello, world.\\n\"";

  ASSERT_TRUE(evalLiteralString(str, value));
  ASSERT_STREQ(value.c_str(), "Hello, world.\n");
}
