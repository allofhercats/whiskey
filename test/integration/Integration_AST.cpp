#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Integration_AST, Single) {
  Field *f0 = Field::createNode(nullptr);
  Field *f1 = f0->clone();

  ASSERT_EQ(f0->getKind(), Field::Kind::Node);
  ASSERT_EQ(f1->getKind(), Field::Kind::Node);

  ASSERT_DEATH({ f0->getInt(); }, "");

  ASSERT_DEATH({ f0->setInt(0); }, "");

  ASSERT_DEATH({ f0->getUInt(); }, "");

  ASSERT_DEATH({ f0->setUInt(0); }, "");

  ASSERT_DEATH({ f0->getReal(); }, "");

  ASSERT_DEATH({ f0->setReal(0.0); }, "");

  ASSERT_DEATH({ f0->getString8(); }, "");

  ASSERT_DEATH({ f0->setString8(""); }, "");

  ASSERT_DEATH({ f0->getString16(); }, "");

  ASSERT_DEATH({ f0->setString16(u""); }, "");

  ASSERT_DEATH({ f0->getString32(); }, "");

  ASSERT_DEATH({ f0->setString32(U""); }, "");

  ASSERT_EQ(f0->getLength(), 0);
  ASSERT_EQ(f1->getLength(), 0);

  ASSERT_EQ(f0->getNode(), nullptr);
  ASSERT_EQ(f1->getNode(), nullptr);

  ASSERT_TRUE(f0->compare(f1));

  ASSERT_DEATH({ f0->printLiteral(std::cout); }, "");

  f0->setNode(Node::createTypeAtomicInt32());

  ASSERT_NE(f0->getNode(), nullptr);
  ASSERT_EQ(f1->getNode(), nullptr);

  ASSERT_FALSE(f0->compare(f1));

  Field *f2 = f0->clone();

  ASSERT_EQ(f2->getKind(), Field::Kind::Node);

  ASSERT_NE(f0->getNode(), nullptr);
  ASSERT_NE(f2->getNode(), nullptr);
  ASSERT_NE(f0->getNode(), f2->getNode());

  ASSERT_TRUE(f0->compare(f2));

  f1->setNode(Node::createTypeAtomicInt64());

  ASSERT_FALSE(f0->compare(f1));
  ASSERT_FALSE(f2->compare(f1));

  delete f0;
  delete f1;
  delete f2;
}
