#include <gtest/gtest.h>

#include <whiskey/Unicode/FileByteOutStream.hpp>
#include <whiskey/Unicode/ByteCharOutStream.hpp>

using namespace whiskey;

TEST(Unicode_Unit_ByteCharOutStream, Unopened) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path);
	ByteCharOutStream cs(bs, Encoding::UTF8);

	ASSERT_EQ(cs.getEncoding(), Encoding::UTF8);
	
	ASSERT_DEATH({
		cs.write(0);
	}, "");
}

TEST(Unicode_Unit_ByteCharOutStream, Empty) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path);
	ByteCharOutStream cs(bs, Encoding::UTF8);

	ASSERT_TRUE(bs.open());

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 0);
	fclose(f);

	remove(path);
}

TEST(Unicode_Unit_ByteCharOutStream, SimpleUTF8) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path);
	ByteCharOutStream cs(bs, Encoding::UTF8);

	ASSERT_TRUE(bs.open());

	cs.write("hello");

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

	remove(path);
}

TEST(Unicode_Unit_ByteCharOutStream, SimpleUTF16LE) {
	const char *path = "thisIsAFileNameThatProbablyDoesntExist.txt";

	FileByteOutStream bs(path);
	ByteCharOutStream cs(bs, Encoding::UTF16LE);

	ASSERT_TRUE(bs.open());

	cs.write(StringRef("hello"));

	bs.close();

	FILE *f = fopen(path, "r");
	ASSERT_NE(f, nullptr);

	Char8 buf[1024];
	ASSERT_EQ(fread(buf, 1, 1024, f), 10);
	fclose(f);

	ASSERT_EQ(buf[0], 'h');
	ASSERT_EQ(buf[1], 0);
	ASSERT_EQ(buf[2], 'e');
	ASSERT_EQ(buf[3], 0);
	ASSERT_EQ(buf[4], 'l');
	ASSERT_EQ(buf[5], 0);
	ASSERT_EQ(buf[6], 'l');
	ASSERT_EQ(buf[7], 0);
	ASSERT_EQ(buf[8], 'o');
	ASSERT_EQ(buf[9], 0);

	remove(path);
}
