#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Core/StringRef.hpp>

using namespace whiskey;

TEST(Unit_Core_StringRef, Empty) {
  StringRef r;

  ASSERT_FALSE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_EQ(r.getData8(), nullptr);

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_CString8) {
  StringRef r("", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_CString16) {
  StringRef r(u"", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_CString32) {
  StringRef r(U"", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_CWString) {
  StringRef r(L"", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_String8) {
  std::string tmp("");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_String16) {
  std::u16string tmp(u"");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_String32) {
  std::u32string tmp(U"");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, Empty_WString) {
  std::wstring tmp(L"");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 0);
  ASSERT_EQ(r.getChar(0), 0);
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(5); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CString8_Length0) {
  StringRef r("hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CString8_Length5) {
  StringRef r("hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CString16_Length0) {
  StringRef r(u"hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CString16_Length5) {
  StringRef r(u"hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CString32_Length0) {
  StringRef r(U"hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CString32_Length5) {
  StringRef r(U"hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CWString_Length0) {
  StringRef r(L"hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_CWString_Length5) {
  StringRef r(L"hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_String8) {
  std::string tmp("hello, world.\n");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_String16) {
  std::u16string tmp(u"hello, world.\n");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_String32) {
  std::u32string tmp(U"hello, world.\n");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}

TEST(Unit_Core_StringRef, HelloWorld_WString) {
  std::wstring tmp(L"hello, world.\n");
  StringRef r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 14);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(13), '\n');
  ASSERT_EQ(r.getChar(14), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  String::const_iterator i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, ',');
  ASSERT_EQ(*i++, ' ');
  ASSERT_EQ(*i++, 'w');
  ASSERT_EQ(*i++, 'o');
  ASSERT_EQ(*i++, 'r');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'd');
  ASSERT_EQ(*i++, '.');
  ASSERT_EQ(*i++, '\n');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.setLength(20); }, "");

  r.setLength(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.getLength(), 5);
  ASSERT_EQ(r.getChar(0), 'h');
  ASSERT_EQ(r.getChar(-1), 0);
  ASSERT_EQ(r.getChar(1), 'e');
  ASSERT_EQ(r.getChar(4), 'o');
  ASSERT_EQ(r.getChar(5), 0);

  b = r.begin();
  e = r.end();

  i = b;

  ASSERT_TRUE(i == b);

  ASSERT_EQ(*i, 'h');
  ASSERT_EQ(*i++, 'e');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'l');
  ASSERT_EQ(*i++, 'o');
  i++;

  ASSERT_TRUE(i == e);
  ASSERT_FALSE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  r.setLength(5);

  ASSERT_DEATH({ r.setLength(6); }, "");
}
