#include <gtest/gtest.h>

#include <whiskey/Core/LiteralPrinterUInt.hpp>

using namespace whiskey;

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base2_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 2, false, 0).print(ss);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 2, false, 0).print(ss);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(2, 2, false, 0).print(ss);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(3, 2, false, 0).print(ss);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 2, false, 0).print(ss);
  ASSERT_STREQ("111", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 2, false, 0).print(ss);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 2, false, 0).print(ss);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base2_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 2, false, 5).print(ss);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 2, false, 5).print(ss);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(2, 2, false, 5).print(ss);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(3, 2, false, 5).print(ss);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 2, false, 5).print(ss);
  ASSERT_STREQ("00111", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 2, false, 5).print(ss);
  ASSERT_STREQ("10000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 2, false, 5).print(ss);
  ASSERT_STREQ(
      "1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base2_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 2, true, 0).print(ss);
  ASSERT_STREQ("0b0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 2, true, 0).print(ss);
  ASSERT_STREQ("0b1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(2, 2, true, 0).print(ss);
  ASSERT_STREQ("0b10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(3, 2, true, 0).print(ss);
  ASSERT_STREQ("0b11", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 2, true, 0).print(ss);
  ASSERT_STREQ("0b111", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 2, true, 0).print(ss);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 2, true, 0).print(ss);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base2_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 2, true, 5).print(ss);
  ASSERT_STREQ("0b00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 2, true, 5).print(ss);
  ASSERT_STREQ("0b00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(2, 2, true, 5).print(ss);
  ASSERT_STREQ("0b00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(3, 2, true, 5).print(ss);
  ASSERT_STREQ("0b00011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 2, true, 5).print(ss);
  ASSERT_STREQ("0b00111", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 2, true, 5).print(ss);
  ASSERT_STREQ("0b10000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 2, true, 5).print(ss);
  ASSERT_STREQ(
      "0b1111111111111111111111111111111111111111111111111111111111111111",
      ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base8_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 8, false, 0).print(ss);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 8, false, 0).print(ss);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 8, false, 0).print(ss);
  ASSERT_STREQ("7", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(8, 8, false, 0).print(ss);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 8, false, 0).print(ss);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 8, false, 0).print(ss);
  ASSERT_STREQ("20", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 8, false, 0).print(ss);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base8_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 8, false, 5).print(ss);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 8, false, 5).print(ss);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 8, false, 5).print(ss);
  ASSERT_STREQ("00007", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(8, 8, false, 5).print(ss);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 8, false, 5).print(ss);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 8, false, 5).print(ss);
  ASSERT_STREQ("00020", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 8, false, 5).print(ss);
  ASSERT_STREQ("1777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base8_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 8, true, 0).print(ss);
  ASSERT_STREQ("00", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 8, true, 0).print(ss);
  ASSERT_STREQ("01", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 8, true, 0).print(ss);
  ASSERT_STREQ("07", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(8, 8, true, 0).print(ss);
  ASSERT_STREQ("010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 8, true, 0).print(ss);
  ASSERT_STREQ("011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 8, true, 0).print(ss);
  ASSERT_STREQ("020", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 8, true, 0).print(ss);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base8_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 8, true, 5).print(ss);
  ASSERT_STREQ("000000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 8, true, 5).print(ss);
  ASSERT_STREQ("000001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(7, 8, true, 5).print(ss);
  ASSERT_STREQ("000007", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(8, 8, true, 5).print(ss);
  ASSERT_STREQ("000010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 8, true, 5).print(ss);
  ASSERT_STREQ("000011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 8, true, 5).print(ss);
  ASSERT_STREQ("000020", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 8, true, 5).print(ss);
  ASSERT_STREQ("01777777777777777777777", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base10_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 10, false, 0).print(ss);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 10, false, 0).print(ss);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 10, false, 0).print(ss);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(10, 10, false, 0).print(ss);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(11, 10, false, 0).print(ss);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(69420, 10, false, 0).print(ss);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 10, false, 0).print(ss);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base10_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 10, false, 5).print(ss);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 10, false, 5).print(ss);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 10, false, 5).print(ss);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(10, 10, false, 5).print(ss);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(11, 10, false, 5).print(ss);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(69420, 10, false, 5).print(ss);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 10, false, 5).print(ss);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base10_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 10, true, 0).print(ss);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 10, true, 0).print(ss);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 10, true, 0).print(ss);
  ASSERT_STREQ("9", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(10, 10, true, 0).print(ss);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(11, 10, true, 0).print(ss);
  ASSERT_STREQ("11", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(69420, 10, true, 0).print(ss);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 10, true, 0).print(ss);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base10_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 10, true, 5).print(ss);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 10, true, 5).print(ss);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(9, 10, true, 5).print(ss);
  ASSERT_STREQ("00009", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(10, 10, true, 5).print(ss);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(11, 10, true, 5).print(ss);
  ASSERT_STREQ("00011", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(69420, 10, true, 5).print(ss);
  ASSERT_STREQ("69420", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 10, true, 5).print(ss);
  ASSERT_STREQ("18446744073709551615", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base16_NoPrefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 16, false, 0).print(ss);
  ASSERT_STREQ("0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 16, false, 0).print(ss);
  ASSERT_STREQ("1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(15, 16, false, 0).print(ss);
  ASSERT_STREQ("f", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 16, false, 0).print(ss);
  ASSERT_STREQ("10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(254, 16, false, 0).print(ss);
  ASSERT_STREQ("fe", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(255, 16, false, 0).print(ss);
  ASSERT_STREQ("ff", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 16, false, 0).print(ss);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base16_NoPrefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 16, false, 5).print(ss);
  ASSERT_STREQ("00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 16, false, 5).print(ss);
  ASSERT_STREQ("00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(15, 16, false, 5).print(ss);
  ASSERT_STREQ("0000f", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 16, false, 5).print(ss);
  ASSERT_STREQ("00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(254, 16, false, 5).print(ss);
  ASSERT_STREQ("000fe", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(255, 16, false, 5).print(ss);
  ASSERT_STREQ("000ff", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 16, false, 5).print(ss);
  ASSERT_STREQ("ffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base16_Prefix_Width0) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 16, true, 0).print(ss);
  ASSERT_STREQ("0x0", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 16, true, 0).print(ss);
  ASSERT_STREQ("0x1", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(15, 16, true, 0).print(ss);
  ASSERT_STREQ("0xf", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 16, true, 0).print(ss);
  ASSERT_STREQ("0x10", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(254, 16, true, 0).print(ss);
  ASSERT_STREQ("0xfe", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(255, 16, true, 0).print(ss);
  ASSERT_STREQ("0xff", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 16, true, 0).print(ss);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterUInt, UInt_Base16_Prefix_Width5) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterUInt(0, 16, true, 5).print(ss);
  ASSERT_STREQ("0x00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(1, 16, true, 5).print(ss);
  ASSERT_STREQ("0x00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(15, 16, true, 5).print(ss);
  ASSERT_STREQ("0x0000f", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(16, 16, true, 5).print(ss);
  ASSERT_STREQ("0x00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(254, 16, true, 5).print(ss);
  ASSERT_STREQ("0x000fe", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(255, 16, true, 5).print(ss);
  ASSERT_STREQ("0x000ff", ss.str().c_str());

  ss.str("");
  LiteralPrinterUInt(-1, 16, true, 5).print(ss);
  ASSERT_STREQ("0xffffffffffffffff", ss.str().c_str());
}
