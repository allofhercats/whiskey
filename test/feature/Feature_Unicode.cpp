#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Feature_Unicode, PrintLiteralChar) {
	std::stringstream ss;

	printLiteralChar(ss, 0x7f);
	ASSERT_STREQ(ss.str().c_str(), "'\\x7f'");

	ss.str("");
	printLiteralChar(ss, 0x80);
	ASSERT_STREQ(ss.str().c_str(), "'\\x80'");

	ss.str("");
	printLiteralChar(ss, 0xff);
	ASSERT_STREQ(ss.str().c_str(), "'\\xff'");

	ss.str("");
	printLiteralChar(ss, 0x100);
	ASSERT_STREQ(ss.str().c_str(), "'\\u0100'");

	ss.str("");
	printLiteralChar(ss, 0xffff);
	ASSERT_STREQ(ss.str().c_str(), "'\\uffff'");

	ss.str("");
	printLiteralChar(ss, 0x10000);
	ASSERT_STREQ(ss.str().c_str(), "'\\U00010000'");

	ss.str("");
	printLiteralChar(ss, 0xffffffff);
	ASSERT_STREQ(ss.str().c_str(), "'\\Uffffffff'");
}

TEST(Feature_Unicode, PrintLiteralString8) {
	std::stringstream ss;

	printLiteralString(ss, "a\xff");
	ASSERT_STREQ(ss.str().c_str(), "\"a\\xff\"");
}

TEST(Feature_Unicode, PrintLiteralString16) {
	std::stringstream ss;

	printLiteralString(ss, u"a\xff\uffff");
	ASSERT_STREQ(ss.str().c_str(), "\"a\\xff\\uffff\"");
}

TEST(Feature_Unicode, PrintLiteralString32) {
	std::stringstream ss;

	printLiteralString(ss, U"a\xff\uffff\U0002070e");
	ASSERT_STREQ(ss.str().c_str(), "\"a\\xff\\uffff\\U0002070e\"");
}

TEST(Feature_Unicode, AppendChar32ToString8) {
	std::string s;

	appendChar32ToString8(s, U'a');
	ASSERT_STREQ(s.c_str(), "a");

	s = "";
	appendChar32ToString8(s, U'\xff');
	ASSERT_STREQ(s.c_str(), "\xff");

	s = "";
	appendChar32ToString8(s, u'\u7702');
	ASSERT_STREQ(s.c_str(), "\xc9\xb7");
}
