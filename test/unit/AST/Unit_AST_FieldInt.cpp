#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldInt.hpp>

using namespace whiskey;

TEST(Unit_AST_FieldInt, Format) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldInt>(0);
  ASSERT_EQ(f0->getFormat(), FieldFormat::Int);
}

TEST(Unit_AST_FieldInt, Value) {
  std::unique_ptr<FieldInt> f0 = std::make_unique<FieldInt>(0);
  ASSERT_EQ(f0->getValue(), 0);
  f0->setValue(5);
  ASSERT_EQ(f0->getValue(), 5);
  f0->setValue(-5);
  ASSERT_EQ(f0->getValue(), -5);
}

TEST(Unit_AST_FieldInt, ValueFromField) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldInt>(0);
  ASSERT_EQ(f0->getInt(), 0);
  static_cast<FieldInt &>(*f0).setValue(5);
  ASSERT_EQ(f0->getInt(), 5);
  static_cast<FieldInt &>(*f0).setValue(-5);
  ASSERT_EQ(f0->getInt(), -5);
}

TEST(Unit_AST_FieldInt, Compare) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldInt>(0);
  std::unique_ptr<Field> f1 = std::make_unique<FieldInt>(5);
  std::unique_ptr<Field> f2 = std::make_unique<FieldInt>(-5);
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
