#include <gtest/gtest.h>

#include <whiskey/Unicode/StringContainer.hpp>

using namespace whiskey;

TEST(Unit_Unicode_StringContainer, Constructor) {
  StringContainer sc;

  ASSERT_EQ(sc.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sc.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorEncoding) {
  ASSERT_DEATH({ StringContainer sc(Encoding::Auto); }, "");

  StringContainer sc0(Encoding::UTF8);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sc0.getLength(), 0);

  StringContainer sc1(Encoding::UTF16LE);

  ASSERT_EQ(sc1.getEncoding(), Encoding::UTF16LE);
  ASSERT_EQ(sc1.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorUTF8) {
  ASSERT_DEATH({ StringContainer sc((const Char8 *)nullptr); }, "");

  StringContainer sc0("hello");

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, ConstructorUTF8Length) {
  ASSERT_DEATH({ StringContainer sc((const Char8 *)nullptr, 3); }, "");

  StringContainer sc0("hello", 3);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringContainer, ConstructorUTF16) {
  ASSERT_DEATH({ StringContainer sc((const Char16 *)nullptr); }, "");

  StringContainer sc0(u"hello");

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, ConstructorUTF16Length) {
  ASSERT_DEATH({ StringContainer sc((const Char16 *)nullptr, 3); }, "");

  StringContainer sc0(u"hello", 3);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringContainer, ConstructorUTF32) {
  ASSERT_DEATH({ StringContainer sc((const Char32 *)nullptr); }, "");

  StringContainer sc0(U"hello");

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);
  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, ConstructorUTF32Length) {
  ASSERT_DEATH({ StringContainer sc((const Char32 *)nullptr, 3); }, "");

  StringContainer sc0(U"hello", 3);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);
  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringContainer, ConstructorStringUTF8) {
  std::string s0 = std::string("hello");
  StringContainer sc0(s0);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, ConstructorStringUTF8Length) {
  std::string s0 = std::string("hello");
  StringContainer sc0(s0, 3);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);
  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringContainer, ConstructorStringUTF16) {
  std::u16string s0 = std::u16string(u"hello");
  StringContainer sc0(s0);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, ConstructorStringUTF16Length) {
  std::u16string s0 = std::u16string(u"hello");
  StringContainer sc0(s0, 3);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);
  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringContainer, ConstructorStringUTF32) {
  std::u32string s0 = std::u32string(U"hello");
  StringContainer sc0(s0);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);
  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, ConstructorStringUTF32Length) {
  std::u32string s0 = std::u32string(U"hello");
  StringContainer sc0(s0, 3);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);
  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
}

TEST(Unit_Unicode_StringContainer, GetEncoding) {
  ASSERT_EQ(StringContainer(Encoding::UTF8).getEncoding(), Encoding::UTF8);
  ASSERT_EQ(StringContainer(Encoding::UTF16LE).getEncoding(),
            Encoding::UTF16LE);
  ASSERT_EQ(StringContainer(Encoding::UTF16BE).getEncoding(),
            Encoding::UTF16BE);
  ASSERT_EQ(StringContainer(Encoding::UTF32LE).getEncoding(),
            Encoding::UTF32LE);
  ASSERT_EQ(StringContainer(Encoding::UTF32BE).getEncoding(),
            Encoding::UTF32BE);
}

TEST(Unit_Unicode_StringContainer, GetLength) {
  ASSERT_EQ(StringContainer().getLength(), 0);
  ASSERT_EQ(StringContainer("").getLength(), 0);
  ASSERT_EQ(StringContainer("a").getLength(), 1);
  ASSERT_EQ(StringContainer("hello, world.").getLength(), 13);
  ASSERT_EQ(StringContainer(u"").getLength(), 0);
  ASSERT_EQ(StringContainer(u"a").getLength(), 1);
  ASSERT_EQ(StringContainer(u"hello, world.").getLength(), 13);
  ASSERT_EQ(StringContainer(U"").getLength(), 0);
  ASSERT_EQ(StringContainer(U"a").getLength(), 1);
  ASSERT_EQ(StringContainer(U"hello, world.").getLength(), 13);
}

TEST(Unit_Unicode_StringContainer, SetLengthEmpty) {
  StringContainer sc0;

  ASSERT_EQ(sc0.getLength(), 0);

  sc0.setLength(0);

  ASSERT_EQ(sc0.getLength(), 0);

  ASSERT_DEATH({ sc0.setLength(1); }, "");
}

TEST(Unit_Unicode_StringContainer, SetLengthUTF8) {
  StringContainer sc0("hello");

  ASSERT_EQ(sc0.getLength(), 5);

  sc0.setLength(5);

  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_DEATH({ sc0.setLength(6); }, "");

  sc0.setLength(3);

  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_DEATH({ sc0.setLength(4); }, "");
}

TEST(Unit_Unicode_StringContainer, SetLengthUTF16) {
  StringContainer sc0(u"hello");

  ASSERT_EQ(sc0.getLength(), 5);

  sc0.setLength(5);

  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_DEATH({ sc0.setLength(6); }, "");

  sc0.setLength(3);

  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_DEATH({ sc0.setLength(4); }, "");
}

TEST(Unit_Unicode_StringContainer, SetLengthUTF32) {
  StringContainer sc0(U"hello");

  ASSERT_EQ(sc0.getLength(), 5);

  sc0.setLength(5);

  ASSERT_EQ(sc0.getLength(), 5);

  ASSERT_DEATH({ sc0.setLength(6); }, "");

  sc0.setLength(3);

  ASSERT_EQ(sc0.getLength(), 3);

  ASSERT_DEATH({ sc0.setLength(4); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt8Empty) {
  StringContainer sc0;

  ASSERT_EQ(sc0.getChar8At(0), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAt8UTF8) {
  StringContainer sc0("hello");

  ASSERT_EQ(sc0.getChar8At(0), 'h');
  ASSERT_EQ(sc0.getChar8At(1), 'e');
  ASSERT_EQ(sc0.getChar8At(2), 'l');
  ASSERT_EQ(sc0.getChar8At(3), 'l');
  ASSERT_EQ(sc0.getChar8At(4), 'o');
  ASSERT_EQ(sc0.getChar8At(5), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAt8UTF16) {
  StringContainer sc0(u"hello");

  ASSERT_DEATH({ sc0.getChar8At(0); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt8UTF32) {
  StringContainer sc0(U"hello");

  ASSERT_DEATH({ sc0.getChar8At(0); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt16UTF8) {
  StringContainer sc0("hello");

  ASSERT_DEATH({ sc0.getChar16At(0); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt16UTF16) {
  StringContainer sc0(u"hello");

  ASSERT_EQ(sc0.getChar16At(0), 'h');
  ASSERT_EQ(sc0.getChar16At(1), 'e');
  ASSERT_EQ(sc0.getChar16At(2), 'l');
  ASSERT_EQ(sc0.getChar16At(3), 'l');
  ASSERT_EQ(sc0.getChar16At(4), 'o');
  ASSERT_EQ(sc0.getChar16At(5), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAt16UTF32) {
  StringContainer sc0(U"hello");

  ASSERT_DEATH({ sc0.getChar16At(0); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt32UTF8) {
  StringContainer sc0("hello");

  ASSERT_DEATH({ sc0.getChar32At(0); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt32UTF16) {
  StringContainer sc0(u"hello");

  ASSERT_DEATH({ sc0.getChar32At(0); }, "");
}

TEST(Unit_Unicode_StringContainer, GetCharAt32UTF32) {
  StringContainer sc0(U"hello");

  ASSERT_EQ(sc0.getChar32At(0), 'h');
  ASSERT_EQ(sc0.getChar32At(1), 'e');
  ASSERT_EQ(sc0.getChar32At(2), 'l');
  ASSERT_EQ(sc0.getChar32At(3), 'l');
  ASSERT_EQ(sc0.getChar32At(4), 'o');
  ASSERT_EQ(sc0.getChar32At(5), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAtEmpty) {
  StringContainer sc0;

  ASSERT_EQ(sc0.getCharAt(0), 0);
  ASSERT_EQ(sc0.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAtUTF8) {
  StringContainer sc0("hello");

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAtUTF8Multibyte) {
  StringContainer sc0("\xc2\xa3");

  ASSERT_EQ(sc0.getCharAt(0), u'\u00a3');
  ASSERT_EQ(sc0.getCharAt(2), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAtUTF16) {
  StringContainer sc0(u"hello");

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, GetCharAtUTF32) {
  StringContainer sc0(U"hello");

  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, EatCharAtEmpty) {
  StringContainer sc0;
  size_t pos = 0;

  ASSERT_EQ(sc0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 0);

  pos = 1;
  ASSERT_EQ(sc0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 1);
}

TEST(Unit_Unicode_StringContainer, EatCharAtUTF8) {
  StringContainer sc0("hello");
  size_t pos = 0;

  ASSERT_EQ(sc0.eatCharAt(pos), 'h');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sc0.eatCharAt(pos), 'e');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sc0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 3);

  ASSERT_EQ(sc0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 4);

  ASSERT_EQ(sc0.eatCharAt(pos), 'o');
  ASSERT_EQ(pos, 5);

  ASSERT_EQ(sc0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, EatCharAtUTF8Multibyte) {
  StringContainer sc0("\xc2\xa3");
  size_t pos = 0;

  ASSERT_EQ(sc0.eatCharAt(pos), u'\u00a3');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sc0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 2);
}

TEST(Unit_Unicode_StringContainer, EatCharAtUTF16) {
  StringContainer sc0(u"hello");
  size_t pos = 0;

  ASSERT_EQ(sc0.eatCharAt(pos), 'h');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sc0.eatCharAt(pos), 'e');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sc0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 3);

  ASSERT_EQ(sc0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 4);

  ASSERT_EQ(sc0.eatCharAt(pos), 'o');
  ASSERT_EQ(pos, 5);

  ASSERT_EQ(sc0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, EatCharAtUTF32) {
  StringContainer sc0(U"hello");
  size_t pos = 0;

  ASSERT_EQ(sc0.eatCharAt(pos), 'h');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sc0.eatCharAt(pos), 'e');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sc0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 3);

  ASSERT_EQ(sc0.eatCharAt(pos), 'l');
  ASSERT_EQ(pos, 4);

  ASSERT_EQ(sc0.eatCharAt(pos), 'o');
  ASSERT_EQ(pos, 5);

  ASSERT_EQ(sc0.eatCharAt(pos), 0);
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, SubStringEmpty) {
  StringContainer sc0;
  StringContainer sc1 = sc0.subString(1, 1);

  ASSERT_EQ(sc1.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringZeroLength) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(0, 0);

  ASSERT_EQ(sc1.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringLastPastEnd) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(0, 6);

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringFirstPastEnd) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(5, 1);

  ASSERT_EQ(sc1.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringOneLength) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(0, 1);

  ASSERT_EQ(sc1.getLength(), 1);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringOneLengthAtEnd) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(4, 1);

  ASSERT_EQ(sc1.getLength(), 1);
  ASSERT_EQ(sc1.getCharAt(0), 'o');
  ASSERT_EQ(sc1.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringExact) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(0, 5);

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringNoLengthEmpty) {
  StringContainer sc0;
  StringContainer sc1 = sc0.subString(0);

  ASSERT_EQ(sc1.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringNoLengthAtStart) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(0);

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringNoLengthAtEnd) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(4);

  ASSERT_EQ(sc1.getLength(), 1);
  ASSERT_EQ(sc1.getCharAt(0), 'o');
  ASSERT_EQ(sc1.getCharAt(1), 0);
}

TEST(Unit_Unicode_StringContainer, SubStringNoLengthPastEnd) {
  StringContainer sc0("hello");
  StringContainer sc1 = sc0.subString(5);

  ASSERT_EQ(sc1.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, CompareEmpty) {
  StringContainer sc0;
  StringContainer sc1;

  ASSERT_TRUE(sc0.compare(sc1));
}

TEST(Unit_Unicode_StringContainer, Compare) {
  StringContainer sc0("hello");
  StringContainer sc1("hello");

  ASSERT_TRUE(sc0.compare(sc1));

  sc1 = "goodbye";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = "apple";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = "helloo";

  ASSERT_FALSE(sc0.compare(sc1));
}

TEST(Unit_Unicode_StringContainer, CompareUTF16WithUTF8) {
  StringContainer sc0(u"hello");
  StringContainer sc1("hello");

  ASSERT_TRUE(sc0.compare(sc1));

  sc1 = "goodbye";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = "apple";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = "helloo";

  ASSERT_FALSE(sc0.compare(sc1));
}

TEST(Unit_Unicode_StringContainer, CompareUTF32WithUTF8) {
  StringContainer sc0(U"hello");
  StringContainer sc1("hello");

  ASSERT_TRUE(sc0.compare(sc1));

  sc1 = "goodbye";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = "apple";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = "helloo";

  ASSERT_FALSE(sc0.compare(sc1));
}

TEST(Unit_Unicode_StringContainer, CompareUTF32WithUTF16) {
  StringContainer sc0(U"hello");
  StringContainer sc1(u"hello");

  ASSERT_TRUE(sc0.compare(sc1));

  sc1 = u"goodbye";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = u"apple";

  ASSERT_FALSE(sc0.compare(sc1));

  sc1 = u"helloo";

  ASSERT_FALSE(sc0.compare(sc1));
}

TEST(Unit_Unicode_StringContainer, CompareWithLength) {
  StringContainer sc0("hello");
  StringContainer sc1("helloo");

  ASSERT_TRUE(sc0.compare(sc1, 5));
  ASSERT_FALSE(sc0.compare(sc1, 6));
  ASSERT_FALSE(sc0.compare(sc1, 7));
}

TEST(Unit_Unicode_StringContainer, ConstructorStringRefEmpty) {
  StringRef sr0;
  StringContainer sc0(sr0);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorStringRefUTF8) {
  StringRef sr0("hello");
  StringContainer sc0(sr0);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorStringRefUTF16) {
  StringRef sr0(u"hello");
  StringContainer sc0(sr0);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorStringRefUTF32) {
  StringRef sr0(U"hello");
  StringContainer sc0(sr0);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorCopyEmpty) {
  StringContainer sc1;
  StringContainer sc0(sc1);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorCopyUTF8) {
  StringContainer sc1("hello");
  StringContainer sc0(sc1);

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorCopyUTF16) {
  StringContainer sc1(u"hello");
  StringContainer sc0(sc1);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, ConstructorCopyUTF32) {
  StringContainer sc1(U"hello");
  StringContainer sc0(sc1);

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, CopyAssignEmpty) {
  StringContainer sc1;
  StringContainer sc0;
  sc0 = sc1;

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, CopyAssignUTF8) {
  StringContainer sc1("hello");
  StringContainer sc0;
  sc0 = sc1;

  ASSERT_EQ(sc0.getEncoding(), Encoding::UTF8);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, CopyAssignUTF16) {
  StringContainer sc1(u"hello");
  StringContainer sc0;
  sc0 = sc1;

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF16LE ||
              sc0.getEncoding() == Encoding::UTF16BE);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, CopyAssignUTF32) {
  StringContainer sc1(U"hello");
  StringContainer sc0;
  sc0 = sc1;

  ASSERT_TRUE(sc0.getEncoding() == Encoding::UTF32LE ||
              sc0.getEncoding() == Encoding::UTF32BE);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, MemoryBehavior) {
  Char8 buf[] = "hello";

  StringContainer sc0(buf);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);

  buf[0] = 'A';

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, MemoryBehaviorCopy) {
  StringContainer sc0("hello");

  StringContainer sc1(sc0);

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);

  sc0.setCharAt(0, 'A');

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, MemoryBehaviorCopyAssign) {
  StringContainer sc0("hello");

  StringContainer sc1;
  sc1 = sc0;

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);

  sc0.setCharAt(0, 'A');

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 0);

  ASSERT_EQ(sc1.getLength(), 5);
  ASSERT_EQ(sc1.getCharAt(0), 'h');
  ASSERT_EQ(sc1.getCharAt(1), 'e');
  ASSERT_EQ(sc1.getCharAt(2), 'l');
  ASSERT_EQ(sc1.getCharAt(3), 'l');
  ASSERT_EQ(sc1.getCharAt(4), 'o');
  ASSERT_EQ(sc1.getCharAt(5), 0);
}

TEST(Unit_Unicode_StringContainer, ToStringRefEmpty) {
  StringContainer sc0;
  StringRef sr0 = sc0;

  ASSERT_EQ(sr0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, ConvertToEncodingUTF8) {
  StringContainer sr0("hello");

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

TEST(Unit_Unicode_StringContainer, ConvertToEncodingUTF16) {
  StringContainer sr0(u"hello");

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

TEST(Unit_Unicode_StringContainer, ConvertToEncodingUTF32) {
  StringContainer sr0(U"hello");

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

TEST(Unit_Unicode_StringContainer, GetCapacityEmpty) {
  StringContainer sc0;

  ASSERT_EQ(sc0.getCapacity(), 0);
}

TEST(Unit_Unicode_StringContainer, GetCapacity) {
  StringContainer sc0("hello");

  ASSERT_GE(sc0.getCapacity(), 5);
}

TEST(Unit_Unicode_StringContainer, SetCapacityEmpty) {
  StringContainer sc0;

  sc0.setCapacity(1000);

  ASSERT_GE(sc0.getCapacity(), 1000);

  ASSERT_DEATH({ sc0.setCapacity(0); }, "");

  sc0.setCapacity(1);

  ASSERT_GE(sc0.getCapacity(), 1);
}

TEST(Unit_Unicode_StringContainer, SetCapacity) {
  StringContainer sc0("hello");

  sc0.setCapacity(1000);

  ASSERT_GE(sc0.getCapacity(), 1000);

  ASSERT_DEATH({ sc0.setCapacity(0); }, "");

  ASSERT_DEATH({ sc0.setCapacity(4); }, "");

  sc0.setCapacity(5);

  ASSERT_GE(sc0.getCapacity(), 5);
}

TEST(Unit_Unicode_StringContainer, SetChar8At) {
  StringContainer sc0("hello");

  sc0.setChar8At(0, 'A');

  ASSERT_EQ(sc0.getChar8At(0), 'A');

  sc0.setChar8At(4, 'A');

  ASSERT_EQ(sc0.getChar8At(4), 'A');

  ASSERT_DEATH({ sc0.setChar8At(5, 'A'); }, "");

  ASSERT_DEATH({ sc0.setChar16At(0, 'A'); }, "");

  ASSERT_DEATH({ sc0.setChar32At(0, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, SetChar16At) {
  StringContainer sc0(u"hello");

  ASSERT_DEATH({ sc0.setChar8At(0, 'A'); }, "");

  sc0.setChar16At(0, 'A');

  ASSERT_EQ(sc0.getChar16At(0), 'A');

  sc0.setChar16At(4, 'A');

  ASSERT_EQ(sc0.getChar16At(4), 'A');

  ASSERT_DEATH({ sc0.setChar16At(5, 'A'); }, "");

  ASSERT_DEATH({ sc0.setChar32At(0, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, SetChar32At) {
  StringContainer sc0(U"hello");

  ASSERT_DEATH({ sc0.setChar8At(0, 'A'); }, "");

  ASSERT_DEATH({ sc0.setChar16At(0, 'A'); }, "");

  sc0.setChar32At(0, 'A');

  ASSERT_EQ(sc0.getChar32At(0), 'A');

  sc0.setChar32At(4, 'A');

  ASSERT_EQ(sc0.getChar32At(4), 'A');

  ASSERT_DEATH({ sc0.setChar32At(5, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, SetCharAtUTF8) {
  StringContainer sc0("hello");

  sc0.setCharAt(0, 'A');

  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');

  sc0.setCharAt(4, 'A');
  ASSERT_EQ(sc0.getChar8At(4), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.setCharAt(5, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, SetCharAtUTF8Multibyte) {
  StringContainer sc0("hello");

  sc0.setCharAt(0, u'\u00a3');

  ASSERT_EQ(sc0.getCharAt(0), u'\u00a3');
  ASSERT_EQ(sc0.getCharAt(2), 'l');

  sc0.setCharAt(3, u'\u00a3');
  ASSERT_EQ(sc0.getCharAt(3), u'\u00a3');

  ASSERT_DEATH({ sc0.setCharAt(4, u'\u00a3'); }, "");

  ASSERT_DEATH({ sc0.setCharAt(5, u'\u00a3'); }, "");
}

TEST(Unit_Unicode_StringContainer, SetCharAtUTF16) {
  StringContainer sc0(u"hello");

  sc0.setCharAt(0, 'A');

  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');

  sc0.setCharAt(4, 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.setCharAt(5, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, SetCharAtUTF32) {
  StringContainer sc0(U"hello");

  sc0.setCharAt(0, 'A');

  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');

  sc0.setCharAt(4, 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.setCharAt(5, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, WriteCharAtUTF8) {
  StringContainer sc0("hello");
  size_t pos = 0;

  sc0.writeCharAt(pos, 'A');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');

  pos = 4;
  sc0.writeCharAt(pos, 'A');
  ASSERT_EQ(pos, 5);
  ASSERT_EQ(sc0.getChar8At(4), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  pos = 5;
  ASSERT_DEATH({ sc0.writeCharAt(pos, 'A'); }, "");
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, WriteCharAtUTF8Multibyte) {
  StringContainer sc0("hello");
  size_t pos = 0;

  sc0.writeCharAt(pos, u'\u00a3');
  ASSERT_EQ(pos, 2);

  ASSERT_EQ(sc0.getCharAt(0), u'\u00a3');
  ASSERT_EQ(sc0.getCharAt(2), 'l');

  pos = 3;
  sc0.writeCharAt(pos, u'\u00a3');
  ASSERT_EQ(pos, 5);
  ASSERT_EQ(sc0.getCharAt(3), u'\u00a3');

  pos = 4;
  ASSERT_DEATH({ sc0.writeCharAt(pos, u'\u00a3'); }, "");
  ASSERT_EQ(pos, 4);

  pos = 5;
  ASSERT_DEATH({ sc0.writeCharAt(pos, u'\u00a3'); }, "");
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, WriteCharAtUTF16) {
  StringContainer sc0(u"hello");
  size_t pos = 0;

  sc0.writeCharAt(pos, 'A');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');

  pos = 4;
  sc0.writeCharAt(pos, 'A');
  ASSERT_EQ(pos, 5);
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  pos = 5;
  ASSERT_DEATH({ sc0.writeCharAt(pos, 'A'); }, "");
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, WriteCharAtUTF32) {
  StringContainer sc0(U"hello");
  size_t pos = 0;

  sc0.writeCharAt(pos, 'A');
  ASSERT_EQ(pos, 1);

  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'e');

  pos = 4;
  sc0.writeCharAt(pos, 'A');
  ASSERT_EQ(pos, 5);
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  pos = 5;
  ASSERT_DEATH({ sc0.writeCharAt(pos, 'A'); }, "");
  ASSERT_EQ(pos, 5);
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF8Empty) {
  StringContainer sc0;
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF8MultibyteEmpty) {
  StringContainer sc0;
  sc0.append(u'\u00a3');

  ASSERT_EQ(sc0.getLength(), 2);
  ASSERT_EQ(sc0.getCharAt(0), u'\x00a3');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF8) {
  StringContainer sc0("hello");
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF8Multibyte) {
  StringContainer sc0("hello");
  sc0.append(u'\u00a3');

  ASSERT_EQ(sc0.getLength(), 7);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), u'\x00a3');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF8Empty) {
  StringContainer sc0;
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF8MultibyteEmpty) {
  StringContainer sc0;
  sc0.append(u'\u00a3', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(2), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(4), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(6), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(8), u'\x00a3');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF8) {
  StringContainer sc0("hello");
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF8Multibyte) {
  StringContainer sc0("hello");
  sc0.append(u'\u00a3', 5);

  ASSERT_EQ(sc0.getLength(), 15);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(7), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(9), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(11), u'\x00a3');
  ASSERT_EQ(sc0.getCharAt(13), u'\x00a3');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF16LEEmpty) {
  StringContainer sc0(Encoding::UTF16LE);
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF16BEEmpty) {
  StringContainer sc0(Encoding::UTF16BE);
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF16) {
  StringContainer sc0(u"hello");
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF16LEEmpty) {
  StringContainer sc0(Encoding::UTF16LE);
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF16BEEmpty) {
  StringContainer sc0(Encoding::UTF16BE);
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF16) {
  StringContainer sc0(u"hello");
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF32LEEmpty) {
  StringContainer sc0(Encoding::UTF32LE);
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF32BEEmpty) {
  StringContainer sc0(Encoding::UTF32BE);
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharOneUTF32) {
  StringContainer sc0(U"hello");
  sc0.append('A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF32LEEmpty) {
  StringContainer sc0(Encoding::UTF32LE);
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF32BEEmpty) {
  StringContainer sc0(Encoding::UTF32BE);
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendCharManyUTF32) {
  StringContainer sc0(U"hello");
  sc0.append('A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'A');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF8EmptyToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1;
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF8ToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1("hello");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF8EmptyToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1;
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF8ToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1("bye");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 8);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'b');
  ASSERT_EQ(sc0.getCharAt(6), 'y');
  ASSERT_EQ(sc0.getCharAt(7), 'e');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16LEToUTF8EmptyEmpty) {
  StringContainer sc0;
  StringContainer sc1(Encoding::UTF16LE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16BEEmptyToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1(Encoding::UTF16BE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16ToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1(u"hello");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16MultibyteToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1(u"hell\u00a3");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), u'\x00a3');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16LEEmptyToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1(Encoding::UTF16LE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16BEEmptyToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1(Encoding::UTF16BE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF16ToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1(u"bye");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 8);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'b');
  ASSERT_EQ(sc0.getCharAt(6), 'y');
  ASSERT_EQ(sc0.getCharAt(7), 'e');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF32LEToUTF8EmptyEmpty) {
  StringContainer sc0;
  StringContainer sc1(Encoding::UTF32LE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF32BEEmptyToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1(Encoding::UTF32BE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF32ToUTF8Empty) {
  StringContainer sc0;
  StringContainer sc1(U"hello");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF32LEEmptyToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1(Encoding::UTF32LE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF32BEEmptyToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1(Encoding::UTF32BE);
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
}

TEST(Unit_Unicode_StringContainer, AppendStringUTF32ToUTF8) {
  StringContainer sc0("hello");
  StringContainer sc1(U"bye");
  sc0.append(sc1);

  ASSERT_EQ(sc0.getLength(), 8);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'b');
  ASSERT_EQ(sc0.getCharAt(6), 'y');
  ASSERT_EQ(sc0.getCharAt(7), 'e');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8Empty) {
  StringContainer sc0;

  ASSERT_DEATH({ sc0.remove(0, 1); }, "");

  ASSERT_DEATH({ sc0.remove(0, 0); }, "");
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8OneAtBeginning) {
  StringContainer sc0("hello");

  sc0.remove(0);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'e');
  ASSERT_EQ(sc0.getCharAt(1), 'l');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8SomeAtBeginning) {
  StringContainer sc0("hello");

  sc0.remove(0, 4);

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8AllAtBeginning) {
  StringContainer sc0("hello");

  sc0.remove(0, 5);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8OneInMiddle) {
  StringContainer sc0("hello");

  sc0.remove(2);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8SomeInMiddle) {
  StringContainer sc0("hello");

  sc0.remove(2, 2);

  ASSERT_EQ(sc0.getLength(), 3);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8AllInMiddle) {
  StringContainer sc0("hello");

  sc0.remove(2, 3);

  ASSERT_EQ(sc0.getLength(), 2);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF8OneAtEnd) {
  StringContainer sc0("hello");

  sc0.remove(4);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
}

TEST(Unit_Unicode_StringContainer, RemoveEmptyUTF16LE) {
  StringContainer sc0(Encoding::UTF16LE);

  ASSERT_DEATH({ sc0.remove(0, 1); }, "");

  ASSERT_DEATH({ sc0.remove(0, 0); }, "");
}

TEST(Unit_Unicode_StringContainer, RemoveEmptyUTF16BE) {
  StringContainer sc0(Encoding::UTF16BE);

  ASSERT_DEATH({ sc0.remove(0, 1); }, "");

  ASSERT_DEATH({ sc0.remove(0, 0); }, "");
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16OneAtBeginning) {
  StringContainer sc0(u"hello");

  sc0.remove(0);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'e');
  ASSERT_EQ(sc0.getCharAt(1), 'l');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16SomeAtBeginning) {
  StringContainer sc0(u"hello");

  sc0.remove(0, 4);

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16AllAtBeginning) {
  StringContainer sc0(u"hello");

  sc0.remove(0, 5);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16OneInMiddle) {
  StringContainer sc0(u"hello");

  sc0.remove(2);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16SomeInMiddle) {
  StringContainer sc0(u"hello");

  sc0.remove(2, 2);

  ASSERT_EQ(sc0.getLength(), 3);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16AllInMiddle) {
  StringContainer sc0(u"hello");

  sc0.remove(2, 3);

  ASSERT_EQ(sc0.getLength(), 2);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF16OneAtEnd) {
  StringContainer sc0(u"hello");

  sc0.remove(4);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
}

TEST(Unit_Unicode_StringContainer, RemoveEmptyUTF32LE) {
  StringContainer sc0(Encoding::UTF32LE);

  ASSERT_DEATH({ sc0.remove(0, 1); }, "");

  ASSERT_DEATH({ sc0.remove(0, 0); }, "");
}

TEST(Unit_Unicode_StringContainer, RemoveEmptyUTF32BE) {
  StringContainer sc0(Encoding::UTF32BE);

  ASSERT_DEATH({ sc0.remove(0, 1); }, "");

  ASSERT_DEATH({ sc0.remove(0, 0); }, "");
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32OneAtBeginning) {
  StringContainer sc0(U"hello");

  sc0.remove(0);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'e');
  ASSERT_EQ(sc0.getCharAt(1), 'l');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32SomeAtBeginning) {
  StringContainer sc0(U"hello");

  sc0.remove(0, 4);

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32AllAtBeginning) {
  StringContainer sc0(U"hello");

  sc0.remove(0, 5);

  ASSERT_EQ(sc0.getLength(), 0);
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32OneInMiddle) {
  StringContainer sc0(U"hello");

  sc0.remove(2);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32SomeInMiddle) {
  StringContainer sc0(U"hello");

  sc0.remove(2, 2);

  ASSERT_EQ(sc0.getLength(), 3);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'o');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32AllInMiddle) {
  StringContainer sc0(U"hello");

  sc0.remove(2, 3);

  ASSERT_EQ(sc0.getLength(), 2);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
}

TEST(Unit_Unicode_StringContainer, RemoveUTF32OneAtEnd) {
  StringContainer sc0(U"hello");

  sc0.remove(4);

  ASSERT_EQ(sc0.getLength(), 4);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
}

TEST(Unit_Unicode_StringContainer, InsertUTF8OneAtBeginningEmpty) {
  StringContainer sc0;

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');

  ASSERT_DEATH({ sc0.insert(2, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8ManyAtBeginningEmpty) {
  StringContainer sc0;

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.insert(6, 'A', 5); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8OneAtBeginning) {
  StringContainer sc0("hello");

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'h');
  ASSERT_EQ(sc0.getCharAt(2), 'e');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'l');
  ASSERT_EQ(sc0.getCharAt(5), 'o');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8ManyAtBeginning) {
  StringContainer sc0("hello");

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'h');
  ASSERT_EQ(sc0.getCharAt(6), 'e');
  ASSERT_EQ(sc0.getCharAt(7), 'l');
  ASSERT_EQ(sc0.getCharAt(8), 'l');
  ASSERT_EQ(sc0.getCharAt(9), 'o');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8OneInMiddle) {
  StringContainer sc0("hello");

  sc0.insert(4, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'o');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8ManyInMiddle) {
  StringContainer sc0("hello");

  sc0.insert(4, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'o');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8OneAtEnd) {
  StringContainer sc0("hello");

  sc0.insert(5, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF8ManyAtEnd) {
  StringContainer sc0("hello");

  sc0.insert(5, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'A');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16LEOneAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF16LE);

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');

  ASSERT_DEATH({ sc0.insert(2, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16BEOneAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF16BE);

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');

  ASSERT_DEATH({ sc0.insert(2, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16LEManyAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF16LE);

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.insert(6, 'A', 5); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16BEManyAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF16BE);

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.insert(6, 'A', 5); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16OneAtBeginning) {
  StringContainer sc0(u"hello");

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'h');
  ASSERT_EQ(sc0.getCharAt(2), 'e');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'l');
  ASSERT_EQ(sc0.getCharAt(5), 'o');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16ManyAtBeginning) {
  StringContainer sc0(u"hello");

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'h');
  ASSERT_EQ(sc0.getCharAt(6), 'e');
  ASSERT_EQ(sc0.getCharAt(7), 'l');
  ASSERT_EQ(sc0.getCharAt(8), 'l');
  ASSERT_EQ(sc0.getCharAt(9), 'o');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16OneInMiddle) {
  StringContainer sc0(u"hello");

  sc0.insert(4, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'o');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16ManyInMiddle) {
  StringContainer sc0(u"hello");

  sc0.insert(4, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'o');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16OneAtEnd) {
  StringContainer sc0(u"hello");

  sc0.insert(5, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF16ManyAtEnd) {
  StringContainer sc0(u"hello");

  sc0.insert(5, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'A');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32LEOneAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF32LE);

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');

  ASSERT_DEATH({ sc0.insert(2, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32BEOneAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF32BE);

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 1);
  ASSERT_EQ(sc0.getCharAt(0), 'A');

  ASSERT_DEATH({ sc0.insert(2, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32LEManyAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF32LE);

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.insert(6, 'A', 5); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32BEManyAtBeginningEmpty) {
  StringContainer sc0(Encoding::UTF32BE);

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 5);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');

  ASSERT_DEATH({ sc0.insert(6, 'A', 5); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32OneAtBeginning) {
  StringContainer sc0(U"hello");

  sc0.insert(0, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'h');
  ASSERT_EQ(sc0.getCharAt(2), 'e');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'l');
  ASSERT_EQ(sc0.getCharAt(5), 'o');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32ManyAtBeginning) {
  StringContainer sc0(U"hello");

  sc0.insert(0, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'A');
  ASSERT_EQ(sc0.getCharAt(1), 'A');
  ASSERT_EQ(sc0.getCharAt(2), 'A');
  ASSERT_EQ(sc0.getCharAt(3), 'A');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'h');
  ASSERT_EQ(sc0.getCharAt(6), 'e');
  ASSERT_EQ(sc0.getCharAt(7), 'l');
  ASSERT_EQ(sc0.getCharAt(8), 'l');
  ASSERT_EQ(sc0.getCharAt(9), 'o');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32OneInMiddle) {
  StringContainer sc0(U"hello");

  sc0.insert(4, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'o');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32ManyInMiddle) {
  StringContainer sc0(U"hello");

  sc0.insert(4, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'A');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'o');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32OneAtEnd) {
  StringContainer sc0(U"hello");

  sc0.insert(5, 'A');

  ASSERT_EQ(sc0.getLength(), 6);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');

  ASSERT_DEATH({ sc0.insert(7, 'A'); }, "");
}

TEST(Unit_Unicode_StringContainer, InsertUTF32ManyAtEnd) {
  StringContainer sc0(U"hello");

  sc0.insert(5, 'A', 5);

  ASSERT_EQ(sc0.getLength(), 10);
  ASSERT_EQ(sc0.getCharAt(0), 'h');
  ASSERT_EQ(sc0.getCharAt(1), 'e');
  ASSERT_EQ(sc0.getCharAt(2), 'l');
  ASSERT_EQ(sc0.getCharAt(3), 'l');
  ASSERT_EQ(sc0.getCharAt(4), 'o');
  ASSERT_EQ(sc0.getCharAt(5), 'A');
  ASSERT_EQ(sc0.getCharAt(6), 'A');
  ASSERT_EQ(sc0.getCharAt(7), 'A');
  ASSERT_EQ(sc0.getCharAt(8), 'A');
  ASSERT_EQ(sc0.getCharAt(9), 'A');

  ASSERT_DEATH({ sc0.insert(11, 'A'); }, "");
}
