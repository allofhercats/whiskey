#include <gtest/gtest.h>

#include <whiskey/Core/LiteralPrinterBool.hpp>

using namespace whiskey;

TEST(Unit_Core_LiteralPrinterBool, Bool) {
  std::stringstream ss;

  ss.str("");
  LiteralPrinterBool(true).print(ss);
  ASSERT_STREQ("true", ss.str().c_str());

  ss.str("");
  LiteralPrinterBool(false).print(ss);
  ASSERT_STREQ("false", ss.str().c_str());
}
