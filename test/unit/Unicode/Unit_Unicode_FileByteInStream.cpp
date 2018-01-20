#include <gtest/gtest.h>

#include <whiskey/Unicode/FileByteInStream.hpp>

using namespace whiskey;

TEST(Unicode_Unit_FileByteInStream, Unopened) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteInStream bs(path);

	ASSERT_FALSE(bs.isOpen());

	ASSERT_DEATH({
		bs.isMore();
	}, "");

	ASSERT_DEATH({
		bs.getChar();
	}, "");

	ASSERT_DEATH({
		bs.eatChar();
	}, "");

	ASSERT_DEATH({
		bs.getLength();
	}, "");

	ASSERT_DEATH({
		bs.getEncoding();
	}, "");
}

TEST(Unicode_Unit_FileByteInStream, CannotOpen) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	remove(path);
	
	FileByteInStream bs(path);

	if (bs.open()) {
		bs.close();
		FAIL() << "Should be unable to open file.";
	}
}

TEST(Unicode_Unit_FileByteInStream, Empty) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FILE *f = fopen(path, "w");
	fclose(f);

	FileByteInStream bs(path);

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 0);
	ASSERT_EQ(bs.getEncoding(), Encoding::Auto);

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	ASSERT_FALSE(bs.isOpen());

	remove(path);
}

TEST(Unicode_Unit_FileByteInStream, SimpleAuto) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FILE *f = fopen(path, "w");
	fputs("hello", f);
	fclose(f);

	f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	ASSERT_EQ(ftell(f), 5);
	fclose(f);

	FileByteInStream bs(path);

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 5);
	ASSERT_EQ(bs.getEncoding(), Encoding::Auto);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'h');
	ASSERT_EQ(bs.eatChar(), 'h');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'e');
	ASSERT_EQ(bs.eatChar(), 'e');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'o');
	ASSERT_EQ(bs.eatChar(), 'o');

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	remove(path);
}

TEST(Unicode_Unit_FileByteInStream, SimpleUTF8) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FILE *f = fopen(path, "w");
	fputs("\xef\xbb\xbfhello", f);
	fclose(f);

	FileByteInStream bs(path);

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 5);
	ASSERT_EQ(bs.getEncoding(), Encoding::UTF8);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'h');
	ASSERT_EQ(bs.eatChar(), 'h');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'e');
	ASSERT_EQ(bs.eatChar(), 'e');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'o');
	ASSERT_EQ(bs.eatChar(), 'o');

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	remove(path);
}

TEST(Unicode_Unit_FileByteInStream, SimpleUTF16LE) {
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

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 10);
	ASSERT_EQ(bs.getEncoding(), Encoding::UTF16LE);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'h');
	ASSERT_EQ(bs.eatChar(), 'h');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'e');
	ASSERT_EQ(bs.eatChar(), 'e');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'o');
	ASSERT_EQ(bs.eatChar(), 'o');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	remove(path);
}

TEST(Unicode_Unit_FileByteInStream, SimpleUTF16BE) {
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

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 10);
	ASSERT_EQ(bs.getEncoding(), Encoding::UTF16BE);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'h');
	ASSERT_EQ(bs.eatChar(), 'h');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'e');
	ASSERT_EQ(bs.eatChar(), 'e');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'o');
	ASSERT_EQ(bs.eatChar(), 'o');

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	remove(path);
}

TEST(Unicode_Unit_FileByteInStream, SimpleUTF32LE) {
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

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 20);
	ASSERT_EQ(bs.getEncoding(), Encoding::UTF32LE);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'h');
	ASSERT_EQ(bs.eatChar(), 'h');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'e');
	ASSERT_EQ(bs.eatChar(), 'e');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'o');
	ASSERT_EQ(bs.eatChar(), 'o');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	remove(path);
}

TEST(Unicode_Unit_FileByteInStream, SimpleUTF32BE) {
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

	ASSERT_TRUE(bs.open());

	ASSERT_EQ(bs.getLength(), 20);
	ASSERT_EQ(bs.getEncoding(), Encoding::UTF32BE);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'h');
	ASSERT_EQ(bs.eatChar(), 'h');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'e');
	ASSERT_EQ(bs.eatChar(), 'e');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'l');
	ASSERT_EQ(bs.eatChar(), 'l');

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	ASSERT_TRUE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 'o');
	ASSERT_EQ(bs.eatChar(), 'o');

	ASSERT_FALSE(bs.isMore());
	ASSERT_EQ(bs.getChar(), 0);
	ASSERT_EQ(bs.eatChar(), 0);

	bs.close();

	remove(path);
}
