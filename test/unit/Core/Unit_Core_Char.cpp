#include <gtest/gtest.h>

#include <whiskey/Core/Char.hpp>

using namespace whiskey;

TEST(Unit_Core_Char, Char32MinWidth) {
  ASSERT_EQ(getChar32MinWidth(U'\0'), 1);
  ASSERT_EQ(getChar32MinWidth(U'\xff'), 1);
  ASSERT_EQ(getChar32MinWidth(U'\u0100'), 2);
  ASSERT_EQ(getChar32MinWidth(U'\uffff'), 2);
  ASSERT_EQ(getChar32MinWidth(U'\U00010000'), 4);
  ASSERT_EQ(getChar32MinWidth((char32_t)0xffffffffff), 4);
}

TEST(Unit_Core_Char, IsValidUTF32Char) {
	ASSERT_TRUE(isValidUTF32Char(0x1f618));
}

TEST(Unit_Core_Char, ReadCharUTF8_NullSrc) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		readCharUTF8(nullptr, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF8_NegativePos) {
	ASSERT_DEATH({
		CharOffset pos = -1;
		readCharUTF8("hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF8_TooLargePos_0) {
	ASSERT_DEATH({
		CharOffset pos = 5;
		readCharUTF8("hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF8_TooLargePos_1) {
	ASSERT_DEATH({
		CharOffset pos = 6;
		readCharUTF8("hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF8_NegativeLength) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		readCharUTF8("hello", pos, -1);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF8_Width1) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF8("a", pos, 1), 'a');
	ASSERT_EQ(pos, 1);
}

TEST(Unit_Core_Char, ReadCharUTF8_Width2) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF8("\xc9\x90", pos, 2), u'\u0250');
	ASSERT_EQ(pos, 2);
}

TEST(Unit_Core_Char, ReadCharUTF8_Width3) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF8("\xe3\x81\x82", pos, 3), u'\u3042');
	ASSERT_EQ(pos, 3);
}

TEST(Unit_Core_Char, ReadCharUTF8_Width4) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF8("\xf0\x9f\x98\x98", pos, 4), U'\U0001f618');
	ASSERT_EQ(pos, 4);
}

TEST(Unit_Core_Char, ReadCharUTF16_NullSrc) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		readCharUTF16(nullptr, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF16_NegativePos) {
	ASSERT_DEATH({
		CharOffset pos = -1;
		readCharUTF16(u"hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF16_TooLargePos_0) {
	ASSERT_DEATH({
		CharOffset pos = 5;
		readCharUTF16(u"hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF16_TooLargePos_1) {
	ASSERT_DEATH({
		CharOffset pos = 6;
		readCharUTF16(u"hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF16_NegativeLength) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		readCharUTF16(u"hello", pos, -1);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF16_Width1) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF16(u"a", pos, 1), 'a');
	ASSERT_EQ(pos, 1);
}

TEST(Unit_Core_Char, ReadCharUTF16_Width2) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF16(u"\u3042", pos, 1), u'\u3042');
	ASSERT_EQ(pos, 1);
}

TEST(Unit_Core_Char, ReadCharUTF16_Width4) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF16(u"\U0001f44d", pos, 2), U'\U0001f44d');
	ASSERT_EQ(pos, 2);
}

TEST(Unit_Core_Char, ReadCharUTF32_NullSrc) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		readCharUTF32(nullptr, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF32_NegativePos) {
	ASSERT_DEATH({
		CharOffset pos = -1;
		readCharUTF32(U"hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF32_TooLargePos_0) {
	ASSERT_DEATH({
		CharOffset pos = 5;
		readCharUTF32(U"hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF32_TooLargePos_1) {
	ASSERT_DEATH({
		CharOffset pos = 6;
		readCharUTF32(U"hello", pos, 5);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF32_NegativeLength) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		readCharUTF32(U"hello", pos, -1);
	}, "");
}

TEST(Unit_Core_Char, ReadCharUTF32) {
	CharOffset pos = 0;
	ASSERT_EQ(readCharUTF32(U"a", pos, 1), 'a');
	ASSERT_EQ(pos, 1);
}

TEST(Unit_Core_Char, WriteCharUTF8_NullDst) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		writeCharUTF8(nullptr, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF8_NegativePos) {
	ASSERT_DEATH({
		CharOffset pos = -1;
		char buf[5];
		writeCharUTF8(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF8_TooLargePos_0) {
	ASSERT_DEATH({
		CharOffset pos = 5;
		char buf[5];
		writeCharUTF8(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF8_TooLargePos_1) {
	ASSERT_DEATH({
		CharOffset pos = 6;
		char buf[5];
		writeCharUTF8(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF8_NegativeLength) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		char buf[5];
		writeCharUTF8(buf, 0, pos, -1);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF8_Width1) {
	CharOffset pos = 0;
	char buf[1];
	writeCharUTF8(buf, 'a', pos, 1);
	ASSERT_EQ(pos, 1);
	ASSERT_EQ(buf[0], 'a');
}

TEST(Unit_Core_Char, WriteCharUTF8_Width2) {
	CharOffset pos = 0;
	char buf[2];
	writeCharUTF8(buf, u'\u0250', pos, 2);
	ASSERT_EQ(pos, 2);
	ASSERT_EQ(buf[0], '\xc9');
	ASSERT_EQ(buf[1], '\x90');
}

TEST(Unit_Core_Char, WriteCharUTF8_Width3) {
	CharOffset pos = 0;
	char buf[3];
	writeCharUTF8(buf, u'\u3042', pos, 3);
	ASSERT_EQ(pos, 3);
	ASSERT_EQ(buf[0], '\xe3');
	ASSERT_EQ(buf[1], '\x81');
	ASSERT_EQ(buf[2], '\x82');
}

TEST(Unit_Core_Char, WriteCharUTF8_Width4) {
	CharOffset pos = 0;
	char buf[4];
	writeCharUTF8(buf, U'\U0001f618', pos, 4);
	ASSERT_EQ(pos, 4);
	ASSERT_EQ(buf[0], '\xf0');
	ASSERT_EQ(buf[1], '\x9f');
	ASSERT_EQ(buf[2], '\x98');
	ASSERT_EQ(buf[3], '\x98');
}

TEST(Unit_Core_Char, WriteCharUTF16_NullDst) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		writeCharUTF16(nullptr, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF16_NegativePos) {
	ASSERT_DEATH({
		CharOffset pos = -1;
		char16_t buf[5];
		writeCharUTF16(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF16_TooLargePos_0) {
	ASSERT_DEATH({
		CharOffset pos = 5;
		char16_t buf[5];
		writeCharUTF16(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF16_TooLargePos_1) {
	ASSERT_DEATH({
		CharOffset pos = 6;
		char16_t buf[5];
		writeCharUTF16(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF16_NegativeLength) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		char16_t buf[5];
		writeCharUTF16(buf, 0, pos, -1);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF16_Width1) {
	CharOffset pos = 0;
	char16_t buf[1];
	writeCharUTF16(buf, 'a', pos, 1);
	ASSERT_EQ(pos, 1);
	ASSERT_EQ(buf[0], 'a');
}

TEST(Unit_Core_Char, WriteCharUTF16_Width2) {
	CharOffset pos = 0;
	char16_t buf[1];
	writeCharUTF16(buf, u'\u3042', pos, 1);
	ASSERT_EQ(pos, 1);
	ASSERT_EQ(buf[0], u'\u3042');
}

TEST(Unit_Core_Char, WriteCharUTF16_Width4) {
	CharOffset pos = 0;
	char16_t buf[2];
	writeCharUTF16(buf, U'\U0001f44d', pos, 2);
	ASSERT_EQ(pos, 2);
	ASSERT_EQ(buf[0], 0xd83d);
	ASSERT_EQ(buf[1], 0xdc4d);
}

TEST(Unit_Core_Char, WriteCharUTF32_NullDst) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		writeCharUTF32(nullptr, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF32_NegativePos) {
	ASSERT_DEATH({
		CharOffset pos = -1;
		char32_t buf[5];
		writeCharUTF32(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF32_TooLargePos_0) {
	ASSERT_DEATH({
		CharOffset pos = 5;
		char32_t buf[5];
		writeCharUTF32(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF32_TooLargePos_1) {
	ASSERT_DEATH({
		CharOffset pos = 6;
		char32_t buf[5];
		writeCharUTF32(buf, 0, pos, 5);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF32_NegativeLength) {
	ASSERT_DEATH({
		CharOffset pos = 0;
		char32_t buf[5];
		writeCharUTF32(buf, 0, pos, -1);
	}, "");
}

TEST(Unit_Core_Char, WriteCharUTF32) {
	CharOffset pos = 0;
	char32_t buf[1];
	writeCharUTF32(buf, 'a', pos, 1);
	ASSERT_EQ(pos, 1);
	ASSERT_EQ(buf[0], 'a');
}
