#include <gtest/gtest.h>

#include <whiskey/Unicode/FileByteOutStream.hpp>

using namespace whiskey;

TEST(Unicode_Unit_FileByteOutStream, Unopened) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path);

	ASSERT_FALSE(bs.isOpen());

	ASSERT_EQ(bs.getEncoding(), Encoding::Auto);

	bs.setEncoding(Encoding::UTF8);

	ASSERT_EQ(bs.getEncoding(), Encoding::UTF8);

	ASSERT_FALSE(bs.isOpen());

	ASSERT_DEATH({
		bs.close();
	}, "");

	ASSERT_DEATH({
		bs.writeChar(0);
	}, "");
}

TEST(Unicode_Unit_FileByteOutStream, Auto) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path);

	ASSERT_TRUE(bs.open());

	bs.writeChar('h');
	bs.writeChar('e');
	bs.writeChar('l');
	bs.writeChar('l');
	bs.writeChar('o');

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 5);
	fclose(f);

	ASSERT_EQ(buf[0], 'h');
	ASSERT_EQ(buf[1], 'e');
	ASSERT_EQ(buf[2], 'l');
	ASSERT_EQ(buf[3], 'l');
	ASSERT_EQ(buf[4], 'o');
}

TEST(Unicode_Unit_FileByteOutStream, UTF8) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path, Encoding::UTF8);

	ASSERT_TRUE(bs.open());

	bs.writeChar('h');
	bs.writeChar('e');
	bs.writeChar('l');
	bs.writeChar('l');
	bs.writeChar('o');

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 8);
	fclose(f);

	ASSERT_EQ(buf[0], '\xef');
	ASSERT_EQ(buf[1], '\xbb');
	ASSERT_EQ(buf[2], '\xbf');
	ASSERT_EQ(buf[3], 'h');
	ASSERT_EQ(buf[4], 'e');
	ASSERT_EQ(buf[5], 'l');
	ASSERT_EQ(buf[6], 'l');
	ASSERT_EQ(buf[7], 'o');
}

TEST(Unicode_Unit_FileByteOutStream, UTF16LE) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path, Encoding::UTF16LE);

	ASSERT_TRUE(bs.open());

	bs.writeChar('h');
	bs.writeChar('e');
	bs.writeChar('l');
	bs.writeChar('l');
	bs.writeChar('o');

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 7);
	fclose(f);

	ASSERT_EQ(buf[0], '\xfe');
	ASSERT_EQ(buf[1], '\xff');
	ASSERT_EQ(buf[2], 'h');
	ASSERT_EQ(buf[3], 'e');
	ASSERT_EQ(buf[4], 'l');
	ASSERT_EQ(buf[5], 'l');
	ASSERT_EQ(buf[6], 'o');
}

TEST(Unicode_Unit_FileByteOutStream, UTF16BE) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path, Encoding::UTF16BE);

	ASSERT_TRUE(bs.open());

	bs.writeChar('h');
	bs.writeChar('e');
	bs.writeChar('l');
	bs.writeChar('l');
	bs.writeChar('o');

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 7);
	fclose(f);

	ASSERT_EQ(buf[0], '\xff');
	ASSERT_EQ(buf[1], '\xfe');
	ASSERT_EQ(buf[2], 'h');
	ASSERT_EQ(buf[3], 'e');
	ASSERT_EQ(buf[4], 'l');
	ASSERT_EQ(buf[5], 'l');
	ASSERT_EQ(buf[6], 'o');
}

TEST(Unicode_Unit_FileByteOutStream, UTF32LE) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path, Encoding::UTF32LE);

	ASSERT_TRUE(bs.open());

	bs.writeChar('h');
	bs.writeChar('e');
	bs.writeChar('l');
	bs.writeChar('l');
	bs.writeChar('o');

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 9);
	fclose(f);

	ASSERT_EQ(buf[0], '\xff');
	ASSERT_EQ(buf[1], '\xfe');
	ASSERT_EQ(buf[2], '\x00');
	ASSERT_EQ(buf[3], '\x00');
	ASSERT_EQ(buf[4], 'h');
	ASSERT_EQ(buf[5], 'e');
	ASSERT_EQ(buf[6], 'l');
	ASSERT_EQ(buf[7], 'l');
	ASSERT_EQ(buf[8], 'o');
}

TEST(Unicode_Unit_FileByteOutStream, UTF32BE) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path, Encoding::UTF32BE);

	ASSERT_TRUE(bs.open());

	bs.writeChar('h');
	bs.writeChar('e');
	bs.writeChar('l');
	bs.writeChar('l');
	bs.writeChar('o');

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 9);
	fclose(f);

	ASSERT_EQ(buf[0], '\x00');
	ASSERT_EQ(buf[1], '\x00');
	ASSERT_EQ(buf[2], '\xfe');
	ASSERT_EQ(buf[3], '\xff');
	ASSERT_EQ(buf[4], 'h');
	ASSERT_EQ(buf[5], 'e');
	ASSERT_EQ(buf[6], 'l');
	ASSERT_EQ(buf[7], 'l');
	ASSERT_EQ(buf[8], 'o');
}
