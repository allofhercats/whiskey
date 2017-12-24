#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Test_Core_Color, All) {
	std::stringstream ss;

	Color::enabled = true;
	ss << Color::red;

	ASSERT_GT(ss.str().size(), 0);

	Color::enabled = false;
	ss.str("");
	ASSERT_EQ(ss.str().size(), 0);
	ss << Color::red;
	ASSERT_EQ(ss.str().size(), 0);
}
