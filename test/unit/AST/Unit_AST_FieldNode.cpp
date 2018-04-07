#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldNode.hpp>

using namespace whiskey;

TEST(Unit_AST_FieldNode, Format) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldNode>(Node());
  ASSERT_EQ(f0->getFormat(), FieldFormat::Node);
}

TEST(Unit_AST_FieldNode, Value) {
  std::unique_ptr<FieldNode> f0 = std::make_unique<FieldNode>(Node());
  ASSERT_TRUE(f0->getValue() == Node());
  f0->setValue(Node(NodeType::TypeAtomicInt8));
  ASSERT_TRUE(f0->getValue() == Node(NodeType::TypeAtomicInt8));
  f0->setValue(Node(NodeType::TypeAtomicInt16));
  ASSERT_TRUE(f0->getValue() == Node(NodeType::TypeAtomicInt16));
}

TEST(Unit_AST_FieldNode, ValueFromField) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldNode>(Node());
  ASSERT_TRUE(f0->getNode() == Node());
  static_cast<FieldNode &>(*f0).setValue(Node(NodeType::TypeAtomicInt8));
  ASSERT_TRUE(f0->getNode() == Node(NodeType::TypeAtomicInt8));
  static_cast<FieldNode &>(*f0).setValue(Node(NodeType::TypeAtomicInt16));
  ASSERT_TRUE(f0->getNode() == Node(NodeType::TypeAtomicInt16));
}

TEST(Unit_AST_FieldNode, Compare) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldNode>(Node());
  std::unique_ptr<Field> f1 = std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt8));
  std::unique_ptr<Field> f2 = std::make_unique<FieldNode>(Node(NodeType::TypeAtomicInt16));
  ASSERT_TRUE(*f0 == *f0);
  ASSERT_TRUE(*f1 == *f1);
  ASSERT_FALSE(*f0 == *f1);
  ASSERT_FALSE(*f0 != *f0);
  ASSERT_FALSE(*f1 != *f1);
  ASSERT_TRUE(*f0 != *f1);
  ASSERT_TRUE(*f0 == *f0);
  ASSERT_TRUE(*f2 == *f2);
  ASSERT_FALSE(*f0 == *f2);
  ASSERT_FALSE(*f0 != *f0);
  ASSERT_FALSE(*f2 != *f2);
  ASSERT_TRUE(*f0 != *f2);
  ASSERT_TRUE(*f1 == *f1);
  ASSERT_TRUE(*f2 == *f2);
  ASSERT_FALSE(*f1 == *f2);
  ASSERT_FALSE(*f1 != *f1);
  ASSERT_FALSE(*f2 != *f2);
  ASSERT_TRUE(*f1 != *f2);
}
