#include <gtest/gtest.h>

#include <whiskey/Unicode/OStreamByteOutStream.hpp>

using namespace whiskey;

TEST(Unicode_Unit_OStreamByteOutStream, Simple) {
	std::stringstream ss;
	OStreamByteOutStream bs(ss);

	ASSERT_STREQ(ss.str().c_str(), "");

	bs.writeChar('a');
	ASSERT_STREQ(ss.str().c_str(), "a");

	bs.writeChar('b');
	ASSERT_STREQ(ss.str().c_str(), "ab");
}
