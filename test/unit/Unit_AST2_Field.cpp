#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Unit_AST2_Field, Int) {
	Field *f0 = Field::createInt(5);

	ASSERT_NE(f0, nullptr);

	Field *f1 = f0->clone();

	ASSERT_NE(f1, nullptr);
	ASSERT_NE(f0, f1);

	ASSERT_EQ(f0->getKind(), Field::Kind::Int);
	ASSERT_EQ(f1->getKind(), Field::Kind::Int);

	ASSERT_EQ(f0->getInt(), 5);
	ASSERT_EQ(f1->getInt(), 5);

	f0->setInt(-5);

	ASSERT_EQ(f0->getInt(), -5);
	ASSERT_EQ(f1->getInt(), 5);

	ASSERT_DEATH({
		f0->getReal();
	}, "");

	ASSERT_DEATH({
		f0->setReal(0.0);
	}, "");

	ASSERT_DEATH({
		f0->getString8();
	}, "");

	ASSERT_DEATH({
		f0->setString8("");
	}, "");

	ASSERT_DEATH({
		f0->getString16();
	}, "");

	ASSERT_DEATH({
		f0->setString16(u"");
	}, "");

	ASSERT_DEATH({
		f0->getString32();
	}, "");

	ASSERT_DEATH({
		f0->setString32(U"");
	}, "");

	ASSERT_EQ(f0->getLength(), 0);
	ASSERT_EQ(f1->getLength(), 0);

	ASSERT_DEATH({
		f0->getNode();
	}, "");

	ASSERT_DEATH({
		((const Field *)f0)->getNode();
	}, "");

	ASSERT_DEATH({
		f0->setNode(nullptr);
	}, "");

	ASSERT_FALSE(f0->compare(f1));

	f1->setInt(-5);
	ASSERT_TRUE(f0->compare(f1));

	delete f0;

	ASSERT_EQ(f1->getInt(), -5);

	delete f1;
}

TEST(Unit_AST2_Field, Real) {
	Field *f0 = Field::createReal(5.2);

	ASSERT_NE(f0, nullptr);

	Field *f1 = f0->clone();

	ASSERT_NE(f1, nullptr);
	ASSERT_NE(f0, f1);

	ASSERT_EQ(f0->getKind(), Field::Kind::Real);
	ASSERT_EQ(f1->getKind(), Field::Kind::Real);

	ASSERT_EQ(f0->getReal(), 5.2);
	ASSERT_EQ(f1->getReal(), 5.2);

	f0->setReal(-5.2);

	ASSERT_EQ(f0->getReal(), -5.2);
	ASSERT_EQ(f1->getReal(), 5.2);

	ASSERT_DEATH({
		f0->getInt();
	}, "");

	ASSERT_DEATH({
		f0->setInt(0);
	}, "");

	ASSERT_DEATH({
		f0->getString8();
	}, "");

	ASSERT_DEATH({
		f0->setString8("");
	}, "");

	ASSERT_DEATH({
		f0->getString16();
	}, "");

	ASSERT_DEATH({
		f0->setString16(u"");
	}, "");

	ASSERT_DEATH({
		f0->getString32();
	}, "");

	ASSERT_DEATH({
		f0->setString32(U"");
	}, "");

	ASSERT_EQ(f0->getLength(), 0);
	ASSERT_EQ(f1->getLength(), 0);

	ASSERT_DEATH({
		f0->getNode();
	}, "");

	ASSERT_DEATH({
		((const Field *)f0)->getNode();
	}, "");

	ASSERT_DEATH({
		f0->setNode(nullptr);
	}, "");

	ASSERT_FALSE(f0->compare(f1));

	f1->setReal(-5.2);
	ASSERT_TRUE(f0->compare(f1));

	delete f0;

	ASSERT_EQ(f1->getReal(), -5.2);

	delete f1;
}

TEST(Unit_AST2_Field, String8) {
	Field *f0 = Field::createString8("hello, world\n");

	ASSERT_NE(f0, nullptr);

	Field *f1 = f0->clone();

	ASSERT_NE(f1, nullptr);
	ASSERT_NE(f0, f1);

	ASSERT_EQ(f0->getKind(), Field::Kind::String8);
	ASSERT_EQ(f1->getKind(), Field::Kind::String8);

	ASSERT_STREQ(f0->getString8(), "hello, world\n");
	ASSERT_STREQ(f1->getString8(), "hello, world\n");

	f0->setString8("hello, world\n", 5);

	ASSERT_STREQ(f0->getString8(), "hello");
	ASSERT_STREQ(f1->getString8(), "hello, world\n");

	ASSERT_DEATH({
		f0->getInt();
	}, "");

	ASSERT_DEATH({
		f0->setInt(0);
	}, "");

	ASSERT_DEATH({
		f0->getReal();
	}, "");

	ASSERT_DEATH({
		f0->setReal(0.0);
	}, "");

	ASSERT_DEATH({
		f0->getString16();
	}, "");

	ASSERT_DEATH({
		f0->setString16(u"");
	}, "");

	ASSERT_DEATH({
		f0->getString32();
	}, "");

	ASSERT_DEATH({
		f0->setString32(U"");
	}, "");

	ASSERT_EQ(f0->getLength(), 5);
	ASSERT_EQ(f1->getLength(), 13);

	ASSERT_DEATH({
		f0->getNode();
	}, "");

	ASSERT_DEATH({
		((const Field *)f0)->getNode();
	}, "");

	ASSERT_DEATH({
		f0->setNode(nullptr);
	}, "");

	ASSERT_FALSE(f0->compare(f1));

	f1->setString8("hello");
	ASSERT_EQ(f0->getLength(), 5);
	ASSERT_EQ(f1->getLength(), 5);
	ASSERT_EQ(f0->getString8()[0], 'h');
	ASSERT_EQ(f1->getString8()[0], 'h');
	ASSERT_EQ(f0->getString8()[1], 'e');
	ASSERT_EQ(f1->getString8()[1], 'e');
	ASSERT_EQ(f0->getString8()[2], 'l');
	ASSERT_EQ(f1->getString8()[2], 'l');
	ASSERT_EQ(f0->getString8()[3], 'l');
	ASSERT_EQ(f1->getString8()[3], 'l');
	ASSERT_EQ(f0->getString8()[4], 'o');
	ASSERT_EQ(f1->getString8()[4], 'o');
	ASSERT_TRUE(f0->compare(f1));

	delete f0;

	ASSERT_STREQ(f1->getString8(), "hello");

	delete f1;
}

TEST(Unit_AST2_Field, String16) {
	Field *f0 = Field::createString16(u"hello, world\n");

	ASSERT_NE(f0, nullptr);

	Field *f1 = f0->clone();

	ASSERT_NE(f1, nullptr);
	ASSERT_NE(f0, f1);

	ASSERT_EQ(f0->getKind(), Field::Kind::String16);
	ASSERT_EQ(f1->getKind(), Field::Kind::String16);

	ASSERT_TRUE(std::u16string(f0->getString16(), 13) == u"hello, world\n");
	ASSERT_TRUE(std::u16string(f1->getString16(), 13) == u"hello, world\n");

	f0->setString16(u"hello, world\n", 5);

	ASSERT_TRUE(std::u16string(f0->getString16(), 5) == u"hello");
	ASSERT_TRUE(std::u16string(f1->getString16(), 13) == u"hello, world\n");

	ASSERT_DEATH({
		f0->getInt();
	}, "");

	ASSERT_DEATH({
		f0->setInt(0);
	}, "");

	ASSERT_DEATH({
		f0->getReal();
	}, "");

	ASSERT_DEATH({
		f0->setReal(0.0);
	}, "");

	ASSERT_DEATH({
		f0->getString8();
	}, "");

	ASSERT_DEATH({
		f0->setString8("");
	}, "");

	ASSERT_DEATH({
		f0->getString32();
	}, "");

	ASSERT_DEATH({
		f0->setString32(U"");
	}, "");

	ASSERT_EQ(f0->getLength(), 5);
	ASSERT_EQ(f1->getLength(), 13);

	ASSERT_DEATH({
		f0->getNode();
	}, "");

	ASSERT_DEATH({
		((const Field *)f0)->getNode();
	}, "");

	ASSERT_DEATH({
		f0->setNode(nullptr);
	}, "");

	ASSERT_FALSE(f0->compare(f1));

	f1->setString16(u"hello");
	ASSERT_EQ(f0->getLength(), 5);
	ASSERT_EQ(f1->getLength(), 5);
	ASSERT_EQ(f0->getString16()[0], 'h');
	ASSERT_EQ(f1->getString16()[0], 'h');
	ASSERT_EQ(f0->getString16()[1], 'e');
	ASSERT_EQ(f1->getString16()[1], 'e');
	ASSERT_EQ(f0->getString16()[2], 'l');
	ASSERT_EQ(f1->getString16()[2], 'l');
	ASSERT_EQ(f0->getString16()[3], 'l');
	ASSERT_EQ(f1->getString16()[3], 'l');
	ASSERT_EQ(f0->getString16()[4], 'o');
	ASSERT_EQ(f1->getString16()[4], 'o');
	ASSERT_TRUE(f0->compare(f1));

	delete f0;

	ASSERT_TRUE(std::u16string(f1->getString16(), 5) == u"hello");

	delete f1;
}

TEST(Unit_AST2_Field, String32) {
	Field *f0 = Field::createString32(U"hello, world\n");

	ASSERT_NE(f0, nullptr);

	Field *f1 = f0->clone();

	ASSERT_NE(f1, nullptr);
	ASSERT_NE(f0, f1);

	ASSERT_EQ(f0->getKind(), Field::Kind::String32);
	ASSERT_EQ(f1->getKind(), Field::Kind::String32);

	ASSERT_TRUE(std::u32string(f0->getString32(), 13) == U"hello, world\n");
	ASSERT_TRUE(std::u32string(f1->getString32(), 13) == U"hello, world\n");

	f0->setString32(U"hello, world\n", 5);

	ASSERT_TRUE(std::u32string(f0->getString32(), 5) == U"hello");
	ASSERT_TRUE(std::u32string(f1->getString32(), 13) == U"hello, world\n");

	ASSERT_DEATH({
		f0->getInt();
	}, "");

	ASSERT_DEATH({
		f0->setInt(0);
	}, "");

	ASSERT_DEATH({
		f0->getReal();
	}, "");

	ASSERT_DEATH({
		f0->setReal(0.0);
	}, "");

	ASSERT_DEATH({
		f0->getString8();
	}, "");

	ASSERT_DEATH({
		f0->setString8("");
	}, "");

	ASSERT_DEATH({
		f0->getString16();
	}, "");

	ASSERT_DEATH({
		f0->setString16(u"");
	}, "");

	ASSERT_EQ(f0->getLength(), 5);
	ASSERT_EQ(f1->getLength(), 13);

	ASSERT_DEATH({
		f0->getNode();
	}, "");

	ASSERT_DEATH({
		((const Field *)f0)->getNode();
	}, "");

	ASSERT_DEATH({
		f0->setNode(nullptr);
	}, "");

	ASSERT_FALSE(f0->compare(f1));

	f1->setString32(U"hello");
	ASSERT_EQ(f0->getLength(), 5);
	ASSERT_EQ(f1->getLength(), 5);
	ASSERT_EQ(f0->getString32()[0], 'h');
	ASSERT_EQ(f1->getString32()[0], 'h');
	ASSERT_EQ(f0->getString32()[1], 'e');
	ASSERT_EQ(f1->getString32()[1], 'e');
	ASSERT_EQ(f0->getString32()[2], 'l');
	ASSERT_EQ(f1->getString32()[2], 'l');
	ASSERT_EQ(f0->getString32()[3], 'l');
	ASSERT_EQ(f1->getString32()[3], 'l');
	ASSERT_EQ(f0->getString32()[4], 'o');
	ASSERT_EQ(f1->getString32()[4], 'o');
	ASSERT_TRUE(f0->compare(f1));

	delete f0;

	ASSERT_TRUE(std::u32string(f1->getString32(), 5) == U"hello");

	delete f1;
}

TEST(Unit_AST2_Field, Node) {
	Field *f0 = Field::createNode(nullptr);

	ASSERT_NE(f0, nullptr);

	Field *f1 = f0->clone();

	ASSERT_NE(f1, nullptr);
	ASSERT_NE(f0, f1);

	ASSERT_EQ(f0->getKind(), Field::Kind::Node);
	ASSERT_EQ(f1->getKind(), Field::Kind::Node);

	ASSERT_EQ(f0->getNode(), nullptr);
	ASSERT_EQ(f1->getNode(), nullptr);

	ASSERT_DEATH({
		f0->getInt();
	}, "");

	ASSERT_DEATH({
		f0->setInt(0);
	}, "");

	ASSERT_DEATH({
		f0->getReal();
	}, "");

	ASSERT_DEATH({
		f0->setReal(0.0);
	}, "");

	ASSERT_DEATH({
		f0->getString8();
	}, "");

	ASSERT_DEATH({
		f0->setString8("");
	}, "");

	ASSERT_DEATH({
		f0->getString16();
	}, "");

	ASSERT_DEATH({
		f0->setString16(u"");
	}, "");

	ASSERT_DEATH({
		f0->getString32();
	}, "");

	ASSERT_DEATH({
		f0->setString32(U"");
	}, "");

	ASSERT_EQ(f0->getLength(), 0);
	ASSERT_EQ(f1->getLength(), 0);

	ASSERT_TRUE(f0->compare(f1));

	delete f0;

	ASSERT_EQ(f1->getNode(), nullptr);

	delete f1;
}
