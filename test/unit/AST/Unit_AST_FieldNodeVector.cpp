#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>

using namespace whiskey;

TEST(Unit_AST_FieldNodeVector, Format) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldNodeVector>();
  ASSERT_EQ(f0->getFormat(), FieldFormat::NodeVector);
}

TEST(Unit_AST_FieldNodeVector, Value) {
  std::unique_ptr<FieldNodeVector> f0 = std::make_unique<FieldNodeVector>();
  ASSERT_EQ(f0->getValue().size(), 0);
  std::vector<Node> tmp = {
    Node(NodeType::TypeAtomicInt8)
  };
  f0->getValue() = tmp;
  ASSERT_EQ(f0->getValue().size(), 1);
}

TEST(Unit_AST_FieldNodeVector, ValueFromField) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldNodeVector>();
  ASSERT_EQ(f0->getNodeVector().size(), 0);
  std::vector<Node> tmp = {
    Node(NodeType::TypeAtomicInt8)
  };
  static_cast<FieldNodeVector &>(*f0).getValue() = tmp;
  ASSERT_EQ(f0->getNodeVector().size(), 1);
}

TEST(Unit_AST_FieldNodeVector, Compare) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldNodeVector>();
  std::vector<Node> tmp = {
    Node(NodeType::TypeAtomicInt8)
  };
  std::unique_ptr<Field> f1 = std::make_unique<FieldNodeVector>(tmp);
  ASSERT_TRUE(*f0 == *f0);
  ASSERT_TRUE(*f1 == *f1);
  ASSERT_FALSE(*f0 == *f1);
  ASSERT_FALSE(*f0 != *f0);
  ASSERT_FALSE(*f1 != *f1);
  ASSERT_TRUE(*f0 != *f1);
}
