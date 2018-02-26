#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/Core/Color.hpp>

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
