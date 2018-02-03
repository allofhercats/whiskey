#include <gtest/gtest.h>

#include <whiskey/Unicode/StringContainer.hpp>
#include <whiskey/Unicode/StringRef.hpp>

using namespace whiskey;

TEST(Unit_Unicode_StringRef, Constructor) {
  StringRef sr;

  ASSERT_EQ(sr.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sr.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, ConstructorEncoding) {
  ASSERT_DEATH({ StringRef sr(Encoding::Auto); }, "");

  StringRef sr0(Encoding::UTF8);

  ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sr0.getLength(), 0);

  StringRef sr1(Encoding::UTF16LE);

  ASSERT_EQ(sr1.getEncoding(), Encoding::UTF16LE);
  ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, ConstructorUTF8) {
  ASSERT_DEATH({ StringRef sr((const Char8 *)nullptr); }, "");

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
  ASSERT_DEATH({ StringRef sr((const Char8 *)nullptr, 3); }, "");

  StringRef sr0("hello", 3);

  ASSERT_EQ(sr0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sr0.getLength(), 3);

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF16) {
  ASSERT_DEATH({ StringRef sr((const Char16 *)nullptr); }, "");

  StringRef sr0(u"hello");

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE ||
              sr0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sr0.getLength(), 5);

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF16Length) {
  ASSERT_DEATH({ StringRef sr((const Char16 *)nullptr, 3); }, "");

  StringRef sr0(u"hello", 3);

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE ||
              sr0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sr0.getLength(), 3);

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF32) {
  ASSERT_DEATH({ StringRef sr((const Char32 *)nullptr); }, "");

  StringRef sr0(U"hello");

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE ||
              sr0.getEncoding() == Encoding::UTF32BE);
  ASSERT_EQ(sr0.getLength(), 5);

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringRef, ConstructorUTF32Length) {
  ASSERT_DEATH({ StringRef sr((const Char32 *)nullptr, 3); }, "");

  StringRef sr0(U"hello", 3);

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE ||
              sr0.getEncoding() == Encoding::UTF32BE);
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

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE ||
              sr0.getEncoding() == Encoding::UTF16BE);
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

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF16LE ||
              sr0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sr0.getLength(), 3);

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringRef, ConstructorStringUTF32) {
  std::u32string s0 = std::u32string(U"hello");
  StringRef sr0(s0);

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE ||
              sr0.getEncoding() == Encoding::UTF32BE);
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

  ASSERT_TRUE(sr0.getEncoding() == Encoding::UTF32LE ||
              sr0.getEncoding() == Encoding::UTF32BE);
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

  ASSERT_DEATH({ sr0.setLength(1); }, "");
}

TEST(Unit_Unicode_StringRef, SetLengthUTF8) {
  StringRef sr0("hello");

  ASSERT_EQ(sr0.getLength(), 5);

  sr0.setLength(5);

  ASSERT_EQ(sr0.getLength(), 5);

  ASSERT_DEATH({ sr0.setLength(6); }, "");

  sr0.setLength(3);

  ASSERT_EQ(sr0.getLength(), 3);

  ASSERT_DEATH({ sr0.setLength(4); }, "");
}

TEST(Unit_Unicode_StringRef, SetLengthUTF16) {
  StringRef sr0(u"hello");

  ASSERT_EQ(sr0.getLength(), 5);

  sr0.setLength(5);

  ASSERT_EQ(sr0.getLength(), 5);

  ASSERT_DEATH({ sr0.setLength(6); }, "");

  sr0.setLength(3);

  ASSERT_EQ(sr0.getLength(), 3);

  ASSERT_DEATH({ sr0.setLength(4); }, "");
}

TEST(Unit_Unicode_StringRef, SetLengthUTF32) {
  StringRef sr0(U"hello");

  ASSERT_EQ(sr0.getLength(), 5);

  sr0.setLength(5);

  ASSERT_EQ(sr0.getLength(), 5);

  ASSERT_DEATH({ sr0.setLength(6); }, "");

  sr0.setLength(3);

  ASSERT_EQ(sr0.getLength(), 3);

  ASSERT_DEATH({ sr0.setLength(4); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt8Empty) {
  StringRef sr0;

  ASSERT_EQ(sr0.getChar8At(0), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAt8UTF8) {
  StringRef sr0("hello");

  ASSERT_EQ(sr0.getChar8At(0), 'h');
  ASSERT_EQ(sr0.getChar8At(1), 'e');
  ASSERT_EQ(sr0.getChar8At(2), 'l');
  ASSERT_EQ(sr0.getChar8At(3), 'l');
  ASSERT_EQ(sr0.getChar8At(4), 'o');
  ASSERT_EQ(sr0.getChar8At(5), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAt8UTF16) {
  StringRef sr0(u"hello");

  ASSERT_DEATH({ sr0.getChar8At(0); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt8UTF32) {
  StringRef sr0(U"hello");

  ASSERT_DEATH({ sr0.getChar8At(0); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt16UTF8) {
  StringRef sr0("hello");

  ASSERT_DEATH({ sr0.getChar16At(0); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt16UTF16) {
  StringRef sr0(u"hello");

  ASSERT_EQ(sr0.getChar16At(0), 'h');
  ASSERT_EQ(sr0.getChar16At(1), 'e');
  ASSERT_EQ(sr0.getChar16At(2), 'l');
  ASSERT_EQ(sr0.getChar16At(3), 'l');
  ASSERT_EQ(sr0.getChar16At(4), 'o');
  ASSERT_EQ(sr0.getChar16At(5), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAt16UTF32) {
  StringRef sr0(U"hello");

  ASSERT_DEATH({ sr0.getChar16At(0); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt32UTF8) {
  StringRef sr0("hello");

  ASSERT_DEATH({ sr0.getChar32At(0); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt32UTF16) {
  StringRef sr0(u"hello");

  ASSERT_DEATH({ sr0.getChar32At(0); }, "");
}

TEST(Unit_Unicode_StringRef, GetCharAt32UTF32) {
  StringRef sr0(U"hello");

  ASSERT_EQ(sr0.getChar32At(0), 'h');
  ASSERT_EQ(sr0.getChar32At(1), 'e');
  ASSERT_EQ(sr0.getChar32At(2), 'l');
  ASSERT_EQ(sr0.getChar32At(3), 'l');
  ASSERT_EQ(sr0.getChar32At(4), 'o');
  ASSERT_EQ(sr0.getChar32At(5), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAtEmpty) {
  StringRef sr0;

  ASSERT_EQ(sr0.getCharAt(0), 0);
  ASSERT_EQ(sr0.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAtUTF8) {
  StringRef sr0("hello");

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
  ASSERT_EQ(sr0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAtUTF8Multibyte) {
  StringRef sr0("\xc2\xa3");

  ASSERT_EQ(sr0.getCharAt(0), u'\u00a3');
  ASSERT_EQ(sr0.getCharAt(2), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAtUTF16) {
  StringRef sr0(u"hello");

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
  ASSERT_EQ(sr0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, GetCharAtUTF32) {
  StringRef sr0(U"hello");

  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
  ASSERT_EQ(sr0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, EatCharAtEmpty) {
  StringRef sr0;
  size_t pos = 0;

  ASSERT_EQ(sr0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 0);

  pos = 1;
  ASSERT_EQ(sr0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 1);
}

TEST(Unit_Unicode_StringRef, EatCharAtUTF8) {
  StringRef sr0("hello");
  size_t pos = 0;

  ASSERT_EQ(sr0.eatCharAt(pos), 'h');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sr0.eatCharAt(pos), 'e');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sr0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 3);

  ASSERT_EQ(sr0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 4);

  ASSERT_EQ(sr0.eatCharAt(pos), 'o');
  ASSERT_EQ(pos, 5);

  ASSERT_EQ(sr0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringRef, EatCharAtUTF8Multibyte) {
  StringRef sr0("\xc2\xa3");
  size_t pos = 0;

  ASSERT_EQ(sr0.eatCharAt(pos), u'\u00a3');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sr0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 2);
}

TEST(Unit_Unicode_StringRef, EatCharAtUTF16) {
  StringRef sr0(u"hello");
  size_t pos = 0;

  ASSERT_EQ(sr0.eatCharAt(pos), 'h');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sr0.eatCharAt(pos), 'e');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sr0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 3);

  ASSERT_EQ(sr0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 4);

  ASSERT_EQ(sr0.eatCharAt(pos), 'o');
  ASSERT_EQ(pos, 5);

  ASSERT_EQ(sr0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringRef, EatCharAtUTF32) {
  StringRef sr0(U"hello");
  size_t pos = 0;

  ASSERT_EQ(sr0.eatCharAt(pos), 'h');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sr0.eatCharAt(pos), 'e');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sr0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 3);

  ASSERT_EQ(sr0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 4);

  ASSERT_EQ(sr0.eatCharAt(pos), 'o');
  ASSERT_EQ(pos, 5);

  ASSERT_EQ(sr0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringRef, SubStringEmpty) {
  StringRef sr0;
  StringRef sr1 = sr0.subString(1, 1);

  ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, SubStringZeroLength) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(0, 0);

  ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, SubStringLastPastEnd) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(0, 6);

  ASSERT_EQ(sr1.getLength(), 5);
  ASSERT_EQ(sr1.getCharAt(0), 'h');
  ASSERT_EQ(sr1.getCharAt(1), 'e');
  ASSERT_EQ(sr1.getCharAt(2), 'l');
  ASSERT_EQ(sr1.getCharAt(3), 'l');
  ASSERT_EQ(sr1.getCharAt(4), 'o');
  ASSERT_EQ(sr1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, SubStringFirstPastEnd) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(5, 1);

  ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, SubStringOneLength) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(0, 1);

  ASSERT_EQ(sr1.getLength(), 1);
  ASSERT_EQ(sr1.getCharAt(0), 'h');
  ASSERT_EQ(sr1.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringRef, SubStringOneLengthAtEnd) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(4, 1);

  ASSERT_EQ(sr1.getLength(), 1);
  ASSERT_EQ(sr1.getCharAt(0), 'o');
  ASSERT_EQ(sr1.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringRef, SubStringExact) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(0, 5);

  ASSERT_EQ(sr1.getLength(), 5);
  ASSERT_EQ(sr1.getCharAt(0), 'h');
  ASSERT_EQ(sr1.getCharAt(1), 'e');
  ASSERT_EQ(sr1.getCharAt(2), 'l');
  ASSERT_EQ(sr1.getCharAt(3), 'l');
  ASSERT_EQ(sr1.getCharAt(4), 'o');
  ASSERT_EQ(sr1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, SubStringNoLengthEmpty) {
  StringRef sr0;
  StringRef sr1 = sr0.subString(0);

  ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, SubStringNoLengthAtStart) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(0);

  ASSERT_EQ(sr1.getLength(), 5);
  ASSERT_EQ(sr1.getCharAt(0), 'h');
  ASSERT_EQ(sr1.getCharAt(1), 'e');
  ASSERT_EQ(sr1.getCharAt(2), 'l');
  ASSERT_EQ(sr1.getCharAt(3), 'l');
  ASSERT_EQ(sr1.getCharAt(4), 'o');
  ASSERT_EQ(sr1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, SubStringNoLengthAtEnd) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(4);

  ASSERT_EQ(sr1.getLength(), 1);
  ASSERT_EQ(sr1.getCharAt(0), 'o');
  ASSERT_EQ(sr1.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringRef, SubStringNoLengthPastEnd) {
  StringRef sr0("hello");
  StringRef sr1 = sr0.subString(5);

  ASSERT_EQ(sr1.getLength(), 0);
}

TEST(Unit_Unicode_StringRef, CompareEmpty) {
  StringRef sr0;
  StringRef sr1;

  ASSERT_TRUE(sr0.compare(sr1));
}

TEST(Unit_Unicode_StringRef, Compare) {
  StringRef sr0("hello");
  StringRef sr1("hello");

  ASSERT_TRUE(sr0.compare(sr1));

  sr1 = "goodbye";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = "apple";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = "helloo";

  ASSERT_FALSE(sr0.compare(sr1));
}

TEST(Unit_Unicode_StringRef, CompareUTF16WithUTF8) {
  StringRef sr0(u"hello");
  StringRef sr1("hello");

  ASSERT_TRUE(sr0.compare(sr1));

  sr1 = "goodbye";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = "apple";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = "helloo";

  ASSERT_FALSE(sr0.compare(sr1));
}

TEST(Unit_Unicode_StringRef, CompareUTF32WithUTF8) {
  StringRef sr0(U"hello");
  StringRef sr1("hello");

  ASSERT_TRUE(sr0.compare(sr1));

  sr1 = "goodbye";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = "apple";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = "helloo";

  ASSERT_FALSE(sr0.compare(sr1));
}

TEST(Unit_Unicode_StringRef, CompareUTF32WithUTF16) {
  StringRef sr0(U"hello");
  StringRef sr1(u"hello");

  ASSERT_TRUE(sr0.compare(sr1));

  sr1 = u"goodbye";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = u"apple";

  ASSERT_FALSE(sr0.compare(sr1));

  sr1 = u"helloo";

  ASSERT_FALSE(sr0.compare(sr1));
}

TEST(Unit_Unicode_StringRef, CompareWithLength) {
  StringRef sr0("hello");
  StringRef sr1("helloo");

  ASSERT_TRUE(sr0.compare(sr1, 5));
  ASSERT_FALSE(sr0.compare(sr1, 6));
  ASSERT_FALSE(sr0.compare(sr1, 7));
}

TEST(Unit_Unicode_StringRef, MemoryBehavior) {
  Char8 buf[] = "hello";

  StringRef sr0(buf);

  ASSERT_EQ(sr0.getLength(), 5);
  ASSERT_EQ(sr0.getCharAt(0), 'h');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
  ASSERT_EQ(sr0.getCharAt(5), 0);

  buf[0] = 'A';

  ASSERT_EQ(sr0.getLength(), 5);
  ASSERT_EQ(sr0.getCharAt(0), 'A');
  ASSERT_EQ(sr0.getCharAt(1), 'e');
  ASSERT_EQ(sr0.getCharAt(2), 'l');
  ASSERT_EQ(sr0.getCharAt(3), 'l');
  ASSERT_EQ(sr0.getCharAt(4), 'o');
  ASSERT_EQ(sr0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringRef, ConvertToEncodingUTF8) {
  StringRef sr0("hello");

  StringContainer sc0 = sr0.convertToEncoding(Encoding::UTF8);
  StringContainer sc1 = sr0.convertToEncoding(Encoding::UTF16LE);
  StringContainer sc2 = sr0.convertToEncoding(Encoding::UTF16BE);
  StringContainer sc3 = sr0.convertToEncoding(Encoding::UTF32LE);
  StringContainer sc4 = sr0.convertToEncoding(Encoding::UTF32BE);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_TRUE(sr0.compare(sc0));

  ASSERT_EQ(sc1.getEncoding(), Encoding::UTF16LE);
  ASSERT_TRUE(sr0.compare(sc1));

  ASSERT_EQ(sc2.getEncoding(), Encoding::UTF16BE);
  ASSERT_TRUE(sr0.compare(sc2));

  ASSERT_EQ(sc3.getEncoding(), Encoding::UTF32LE);
  ASSERT_TRUE(sr0.compare(sc3));

  ASSERT_EQ(sc4.getEncoding(), Encoding::UTF32BE);
  ASSERT_TRUE(sr0.compare(sc4));
}

TEST(Unit_Unicode_StringRef, ConvertToEncodingUTF16) {
  StringRef sr0(u"hello");

  StringContainer sc0 = sr0.convertToEncoding(Encoding::UTF8);
  StringContainer sc1 = sr0.convertToEncoding(Encoding::UTF16LE);
  StringContainer sc2 = sr0.convertToEncoding(Encoding::UTF16BE);
  StringContainer sc3 = sr0.convertToEncoding(Encoding::UTF32LE);
  StringContainer sc4 = sr0.convertToEncoding(Encoding::UTF32BE);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_TRUE(sr0.compare(sc0));

  ASSERT_EQ(sc1.getEncoding(), Encoding::UTF16LE);
  ASSERT_TRUE(sr0.compare(sc1));

  ASSERT_EQ(sc2.getEncoding(), Encoding::UTF16BE);
  ASSERT_TRUE(sr0.compare(sc2));

  ASSERT_EQ(sc3.getEncoding(), Encoding::UTF32LE);
  ASSERT_TRUE(sr0.compare(sc3));

  ASSERT_EQ(sc4.getEncoding(), Encoding::UTF32BE);
  ASSERT_TRUE(sr0.compare(sc4));
}

TEST(Unit_Unicode_StringRef, ConvertToEncodingUTF32) {
  StringRef sr0(U"hello");

  StringContainer sc0 = sr0.convertToEncoding(Encoding::UTF8);
  StringContainer sc1 = sr0.convertToEncoding(Encoding::UTF16LE);
  StringContainer sc2 = sr0.convertToEncoding(Encoding::UTF16BE);
  StringContainer sc3 = sr0.convertToEncoding(Encoding::UTF32LE);
  StringContainer sc4 = sr0.convertToEncoding(Encoding::UTF32BE);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_TRUE(sr0.compare(sc0));

  ASSERT_EQ(sc1.getEncoding(), Encoding::UTF16LE);
  ASSERT_TRUE(sr0.compare(sc1));

  ASSERT_EQ(sc2.getEncoding(), Encoding::UTF16BE);
  ASSERT_TRUE(sr0.compare(sc2));

  ASSERT_EQ(sc3.getEncoding(), Encoding::UTF32LE);
  ASSERT_TRUE(sr0.compare(sc3));

  ASSERT_EQ(sc4.getEncoding(), Encoding::UTF32BE);
  ASSERT_TRUE(sr0.compare(sc4));
}
