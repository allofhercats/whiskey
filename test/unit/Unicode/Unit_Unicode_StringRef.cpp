#include <gtest/gtest.h>

#include <whiskey/Unicode/StringRef.hpp>

using namespace whiskey;

TEST(Unit_Unicode_StringRef, Constructor) {
	StringRef sr;

	ASSERT_EQ(sr.getEncoding(), Encoding::UTF8);
	ASSERT_EQ(sr.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, ConstructorEncoding) {
	ASSERT_DEATH({
		StringRef sr(Encoding::Auto);
	}, "");

	StringRef sr0(Encoding::UTF8);

	ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
	ASSERT_EQ(sr0.getLength(), 0);

	StringRef sr1(Encoding::UTF16LE);

	ASSERT_EQ(sr1.getEncoding(), Encoding::UTF16LE);
	ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, ConstructorUTF8) {
	ASSERT_DEATH({
		StringRef sr((const Char8 *)nullptr);
	}, "");

	StringRef sr0("hello");

	ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
	ASSERT_EQ(sr0.getCharAt(3), 'l');
	ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF8Length) {
	ASSERT_DEATH({
		StringRef sr((const Char8 *)nullptr, 3);
	}, "");

	StringRef sr0("hello", 3);

	ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF16) {
	ASSERT_DEATH({
		StringRef sr((const Char16 *)nullptr);
	}, "");

	StringRef sr0(u"hello");

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE || sr0.getEncoding() == Encoding::UTF16BE);
	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
	ASSERT_EQ(sr0.getCharAt(3), 'l');
	ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF16Length) {
	ASSERT_DEATH({
		StringRef sr((const Char16 *)nullptr, 3);
	}, "");

	StringRef sr0(u"hello", 3);

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE || sr0.getEncoding() == Encoding::UTF16BE);
	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF32) {
	ASSERT_DEATH({
		StringRef sr((const Char32 *)nullptr);
	}, "");

	StringRef sr0(U"hello");

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE || sr0.getEncoding() == Encoding::UTF32BE);
	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
	ASSERT_EQ(sr0.getCharAt(3), 'l');
	ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF32Length) {
	ASSERT_DEATH({
		StringRef sr((const Char32 *)nullptr, 3);
	}, "");

	StringRef sr0(U"hello", 3);

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE || sr0.getEncoding() == Encoding::UTF32BE);
	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF8) {
	std::string s0 = std::string("hello");
	StringRef sr0(s0);

	ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
	ASSERT_EQ(sr0.getCharAt(3), 'l');
	ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF8Length) {
	std::string s0 = std::string("hello");
	StringRef sr0(s0, 3);

	ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF16) {
	std::u16string s0 = std::u16string(u"hello");
	StringRef sr0(s0);

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE || sr0.getEncoding() == Encoding::UTF16BE);
	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
	ASSERT_EQ(sr0.getCharAt(3), 'l');
	ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF16Length) {
	std::u16string s0 = std::u16string(u"hello");
	StringRef sr0(s0, 3);

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE || sr0.getEncoding() == Encoding::UTF16BE);
	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF32) {
	std::u32string s0 = std::u32string(U"hello");
	StringRef sr0(s0);

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE || sr0.getEncoding() == Encoding::UTF32BE);
	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
	ASSERT_EQ(sr0.getCharAt(3), 'l');
	ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF32Length) {
	std::u32string s0 = std::u32string(U"hello");
	StringRef sr0(s0, 3);

	ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE || sr0.getEncoding() == Encoding::UTF32BE);
	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_EQ(sr0.getCharAt(0), 'h');
	ASSERT_EQ(sr0.getCharAt(1), 'e');
	ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, GetEncoding) {
	ASSERT_EQ(StringRef(Encoding::UTF8).getEncoding(), Encoding::UTF8);
	ASSERT_EQ(StringRef(Encoding::UTF16LE).getEncoding(), Encoding::UTF16LE);
	ASSERT_EQ(StringRef(Encoding::UTF16BE).getEncoding(), Encoding::UTF16BE);
	ASSERT_EQ(StringRef(Encoding::UTF32LE).getEncoding(), Encoding::UTF32LE);
	ASSERT_EQ(StringRef(Encoding::UTF32BE).getEncoding(), Encoding::UTF32BE);
}

TEST(Unit_Unicode_StringRef, GetLength) {
	ASSERT_EQ(StringRef().getLength(), 0);
	ASSERT_EQ(StringRef("").getLength(), 0);
	ASSERT_EQ(StringRef("a").getLength(), 1);
	ASSERT_EQ(StringRef("hello, world.").getLength(), 13);
	ASSERT_EQ(StringRef(u"").getLength(), 0);
	ASSERT_EQ(StringRef(u"a").getLength(), 1);
	ASSERT_EQ(StringRef(u"hello, world.").getLength(), 13);
	ASSERT_EQ(StringRef(U"").getLength(), 0);
	ASSERT_EQ(StringRef(U"a").getLength(), 1);
	ASSERT_EQ(StringRef(U"hello, world.").getLength(), 13);
}

TEST(Unit_Unicode_StringRef, SetLengthEmpty) {
	StringRef sr0;

	ASSERT_EQ(sr0.getLength(), 0);

	sr0.setLength(0);

	ASSERT_EQ(sr0.getLength(), 0);

	ASSERT_DEATH({
		sr0.setLength(1);
	}, "");
}

TEST(Unit_Unicode_StringRef, SetLengthUTF8) {
	StringRef sr0("hello");

	ASSERT_EQ(sr0.getLength(), 5);

	sr0.setLength(5);

	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_DEATH({
		sr0.setLength(6);
	}, "");

	sr0.setLength(3);

	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_DEATH({
		sr0.setLength(4);
	}, "");
}

TEST(Unit_Unicode_StringRef, SetLengthUTF16) {
	StringRef sr0(u"hello");

	ASSERT_EQ(sr0.getLength(), 5);

	sr0.setLength(5);

	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_DEATH({
		sr0.setLength(6);
	}, "");

	sr0.setLength(3);

	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_DEATH({
		sr0.setLength(4);
	}, "");
}

TEST(Unit_Unicode_StringRef, SetLengthUTF32) {
	StringRef sr0(U"hello");

	ASSERT_EQ(sr0.getLength(), 5);

	sr0.setLength(5);

	ASSERT_EQ(sr0.getLength(), 5);

	ASSERT_DEATH({
		sr0.setLength(6);
	}, "");

	sr0.setLength(3);

	ASSERT_EQ(sr0.getLength(), 3);

	ASSERT_DEATH({
		sr0.setLength(4);
	}, "");
}

TEST(Unit_Unicode_StringRef, GetChar8Empty) {
	StringRef sr0;

	ASSERT_EQ(sr0.getChar8At(0), 0);
}

TEST(Unit_Unicode_StringRef, GetChar8UTF8) {
	StringRef sr0("hello");

	ASSERT_EQ(sr0.getChar8At(0), 'h');
	ASSERT_EQ(sr0.getChar8At(1), 'e');
	ASSERT_EQ(sr0.getChar8At(2), 'l');
	ASSERT_EQ(sr0.getChar8At(3), 'l');
	ASSERT_EQ(sr0.getChar8At(4), 'o');
	ASSERT_EQ(sr0.getChar8At(5), 0);
}

TEST(Unit_Unicode_StringRef, GetChar8UTF16) {
	StringRef sr0(u"hello");

	ASSERT_DEATH({
		sr0.getChar8At(0);
	}, "");
}

TEST(Unit_Unicode_StringRef, GetChar8UTF32) {
	StringRef sr0(U"hello");

	ASSERT_DEATH({
		sr0.getChar8At(0);
	}, "");
}

TEST(Unit_Unicode_StringRef, GetChar16UTF8) {
	StringRef sr0("hello");

	ASSERT_DEATH({
		sr0.getChar16At(0);
	}, "");	
}

TEST(Unit_Unicode_StringRef, GetChar16UTF16) {
	StringRef sr0(u"hello");

	ASSERT_EQ(sr0.getChar16At(0), 'h');
	ASSERT_EQ(sr0.getChar16At(1), 'e');
	ASSERT_EQ(sr0.getChar16At(2), 'l');
	ASSERT_EQ(sr0.getChar16At(3), 'l');
	ASSERT_EQ(sr0.getChar16At(4), 'o');
	ASSERT_EQ(sr0.getChar16At(5), 0);
}

TEST(Unit_Unicode_StringRef, GetChar16UTF32) {
	StringRef sr0(U"hello");

	ASSERT_DEATH({
		sr0.getChar16At(0);
	}, "");
}

TEST(Unit_Unicode_StringRef, GetChar32UTF8) {
	StringRef sr0("hello");

	ASSERT_DEATH({
		sr0.getChar32At(0);
	}, "");
}

TEST(Unit_Unicode_StringRef, GetChar32UTF16) {
	StringRef sr0(u"hello");

	ASSERT_DEATH({
		sr0.getChar32At(0);
	}, "");
}

TEST(Unit_Unicode_StringRef, GetChar32UTF32) {
	StringRef sr0(U"hello");

	ASSERT_EQ(sr0.getChar32At(0), 'h');
	ASSERT_EQ(sr0.getChar32At(1), 'e');
	ASSERT_EQ(sr0.getChar32At(2), 'l');
	ASSERT_EQ(sr0.getChar32At(3), 'l');
	ASSERT_EQ(sr0.getChar32At(4), 'o');
	ASSERT_EQ(sr0.getChar32At(5), 0);
}
