#include <gtest/gtest.h>

#include <whiskey/Source/Source.hpp>

using namespace whiskey;

TEST(Unit_Source_Source, GetDefaultPath) {
	std::stringstream sourceStream;

	Source source0(sourceStream, "A.w");

	ASSERT_STREQ(source0.getDefaultPath().c_str(), "A.w");

	Source source1(sourceStream, "B.w");

	ASSERT_STREQ(source1.getDefaultPath().c_str(), "B.w");

	Source source2(sourceStream);

	ASSERT_STREQ(source2.getDefaultPath().c_str(), W_SOURCE_DEFAULT_PATH);
}

TEST(Unit_Source_Source, More_Empty) {
	std::stringstream sourceStream;
	Source source(sourceStream);

	ASSERT_FALSE(source.more());
}

TEST(Unit_Source_Source, More_NonEmpty) {
	std::stringstream sourceStream("a");
	Source source(sourceStream);

	ASSERT_TRUE(source.more());
}

TEST(Unit_Source_Source, Get_Empty) {
	std::stringstream sourceStream;
	Source source(sourceStream);

	ASSERT_EQ(source.get(), 0);
}

TEST(Unit_Source_Source, Get_NonEmpty) {
	std::stringstream sourceStream("a");
	Source source(sourceStream);

	ASSERT_EQ(source.get(), 'a');
}

TEST(Unit_Source_Source, Get_NewlineUnix) {
	std::stringstream sourceStream("\n");
	Source source(sourceStream);

	ASSERT_EQ(source.get(), '\n');
}

TEST(Unit_Source_Source, Get_NewlineDOS) {
	std::stringstream sourceStream("\r\n");
	Source source(sourceStream);

	ASSERT_EQ(source.get(), '\n');
}

TEST(Unit_Source_Source, Eat_Empty) {
	std::stringstream sourceStream;
	Source source(sourceStream);

	ASSERT_FALSE(source.more());
	ASSERT_EQ(source.eat(), 0);
	ASSERT_FALSE(source.more());
	ASSERT_EQ(source.getOffset(), 0);
}

TEST(Unit_Source_Source, Eat_NonEmpty) {
	std::stringstream sourceStream("a");
	Source source(sourceStream);

	ASSERT_TRUE(source.more());
	ASSERT_EQ(source.eat(), 'a');
	ASSERT_FALSE(source.more());
	ASSERT_EQ(source.getOffset(), 1);
}

TEST(Unit_Source_Source, Eat_NewlineUnix) {
	std::stringstream sourceStream("\n");
	Source source(sourceStream);

	ASSERT_TRUE(source.more());
	ASSERT_EQ(source.eat(), '\n');
	ASSERT_FALSE(source.more());
	ASSERT_EQ(source.getOffset(), 1);
}

TEST(Unit_Source_Source, Eat_NewlineDOS) {
	std::stringstream sourceStream("\r\na");
	Source source(sourceStream);

	ASSERT_TRUE(source.more());
	ASSERT_EQ(source.eat(), '\n');
	ASSERT_EQ(source.getOffset(), 2);

	ASSERT_TRUE(source.more());
	ASSERT_EQ(source.eat(), 'a');
	ASSERT_FALSE(source.more());
	ASSERT_EQ(source.getOffset(), 3);
}

TEST(Unit_Source_Source, SetOffset_ToBeginning) {
	std::stringstream sourceStream("hello");
	Source source(sourceStream);

	ASSERT_EQ(source.eat(), 'h');
	ASSERT_EQ(source.eat(), 'e');
	ASSERT_EQ(source.eat(), 'l');
	ASSERT_EQ(source.eat(), 'l');
	ASSERT_EQ(source.eat(), 'o');
	ASSERT_FALSE(source.more());
	ASSERT_EQ(source.getOffset(), 5);

	source.setOffset(0);
	ASSERT_EQ(source.getOffset(), 0);
	ASSERT_TRUE(source.more());
	ASSERT_EQ(source.get(), 'h');
	ASSERT_EQ(source.eat(), 'h');
}

TEST(Unit_Source_Source, SetOffset_ToMiddle) {
	std::stringstream sourceStream("hello");
	Source source(sourceStream);

	source.setOffset(4);
	ASSERT_TRUE(source.more());
	ASSERT_EQ(source.getOffset(), 4);
	ASSERT_EQ(source.get(), 'o');
	ASSERT_EQ(source.eat(), 'o');
	ASSERT_FALSE(source.more());
}
