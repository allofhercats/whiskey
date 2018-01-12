#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Core/StringContainer.hpp>

using namespace whiskey;

TEST(Unit_Core_StringContainer_AsRef, Empty) {
  StringContainer r;

  ASSERT_FALSE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_EQ(r.getData8(), nullptr);

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_CString8) {
  StringContainer r("", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_CString16) {
  StringContainer r(u"", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_CString32) {
  StringContainer r(U"", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_CWString) {
  StringContainer r(L"", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_String8) {
  std::string tmp("");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_String16) {
  std::u16string tmp(u"");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_String32) {
  std::u32string tmp(U"");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, Empty_WString) {
  std::wstring tmp(L"");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 0);
  ASSERT_EQ(r.at(0), 0);
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 0);

  String::const_iterator b = r.begin();
  String::const_iterator e = r.end();

  ASSERT_TRUE(b == e);

  for (auto i : r) {
    ASSERT_NE(i, 0);
  }

  ASSERT_DEATH({ r.resize(5); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CString8_Length0) {
  StringContainer r("hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CString8_Length5) {
  StringContainer r("hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CString16_Length0) {
  StringContainer r(u"hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CString16_Length5) {
  StringContainer r(u"hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CString32_Length0) {
  StringContainer r(U"hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CString32_Length5) {
  StringContainer r(U"hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CWString_Length0) {
  StringContainer r(L"hello, world.\n", 0);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_CWString_Length5) {
  StringContainer r(L"hello, world.\n", 5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_String8) {
  std::string tmp("hello, world.\n");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 1);
  ASSERT_NE(r.getData8(), nullptr);

  ASSERT_STREQ(r.getData8(), "hello, world.\n");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_String16) {
  std::u16string tmp(u"hello, world.\n");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 2);
  ASSERT_NE(r.getData16(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData32(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_String32) {
  std::u32string tmp(U"hello, world.\n");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), 4);
  ASSERT_NE(r.getData32(), nullptr);

  ASSERT_DEATH({ r.getData8(); }, "");

  ASSERT_DEATH({ r.getData16(); }, "");

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}

TEST(Unit_Core_StringContainer_AsRef, HelloWorld_WString) {
  std::wstring tmp(L"hello, world.\n");
  StringContainer r(tmp);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 14);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(13), '\n');
  ASSERT_EQ(r.at(14), 0);

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

  ASSERT_DEATH({ r.resize(20); }, "");

  r.resize(5);

  ASSERT_TRUE(r.isGood());
  ASSERT_EQ(r.getWidth(), sizeof(wchar_t));

  ASSERT_EQ(r.size(), 5);
  ASSERT_EQ(r.at(0), 'h');
  ASSERT_EQ(r.at(-1), 0);
  ASSERT_EQ(r.at(1), 'e');
  ASSERT_EQ(r.at(4), 'o');
  ASSERT_EQ(r.at(5), 0);

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

  r.resize(5);

  ASSERT_DEATH({ r.resize(6); }, "");
}
