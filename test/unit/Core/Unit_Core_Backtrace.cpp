#include <gtest/gtest.h>

#include <whiskey/Core/Backtrace.hpp>

using namespace whiskey;

TEST(Unit_Core_Backtrace, GetCurrentBinaryName) {
  std::string bn0 = getCurrentBinaryName();
  std::string bn1 = getCurrentBinaryName();

  ASSERT_STREQ(bn0.c_str(), bn1.c_str());

  ASSERT_TRUE(bn0.find("whiskey-test-unit") != std::string::npos);
}

TEST(Unit_Core_Backtrace, GetCurrentBinaryName_Max1) {
  std::string bn0 = getCurrentBinaryName(1);
  std::string bn1 = getCurrentBinaryName(1);

  ASSERT_STREQ(bn0.c_str(), bn1.c_str());

  ASSERT_TRUE(bn0 == "/" || bn0 == "\\");
}

extern "C" void thisIsATotallyOriginalSymbol() {
}

TEST(Unit_Core_Backtrace, GetBinaryNameOfSymbol) {
  std::string sn0 =
      getBinaryNameOfSymbol((void *)&thisIsATotallyOriginalSymbol);
  std::string sn1 =
      getBinaryNameOfSymbol((void *)&thisIsATotallyOriginalSymbol);

  ASSERT_STREQ(sn0.c_str(), sn1.c_str());

  ASSERT_TRUE(sn0.find("whiskey-test-unit") != std::string::npos);
}

extern "C" void ifYouWannaBeMyLover() {
  std::stringstream ss;

  printBacktrace(ss);

  std::string s = ss.str();

  ASSERT_TRUE(s.find("ifYouWannaBeMyLover") != std::string::npos);
  ASSERT_TRUE(s.find("youGottaGetWithMyFriends") != std::string::npos);
}

extern "C" void youGottaGetWithMyFriends() {
  ifYouWannaBeMyLover();
}

TEST(Unit_Core_Backtrace, Backtrace) {
  youGottaGetWithMyFriends();
}

extern "C" void ifYouWannaBeMyLover_max1() {
  std::stringstream ss;

  printBacktrace(ss, 1);

  std::string s = ss.str();

  ASSERT_TRUE(s.find("ifYouWannaBeMyLover") != std::string::npos);
  ASSERT_TRUE(s.find("youGottaGetWithMyFriends") == std::string::npos);
}

extern "C" void youGottaGetWithMyFriends_max1() {
  ifYouWannaBeMyLover_max1();
}

TEST(Unit_Core_Backtrace, Backtrace_Max1) {
  youGottaGetWithMyFriends_max1();
}
