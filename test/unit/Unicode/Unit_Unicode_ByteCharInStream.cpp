#include <gtest/gtest.h>

#include <whiskey/Unicode/ByteCharInStream.hpp>
#include <whiskey/Unicode/FileByteInStream.hpp>

using namespace whiskey;

TEST(Unicode_Unit_ByteCharInStream, Unopened) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF8);

  ASSERT_EQ(cs.getEncoding(), Encoding::UTF8);

  ASSERT_DEATH({ cs.isMore(); }, "");

  ASSERT_DEATH({ cs.getChar(); }, "");

  ASSERT_DEATH({ cs.eatChar(); }, "");
}

TEST(Unicode_Unit_ByteCharInStream, Empty) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF8);

  ASSERT_TRUE(bs.open());

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}

TEST(Unicode_Unit_ByteCharInStream, SimpleAuto) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fputs("hello", f);
  fclose(f);

  f = fopen(path, "r");
  fseek(f, 0, SEEK_END);
  ASSERT_EQ(ftell(f), 5);
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF8);

  ASSERT_TRUE(bs.open());

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'h');
  ASSERT_EQ(cs.eatChar(), 'h');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'e');
  ASSERT_EQ(cs.eatChar(), 'e');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'o');
  ASSERT_EQ(cs.eatChar(), 'o');

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}

TEST(Unicode_Unit_ByteCharInStream, SimpleUTF8) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fputs("\xef\xbb\xbfhello", f);
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF8);

  ASSERT_TRUE(bs.open());

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'h');
  ASSERT_EQ(cs.eatChar(), 'h');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'e');
  ASSERT_EQ(cs.eatChar(), 'e');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'o');
  ASSERT_EQ(cs.eatChar(), 'o');

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}

TEST(Unicode_Unit_ByteCharInStream, SimpleUTF16LE) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fputc('\xfe', f);
  fputc('\xff', f);
  fputc('h', f);
  fputc('\x00', f);
  fputc('e', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('o', f);
  fputc('\x00', f);
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF16LE);

  ASSERT_TRUE(bs.open());

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'h');
  ASSERT_EQ(cs.eatChar(), 'h');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'e');
  ASSERT_EQ(cs.eatChar(), 'e');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'o');
  ASSERT_EQ(cs.eatChar(), 'o');

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}

TEST(Unicode_Unit_ByteCharInStream, SimpleUTF16BE) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fputc('\xff', f);
  fputc('\xfe', f);
  fputc('\x00', f);
  fputc('h', f);
  fputc('\x00', f);
  fputc('e', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('o', f);
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF16BE);

  ASSERT_TRUE(bs.open());

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'h');
  ASSERT_EQ(cs.eatChar(), 'h');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'e');
  ASSERT_EQ(cs.eatChar(), 'e');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'o');
  ASSERT_EQ(cs.eatChar(), 'o');

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}

TEST(Unicode_Unit_ByteCharInStream, SimpleUTF32LE) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fputc('\xff', f);
  fputc('\xfe', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('h', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('e', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('o', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF32LE);

  ASSERT_TRUE(bs.open());

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'h');
  ASSERT_EQ(cs.eatChar(), 'h');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'e');
  ASSERT_EQ(cs.eatChar(), 'e');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'o');
  ASSERT_EQ(cs.eatChar(), 'o');

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}

TEST(Unicode_Unit_ByteCharInStream, SimpleUTF32BE) {
  const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

  FILE *f = fopen(path, "w");
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\xfe', f);
  fputc('\xff', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('h', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('e', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('l', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('\x00', f);
  fputc('o', f);
  fclose(f);

  FileByteInStream bs(path);
  ByteCharInStream cs(bs, Encoding::UTF32BE);

  ASSERT_TRUE(bs.open());

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'h');
  ASSERT_EQ(cs.eatChar(), 'h');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'e');
  ASSERT_EQ(cs.eatChar(), 'e');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'l');
  ASSERT_EQ(cs.eatChar(), 'l');

  ASSERT_TRUE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 'o');
  ASSERT_EQ(cs.eatChar(), 'o');

  ASSERT_FALSE(cs.isMore());
  ASSERT_EQ(cs.getChar(), 0);
  ASSERT_EQ(cs.eatChar(), 0);

  bs.close();

  remove(path);
}
