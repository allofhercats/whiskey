#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/Parsing/EvalLiterals.hpp>
#include <whiskey/Source/Location.hpp>
#include <whiskey/Source/Range.hpp>
#include <whiskey/Source/Source.hpp>

using namespace whiskey;

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_0) {
  uint64_t value;

  std::string str = "0b";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_1) {
  uint64_t value;

  std::string str = "0b0";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_2) {
  uint64_t value;

  std::string str = "0b1";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 1);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_3) {
  uint64_t value;

  std::string str = "0b2";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_4) {
  uint64_t value;

  std::string str = "0b10";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 2);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_5) {
  uint64_t value;

  std::string str = "0b11";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 3);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base2_6) {
  uint64_t value;

  std::string str = "0b10011011";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 155);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_0) {
  uint64_t value;

  std::string str = "0";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_1) {
  uint64_t value;

  std::string str = "00";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_2) {
  uint64_t value;

  std::string str = "01";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 1);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_3) {
  uint64_t value;

  std::string str = "07";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 7);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_4) {
  uint64_t value;

  std::string str = "08";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_5) {
  uint64_t value;

  std::string str = "033";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 27);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base8_6) {
  uint64_t value;

  std::string str = "07777";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 4095);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base10_0) {
  uint64_t value;

  std::string str = "1";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 1);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base10_1) {
  uint64_t value;

  std::string str = "9";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 9);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base10_2) {
  uint64_t value;

  std::string str = "19";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 19);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base10_3) {
  uint64_t value;

  std::string str = "123456789";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 123456789);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_0) {
  uint64_t value;

  std::string str = "0x";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_1) {
  uint64_t value;

  std::string str = "0x0";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 0);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_2) {
  uint64_t value;

  std::string str = "0x9";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 9);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_3) {
  uint64_t value;

  std::string str = "0xa";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 10);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_4) {
  uint64_t value;

  std::string str = "0xA";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 10);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_5) {
  uint64_t value;

  std::string str = "0xf";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 15);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_6) {
  uint64_t value;

  std::string str = "0xF";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 15);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_7) {
  uint64_t value;

  std::string str = "0xdeadbeef";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralUInt(rng, value));
  ASSERT_EQ(value, 0xdeadbeef);
}

TEST(Unit_Parsing_EvalLiterals, UInt_Base16_8) {
  uint64_t value;

  std::string str = "0xgeadbeef";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, UInt_NoBase_0) {
  uint64_t value;

  std::string str = "a";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, UInt_NoBase_1) {
  uint64_t value;

  std::string str = "5a";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralUInt(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Real_0) {
  long double value;

  std::string str = "0.0";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Parsing_EvalLiterals, Real_1) {
  long double value;

  std::string str = ".0";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Parsing_EvalLiterals, Real_2) {
  long double value;

  std::string str = "0.";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Parsing_EvalLiterals, Real_3) {
  long double value;

  std::string str = ".";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(Unit_Parsing_EvalLiterals, Real_4) {
  long double value;

  std::string str = "69.";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 69.0);
}

TEST(Unit_Parsing_EvalLiterals, Real_5) {
  long double value;

  std::string str = ".420";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 0.420);
}

TEST(Unit_Parsing_EvalLiterals, Real_6) {
  long double value;

  std::string str = "69.420";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralReal(rng, value));
  ASSERT_DOUBLE_EQ(value, 69.420);
}

TEST(Unit_Parsing_EvalLiterals, Char_0) {
  char value;

  std::string str = "'a'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, 'a');
}

TEST(Unit_Parsing_EvalLiterals, Char_1) {
  char value;

  std::string str = "'a";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralChar(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Char_2) {
  char value;

  std::string str = "a'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralChar(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Char_3) {
  char value;

  std::string str = "''";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralChar(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Char_4) {
  char value;

  std::string str = "'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralChar(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Char_5) {
  char value;

  std::string str = "'\\a'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\a');
}

TEST(Unit_Parsing_EvalLiterals, Char_6) {
  char value;

  std::string str = "'\\0'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Parsing_EvalLiterals, Char_7) {
  char value;

  std::string str = "'\\7'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\7');
}

TEST(Unit_Parsing_EvalLiterals, Char_8) {
  char value;

  std::string str = "'\\00'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Parsing_EvalLiterals, Char_9) {
  char value;

  std::string str = "'\\000'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Parsing_EvalLiterals, Char_10) {
  char value;

  std::string str = "'\\177'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\177');
}

TEST(Unit_Parsing_EvalLiterals, Char_11) {
  char value;

  std::string str = "'\\x00'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\0');
}

TEST(Unit_Parsing_EvalLiterals, Char_12) {
  char value;

  std::string str = "'\\x0'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralChar(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Char_13) {
  char value;

  std::string str = "'\\x'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralChar(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, Char_25) {
  char value;

  std::string str = "'\\\\'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\\');
}

TEST(Unit_Parsing_EvalLiterals, Char_26) {
  char value;

  std::string str = "'\\''";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '\'');
}

TEST(Unit_Parsing_EvalLiterals, Char_27) {
  char value;

  std::string str = "'\"'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '"');
}

TEST(Unit_Parsing_EvalLiterals, Char_28) {
  char value;

  std::string str = "'\\?'";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralChar(rng, value));
  ASSERT_EQ(value, '?');
}

TEST(Unit_Parsing_EvalLiterals, String_0) {
  std::string value;

  std::string str = "\"a\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "a");
}

TEST(Unit_Parsing_EvalLiterals, String_1) {
  std::string value;

  std::string str = "\"a";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralString(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, String_2) {
  std::string value;

  std::string str = "a\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralString(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, String_3) {
  std::string value;

  std::string str = "\"\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "");
}

TEST(Unit_Parsing_EvalLiterals, String_4) {
  std::string value;

  std::string str = "\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralString(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, String_5) {
  std::string value;

  std::string str = "\"\\a\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\a");
}

TEST(Unit_Parsing_EvalLiterals, String_6) {
  std::string value;

  std::string str = "\"\\0\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Parsing_EvalLiterals, String_7) {
  std::string value;

  std::string str = "\"\\7\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\7");
}

TEST(Unit_Parsing_EvalLiterals, String_8) {
  std::string value;

  std::string str = "\"\\00\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Parsing_EvalLiterals, String_9) {
  std::string value;

  std::string str = "\"\\000\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Parsing_EvalLiterals, String_10) {
  std::string value;

  std::string str = "\"\\177\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\177");
}

TEST(Unit_Parsing_EvalLiterals, String_11) {
  std::string value;

  std::string str = "\"\\x00\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\0");
}

TEST(Unit_Parsing_EvalLiterals, String_12) {
  std::string value;

  std::string str = "\"\\x0\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralString(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, String_13) {
  std::string value;

  std::string str = "\"\\x\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_FALSE(evalLiteralString(rng, value));
}

TEST(Unit_Parsing_EvalLiterals, String_25) {
  std::string value;

  std::string str = "\"\\\\\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\\");
}

TEST(Unit_Parsing_EvalLiterals, String_26) {
  std::string value;

  std::string str = "\"\\'\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\'");
}

TEST(Unit_Parsing_EvalLiterals, String_27) {
  std::string value;

  std::string str = "\"\\\"\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "\"");
}

TEST(Unit_Parsing_EvalLiterals, String_28) {
  std::string value;

  std::string str = "\"\\?\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "?");
}

TEST(Unit_Parsing_EvalLiterals, String_29) {
  std::string value;

  std::string str = "\"Hello, world.\\n\"";

  Source src;
  src.loadString(str);

  Location loc(src);

  Range rng(loc, str.size());

  ASSERT_TRUE(evalLiteralString(rng, value));
  ASSERT_STREQ(value.c_str(), "Hello, world.\n");
}
