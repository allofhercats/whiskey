#include <gtest/gtest.h>

#include <whiskey/Core/LiteralPrinterString.hpp>

using namespace whiskey;

TEST(Unit_Core_LiteralPrinterString, Simple) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterString("").print(ss);
  ASSERT_STREQ("\"\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\0").print(ss);
  ASSERT_STREQ("\"\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("a").print(ss);
  ASSERT_STREQ("\"a\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\a").print(ss);
  ASSERT_STREQ("\"\\a\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\033").print(ss);
  ASSERT_STREQ("\"\\e\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\x80").print(ss);
  ASSERT_STREQ("\"\\x80\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\'").print(ss);
  ASSERT_STREQ("\"'\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\"").print(ss);
  ASSERT_STREQ("\"\\\"\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("\\").print(ss);
  ASSERT_STREQ("\"\\\\\"", ss.str().c_str());

  ss.str("");
  LiteralPrinterString("Hello, world.\n").print(ss);
  ASSERT_STREQ("\"Hello, world.\\n\"", ss.str().c_str());
}
