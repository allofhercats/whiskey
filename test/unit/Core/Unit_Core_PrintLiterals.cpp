#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Core/PrintLiterals.hpp>

using namespace whiskey;

TEST(Unit_Core_PrintLiterals, Bool) {
  std::stringstream ss;

  ss.str("");
  printLiteralBool(ss, true);
  ASSERT_STREQ("true", ss.str().c_str());

  ss.str("");
  printLiteralBool(ss, false);
  ASSERT_STREQ("false", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base2_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, false, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, false, 0);
  ASSERT_STREQ("111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, false, 0);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 2, false, 0);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base2_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, false, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, false, 5);
  ASSERT_STREQ("00111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, false, 5);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 2, false, 5);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base2_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, true, 0);
  ASSERT_STREQ("0b0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, true, 0);
  ASSERT_STREQ("0b1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, true, 0);
  ASSERT_STREQ("0b10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, true, 0);
  ASSERT_STREQ("0b11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, true, 0);
  ASSERT_STREQ("0b111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, true, 0);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 2, true, 0);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base2_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 2, true, 5);
  ASSERT_STREQ("0b00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 2, true, 5);
  ASSERT_STREQ("0b00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 2, 2, true, 5);
  ASSERT_STREQ("0b00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 3, 2, true, 5);
  ASSERT_STREQ("0b00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 2, true, 5);
  ASSERT_STREQ("0b00111", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 2, true, 5);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 2, true, 5);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base8_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, false, 0);
  ASSERT_STREQ("7", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, false, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, false, 0);
  ASSERT_STREQ("20", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 8, false, 0);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base8_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, false, 5);
  ASSERT_STREQ("00007", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, false, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, false, 5);
  ASSERT_STREQ("00020", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 8, false, 5);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base8_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, true, 0);
  ASSERT_STREQ("00", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, true, 0);
  ASSERT_STREQ("01", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, true, 0);
  ASSERT_STREQ("07", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, true, 0);
  ASSERT_STREQ("010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, true, 0);
  ASSERT_STREQ("011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, true, 0);
  ASSERT_STREQ("020", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 8, true, 0);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base8_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 8, true, 5);
  ASSERT_STREQ("000000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 8, true, 5);
  ASSERT_STREQ("000001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 7, 8, true, 5);
  ASSERT_STREQ("000007", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 8, 8, true, 5);
  ASSERT_STREQ("000010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 8, true, 5);
  ASSERT_STREQ("000011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 8, true, 5);
  ASSERT_STREQ("000020", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 8, true, 5);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base10_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, false, 0);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, false, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, false, 0);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 10, false, 0);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base10_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, false, 5);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, false, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, false, 5);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 10, false, 5);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base10_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, true, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, true, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, true, 0);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, true, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, true, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, true, 0);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 10, true, 0);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base10_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 10, true, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 10, true, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 9, 10, true, 5);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 10, 10, true, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 11, 10, true, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 69420, 10, true, 5);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 10, true, 5);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base16_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, false, 0);
  ASSERT_STREQ("f", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, false, 0);
  ASSERT_STREQ("fe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, false, 0);
  ASSERT_STREQ("ff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 16, false, 0);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base16_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, false, 5);
  ASSERT_STREQ("0000f", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, false, 5);
  ASSERT_STREQ("000fe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, false, 5);
  ASSERT_STREQ("000ff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 16, false, 5);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base16_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, true, 0);
  ASSERT_STREQ("0x0", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, true, 0);
  ASSERT_STREQ("0x1", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, true, 0);
  ASSERT_STREQ("0xf", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, true, 0);
  ASSERT_STREQ("0x10", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, true, 0);
  ASSERT_STREQ("0xfe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, true, 0);
  ASSERT_STREQ("0xff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 16, true, 0);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, UInt_Base16_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralUInt(ss, 0, 16, true, 5);
  ASSERT_STREQ("0x00000", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 1, 16, true, 5);
  ASSERT_STREQ("0x00001", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 15, 16, true, 5);
  ASSERT_STREQ("0x0000f", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 16, 16, true, 5);
  ASSERT_STREQ("0x00010", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 254, 16, true, 5);
  ASSERT_STREQ("0x000fe", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, 255, 16, true, 5);
  ASSERT_STREQ("0x000ff", ss.str().c_str());

  ss.str("");
  printLiteralUInt(ss, -1, 16, true, 5);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base2_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 2, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 2, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 2, 2, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 3, 2, false, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 2, false, 5);
  ASSERT_STREQ("00111", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 2, false, 5);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 2, false, 5);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base2_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 2, true, 0);
  ASSERT_STREQ("0b0", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 2, true, 0);
  ASSERT_STREQ("0b1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 2, 2, true, 0);
  ASSERT_STREQ("0b10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 3, 2, true, 0);
  ASSERT_STREQ("0b11", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 2, true, 0);
  ASSERT_STREQ("0b111", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 2, true, 0);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 2, true, 0);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base2_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 2, true, 5);
  ASSERT_STREQ("0b00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 2, true, 5);
  ASSERT_STREQ("0b00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 2, 2, true, 5);
  ASSERT_STREQ("0b00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 3, 2, true, 5);
  ASSERT_STREQ("0b00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 2, true, 5);
  ASSERT_STREQ("0b00111", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 2, true, 5);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 2, true, 5);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base8_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 8, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 8, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 8, false, 0);
  ASSERT_STREQ("7", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 8, 8, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 8, false, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 8, false, 0);
  ASSERT_STREQ("20", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 8, false, 0);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base8_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 8, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 8, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 8, false, 5);
  ASSERT_STREQ("00007", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 8, 8, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 8, false, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 8, false, 5);
  ASSERT_STREQ("00020", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 8, false, 5);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base8_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 8, true, 0);
  ASSERT_STREQ("00", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 8, true, 0);
  ASSERT_STREQ("01", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 8, true, 0);
  ASSERT_STREQ("07", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 8, 8, true, 0);
  ASSERT_STREQ("010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 8, true, 0);
  ASSERT_STREQ("011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 8, true, 0);
  ASSERT_STREQ("020", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 8, true, 0);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base8_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 8, true, 5);
  ASSERT_STREQ("000000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 8, true, 5);
  ASSERT_STREQ("000001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 7, 8, true, 5);
  ASSERT_STREQ("000007", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 8, 8, true, 5);
  ASSERT_STREQ("000010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 8, true, 5);
  ASSERT_STREQ("000011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 8, true, 5);
  ASSERT_STREQ("000020", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 8, true, 5);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 10, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 10, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 10, false, 0);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 10, 10, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 11, 10, false, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 69420, 10, false, 0);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 10, false, 0);
  ASSERT_STREQ("-1", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 10, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 10, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 10, false, 5);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 10, 10, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 11, 10, false, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 69420, 10, false, 5);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 10, false, 5);
  ASSERT_STREQ("-00001", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 10, true, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 10, true, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 10, true, 0);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 10, 10, true, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 11, 10, true, 0);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 69420, 10, true, 0);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 10, true, 0);
  ASSERT_STREQ("-1", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 10, true, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 10, true, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 9, 10, true, 5);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 10, 10, true, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 11, 10, true, 5);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 69420, 10, true, 5);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 10, true, 5);
  ASSERT_STREQ("-00001", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_NoPrefix_Width0_Negative) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, -1, 10, false, 0);
  ASSERT_STREQ("-1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -9, 10, false, 0);
  ASSERT_STREQ("-9", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -10, 10, false, 0);
  ASSERT_STREQ("-10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -11, 10, false, 0);
  ASSERT_STREQ("-11", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -69420, 10, false, 0);
  ASSERT_STREQ("-69420", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_NoPrefix_Width5_Negative) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, -1, 10, false, 5);
  ASSERT_STREQ("-00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -9, 10, false, 5);
  ASSERT_STREQ("-00009", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -10, 10, false, 5);
  ASSERT_STREQ("-00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -11, 10, false, 5);
  ASSERT_STREQ("-00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -69420, 10, false, 5);
  ASSERT_STREQ("-69420", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_Prefix_Width0_Negative) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, -1, 10, true, 0);
  ASSERT_STREQ("-1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -9, 10, true, 0);
  ASSERT_STREQ("-9", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -10, 10, true, 0);
  ASSERT_STREQ("-10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -11, 10, true, 0);
  ASSERT_STREQ("-11", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -69420, 10, true, 0);
  ASSERT_STREQ("-69420", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base10_Prefix_Width5_Negative) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, -1, 10, true, 5);
  ASSERT_STREQ("-00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -9, 10, true, 5);
  ASSERT_STREQ("-00009", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -10, 10, true, 5);
  ASSERT_STREQ("-00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -11, 10, true, 5);
  ASSERT_STREQ("-00011", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -69420, 10, true, 5);
  ASSERT_STREQ("-69420", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base16_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 16, false, 0);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 16, false, 0);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 15, 16, false, 0);
  ASSERT_STREQ("f", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 16, false, 0);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 254, 16, false, 0);
  ASSERT_STREQ("fe", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 255, 16, false, 0);
  ASSERT_STREQ("ff", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 16, false, 0);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base16_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 16, false, 5);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 16, false, 5);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 15, 16, false, 5);
  ASSERT_STREQ("0000f", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 16, false, 5);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 254, 16, false, 5);
  ASSERT_STREQ("000fe", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 255, 16, false, 5);
  ASSERT_STREQ("000ff", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 16, false, 5);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base16_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 16, true, 0);
  ASSERT_STREQ("0x0", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 16, true, 0);
  ASSERT_STREQ("0x1", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 15, 16, true, 0);
  ASSERT_STREQ("0xf", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 16, true, 0);
  ASSERT_STREQ("0x10", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 254, 16, true, 0);
  ASSERT_STREQ("0xfe", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 255, 16, true, 0);
  ASSERT_STREQ("0xff", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 16, true, 0);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Int_Base16_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  printLiteralInt(ss, 0, 16, true, 5);
  ASSERT_STREQ("0x00000", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 1, 16, true, 5);
  ASSERT_STREQ("0x00001", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 15, 16, true, 5);
  ASSERT_STREQ("0x0000f", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 16, 16, true, 5);
  ASSERT_STREQ("0x00010", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 254, 16, true, 5);
  ASSERT_STREQ("0x000fe", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, 255, 16, true, 5);
  ASSERT_STREQ("0x000ff", ss.str().c_str());

  ss.str("");
  printLiteralInt(ss, -1, 16, true, 5);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Real_Precision1_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0, 1, false);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0, 1, false);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0, 1, false);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0, 1, false);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0, 1, false);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1, 1, false);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9, 1, false);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5, 1, false);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05, 1, false);
  ASSERT_STREQ("0.0", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Real_Precision1_Truncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0, 1, true);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0, 1, true);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0, 1, true);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0, 1, true);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0, 1, true);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1, 1, true);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9, 1, true);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5, 1, true);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05, 1, true);
  ASSERT_STREQ("0.0", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Real_Precision2_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0, 2, false);
  ASSERT_STREQ("0.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0, 2, false);
  ASSERT_STREQ("1.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0, 2, false);
  ASSERT_STREQ("9.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0, 2, false);
  ASSERT_STREQ("10.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0, 2, false);
  ASSERT_STREQ("11.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0, 2, false);
  ASSERT_STREQ("69420.00", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1, 2, false);
  ASSERT_STREQ("0.10", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9, 2, false);
  ASSERT_STREQ("0.90", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5, 2, false);
  ASSERT_STREQ("0.50", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01, 2, false);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09, 2, false);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05, 2, false);
  ASSERT_STREQ("0.05", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Real_Precision2_Truncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0, 2, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0, 2, true);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0, 2, true);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0, 2, true);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0, 2, true);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0, 2, true);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1, 2, true);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9, 2, true);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5, 2, true);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01, 2, true);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09, 2, true);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05, 2, true);
  ASSERT_STREQ("0.05", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Real_Precision5_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0, 5, false);
  ASSERT_STREQ("0.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0, 5, false);
  ASSERT_STREQ("1.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0, 5, false);
  ASSERT_STREQ("9.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0, 5, false);
  ASSERT_STREQ("10.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0, 5, false);
  ASSERT_STREQ("11.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0, 5, false);
  ASSERT_STREQ("69420.00000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1, 5, false);
  ASSERT_STREQ("0.10000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9, 5, false);
  ASSERT_STREQ("0.90000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5, 5, false);
  ASSERT_STREQ("0.50000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01, 5, false);
  ASSERT_STREQ("0.01000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09, 5, false);
  ASSERT_STREQ("0.09000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05, 5, false);
  ASSERT_STREQ("0.05000", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.001, 5, false);
  ASSERT_STREQ("0.00100", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.009, 5, false);
  ASSERT_STREQ("0.00900", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.005, 5, false);
  ASSERT_STREQ("0.00500", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0001, 5, false);
  ASSERT_STREQ("0.00010", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0009, 5, false);
  ASSERT_STREQ("0.00090", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0005, 5, false);
  ASSERT_STREQ("0.00050", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00001, 5, false);
  ASSERT_STREQ("0.00001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00009, 5, false);
  ASSERT_STREQ("0.00009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00005, 5, false);
  ASSERT_STREQ("0.00005", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Real_Precision5_Truncate) {
  std::stringstream ss;

  ss.str("");
  printLiteralReal(ss, 0.0, 5, true);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 1.0, 5, true);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 9.0, 5, true);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 10.0, 5, true);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 11.0, 5, true);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 69420.0, 5, true);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.1, 5, true);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.9, 5, true);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.5, 5, true);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.01, 5, true);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.09, 5, true);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.05, 5, true);
  ASSERT_STREQ("0.05", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.001, 5, true);
  ASSERT_STREQ("0.001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.009, 5, true);
  ASSERT_STREQ("0.009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.005, 5, true);
  ASSERT_STREQ("0.005", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0001, 5, true);
  ASSERT_STREQ("0.0001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0009, 5, true);
  ASSERT_STREQ("0.0009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.0005, 5, true);
  ASSERT_STREQ("0.0005", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00001, 5, true);
  ASSERT_STREQ("0.00001", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00009, 5, true);
  ASSERT_STREQ("0.00009", ss.str().c_str());

  ss.str("");
  printLiteralReal(ss, 0.00005, 5, true);
  ASSERT_STREQ("0.00005", ss.str().c_str());
}

TEST(Unit_Core_PrintLiterals, Char) {
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
  printLiteralChar(ss, U'\x80');
  ASSERT_STREQ("'\\x80'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, U'\uffff');
  ASSERT_STREQ("'\\uffff'", ss.str().c_str());

  ss.str("");
  printLiteralChar(ss, 0xffffffff);
  ASSERT_STREQ("'\\Uffffffff'", ss.str().c_str());

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

TEST(Unit_Core_PrintLiterals, String) {
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
