#include <gtest/gtest.h>

#include <whiskey/Core/LiteralPrinterChar.hpp>

using namespace whiskey;

TEST(Unit_Core_LiteralPrinterChar, Simple) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterChar('\0').print(ss);
  ASSERT_STREQ("'\\0'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar('a').print(ss);
  ASSERT_STREQ("'a'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar('\a').print(ss);
  ASSERT_STREQ("'\\a'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar('\033').print(ss);
  ASSERT_STREQ("'\\e'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar(U'\x80').print(ss);
  ASSERT_STREQ("'\\x80'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar(U'\uffff').print(ss);
  ASSERT_STREQ("'\\uffff'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar(0xffffffff).print(ss);
  ASSERT_STREQ("'\\Uffffffff'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar('\'').print(ss);
  ASSERT_STREQ("'\\''", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar('\"').print(ss);
  ASSERT_STREQ("'\"'", ss.str().c_str());

  ss.str("");
  LiteralPrinterChar('\\').print(ss);
  ASSERT_STREQ("'\\\\'", ss.str().c_str());
}