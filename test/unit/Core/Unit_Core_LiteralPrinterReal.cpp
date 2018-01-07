#include <gtest/gtest.h>

#include <whiskey/Core/LiteralPrinterReal.hpp>

using namespace whiskey;

TEST(Unit_Core_LiteralPrinterReal, Real_Precision1_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterReal(0.0, 1, false).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(1.0, 1, false).print(ss);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(9.0, 1, false).print(ss);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(10.0, 1, false).print(ss);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(11.0, 1, false).print(ss);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(69420.0, 1, false).print(ss);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.1, 1, false).print(ss);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.9, 1, false).print(ss);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.5, 1, false).print(ss);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.01, 1, false).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.09, 1, false).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.05, 1, false).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterReal, Real_Precision1_Truncate) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterReal(0.0, 1, true).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(1.0, 1, true).print(ss);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(9.0, 1, true).print(ss);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(10.0, 1, true).print(ss);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(11.0, 1, true).print(ss);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(69420.0, 1, true).print(ss);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.1, 1, true).print(ss);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.9, 1, true).print(ss);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.5, 1, true).print(ss);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.01, 1, true).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.09, 1, true).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.05, 1, true).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterReal, Real_Precision2_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterReal(0.0, 2, false).print(ss);
  ASSERT_STREQ("0.00", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(1.0, 2, false).print(ss);
  ASSERT_STREQ("1.00", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(9.0, 2, false).print(ss);
  ASSERT_STREQ("9.00", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(10.0, 2, false).print(ss);
  ASSERT_STREQ("10.00", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(11.0, 2, false).print(ss);
  ASSERT_STREQ("11.00", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(69420.0, 2, false).print(ss);
  ASSERT_STREQ("69420.00", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.1, 2, false).print(ss);
  ASSERT_STREQ("0.10", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.9, 2, false).print(ss);
  ASSERT_STREQ("0.90", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.5, 2, false).print(ss);
  ASSERT_STREQ("0.50", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.01, 2, false).print(ss);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.09, 2, false).print(ss);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.05, 2, false).print(ss);
  ASSERT_STREQ("0.05", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterReal, Real_Precision2_Truncate) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterReal(0.0, 2, true).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(1.0, 2, true).print(ss);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(9.0, 2, true).print(ss);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(10.0, 2, true).print(ss);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(11.0, 2, true).print(ss);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(69420.0, 2, true).print(ss);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.1, 2, true).print(ss);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.9, 2, true).print(ss);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.5, 2, true).print(ss);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.01, 2, true).print(ss);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.09, 2, true).print(ss);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.05, 2, true).print(ss);
  ASSERT_STREQ("0.05", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterReal, Real_Precision5_NoTruncate) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterReal(0.0, 5, false).print(ss);
  ASSERT_STREQ("0.00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(1.0, 5, false).print(ss);
  ASSERT_STREQ("1.00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(9.0, 5, false).print(ss);
  ASSERT_STREQ("9.00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(10.0, 5, false).print(ss);
  ASSERT_STREQ("10.00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(11.0, 5, false).print(ss);
  ASSERT_STREQ("11.00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(69420.0, 5, false).print(ss);
  ASSERT_STREQ("69420.00000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.1, 5, false).print(ss);
  ASSERT_STREQ("0.10000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.9, 5, false).print(ss);
  ASSERT_STREQ("0.90000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.5, 5, false).print(ss);
  ASSERT_STREQ("0.50000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.01, 5, false).print(ss);
  ASSERT_STREQ("0.01000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.09, 5, false).print(ss);
  ASSERT_STREQ("0.09000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.05, 5, false).print(ss);
  ASSERT_STREQ("0.05000", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.001, 5, false).print(ss);
  ASSERT_STREQ("0.00100", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.009, 5, false).print(ss);
  ASSERT_STREQ("0.00900", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.005, 5, false).print(ss);
  ASSERT_STREQ("0.00500", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.0001, 5, false).print(ss);
  ASSERT_STREQ("0.00010", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.0009, 5, false).print(ss);
  ASSERT_STREQ("0.00090", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.0005, 5, false).print(ss);
  ASSERT_STREQ("0.00050", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.00001, 5, false).print(ss);
  ASSERT_STREQ("0.00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.00009, 5, false).print(ss);
  ASSERT_STREQ("0.00009", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.00005, 5, false).print(ss);
  ASSERT_STREQ("0.00005", ss.str().c_str());
}

TEST(Unit_Core_LiteralPrinterReal, Real_Precision5_Truncate) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterReal(0.0, 5, true).print(ss);
  ASSERT_STREQ("0.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(1.0, 5, true).print(ss);
  ASSERT_STREQ("1.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(9.0, 5, true).print(ss);
  ASSERT_STREQ("9.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(10.0, 5, true).print(ss);
  ASSERT_STREQ("10.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(11.0, 5, true).print(ss);
  ASSERT_STREQ("11.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(69420.0, 5, true).print(ss);
  ASSERT_STREQ("69420.0", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.1, 5, true).print(ss);
  ASSERT_STREQ("0.1", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.9, 5, true).print(ss);
  ASSERT_STREQ("0.9", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.5, 5, true).print(ss);
  ASSERT_STREQ("0.5", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.01, 5, true).print(ss);
  ASSERT_STREQ("0.01", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.09, 5, true).print(ss);
  ASSERT_STREQ("0.09", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.05, 5, true).print(ss);
  ASSERT_STREQ("0.05", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.001, 5, true).print(ss);
  ASSERT_STREQ("0.001", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.009, 5, true).print(ss);
  ASSERT_STREQ("0.009", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.005, 5, true).print(ss);
  ASSERT_STREQ("0.005", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.0001, 5, true).print(ss);
  ASSERT_STREQ("0.0001", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.0009, 5, true).print(ss);
  ASSERT_STREQ("0.0009", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.0005, 5, true).print(ss);
  ASSERT_STREQ("0.0005", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.00001, 5, true).print(ss);
  ASSERT_STREQ("0.00001", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.00009, 5, true).print(ss);
  ASSERT_STREQ("0.00009", ss.str().c_str());

  ss.str("");
  LiteralPrinterReal(0.00005, 5, true).print(ss);
  ASSERT_STREQ("0.00005", ss.str().c_str());
}
