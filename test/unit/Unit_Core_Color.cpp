#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Core/Assert.hpp>

using namespace whiskey;

TEST(Unit_Core_Color, Enabled) {
  std::stringstream ss;

  Color tmp("hi");

  ASSERT_STREQ(ss.str().c_str(), "");

  Color::enabled = true;
  ss << tmp;

  ASSERT_STREQ(ss.str().c_str(), "hi");
}

TEST(Unit_Core_Color, Disabled) {
  std::stringstream ss;

  Color tmp("hi");

  ASSERT_STREQ(ss.str().c_str(), "");

  Color::enabled = false;
  ss << tmp;

  ASSERT_STREQ(ss.str().c_str(), "");
}
