#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/AST/Field.hpp>

using namespace whiskey;

TEST(Unit_AST_Field, Int) {
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

  ASSERT_DEATH({ f0->getReal(); }, "");

  ASSERT_DEATH({ f0->setReal(0.0); }, "");

  ASSERT_DEATH({ f0->getString(); }, "");

  ASSERT_DEATH({ f0->setString(""); }, "");

  ASSERT_DEATH({ f0->getNode(); }, "");

  ASSERT_DEATH({ ((const Field *)f0)->getNode(); }, "");

  ASSERT_DEATH({ f0->setNode(nullptr); }, "");

  ASSERT_FALSE(f0->compare(f1));

  f1->setInt(-5);
  ASSERT_TRUE(f0->compare(f1));

  delete f0;

  ASSERT_EQ(f1->getInt(), -5);

  delete f1;
}

TEST(Unit_AST_Field, Real) {
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

  ASSERT_DEATH({ f0->getInt(); }, "");

  ASSERT_DEATH({ f0->setInt(0); }, "");

  ASSERT_DEATH({ f0->getString(); }, "");

  ASSERT_DEATH({ f0->setString(""); }, "");

  ASSERT_DEATH({ f0->getNode(); }, "");

  ASSERT_DEATH({ ((const Field *)f0)->getNode(); }, "");

  ASSERT_DEATH({ f0->setNode(nullptr); }, "");

  ASSERT_FALSE(f0->compare(f1));

  f1->setReal(-5.2);
  ASSERT_TRUE(f0->compare(f1));

  delete f0;

  ASSERT_EQ(f1->getReal(), -5.2);

  delete f1;
}

TEST(Unit_AST_Field, String) {
  Field *f0 = Field::createString("hello, world\n");

  ASSERT_NE(f0, nullptr);

  Field *f1 = f0->clone();

  ASSERT_NE(f1, nullptr);
  ASSERT_NE(f0, f1);

  ASSERT_EQ(f0->getKind(), Field::Kind::String);
  ASSERT_EQ(f1->getKind(), Field::Kind::String);

  ASSERT_TRUE(f0->getString().compare("hello, world\n"));
  ASSERT_TRUE(f1->getString().compare("hello, world\n"));

  f0->setString(StringContainer("hello, world\n", 5));

  ASSERT_TRUE(f0->getString().compare("hello"));
  ASSERT_TRUE(f1->getString().compare("hello, world\n"));

  ASSERT_DEATH({ f0->getInt(); }, "");

  ASSERT_DEATH({ f0->setInt(0); }, "");

  ASSERT_DEATH({ f0->getReal(); }, "");

  ASSERT_DEATH({ f0->setReal(0.0); }, "");

  ASSERT_DEATH({ f0->getNode(); }, "");

  ASSERT_DEATH({ ((const Field *)f0)->getNode(); }, "");

  ASSERT_DEATH({ f0->setNode(nullptr); }, "");

  ASSERT_FALSE(f0->compare(f1));

  f1->setString("hello");
  
  delete f0;

  ASSERT_TRUE(f1->getString().compare("hello"));

  delete f1;
}

TEST(Unit_AST_Field, Node) {
  Field *f0 = Field::createNode(nullptr);

  ASSERT_NE(f0, nullptr);

  Field *f1 = f0->clone();

  ASSERT_NE(f1, nullptr);
  ASSERT_NE(f0, f1);

  ASSERT_EQ(f0->getKind(), Field::Kind::Node);
  ASSERT_EQ(f1->getKind(), Field::Kind::Node);

  ASSERT_EQ(f0->getNode(), nullptr);
  ASSERT_EQ(f1->getNode(), nullptr);

  ASSERT_DEATH({ f0->getInt(); }, "");

  ASSERT_DEATH({ f0->setInt(0); }, "");

  ASSERT_DEATH({ f0->getReal(); }, "");

  ASSERT_DEATH({ f0->setReal(0.0); }, "");

  ASSERT_DEATH({ f0->getString(); }, "");

  ASSERT_DEATH({ f0->setString(""); }, "");

  ASSERT_TRUE(f0->compare(f1));

  delete f0;

  ASSERT_EQ(f1->getNode(), nullptr);

  delete f1;
}
