#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldUInt.hpp>

using namespace whiskey;

TEST(Unit_AST_FieldUInt, Format) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldUInt>(0);
  ASSERT_EQ(f0->getFormat(), FieldFormat::UInt);
}

TEST(Unit_AST_FieldUInt, Value) {
  std::unique_ptr<FieldUInt> f0 = std::make_unique<FieldUInt>(0);
  ASSERT_EQ(f0->getValue(), 0);
  f0->setValue(5);
  ASSERT_EQ(f0->getValue(), 5);
}

TEST(Unit_AST_FieldUInt, ValueFromField) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldUInt>(0);
  ASSERT_EQ(f0->getUInt(), 0);
  static_cast<FieldUInt &>(*f0).setValue(5);
  ASSERT_EQ(f0->getUInt(), 5);
}

TEST(Unit_AST_FieldUInt, Compare) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldUInt>(0);
  std::unique_ptr<Field> f1 = std::make_unique<FieldUInt>(5);
  ASSERT_TRUE(*f0 == *f0);
  ASSERT_TRUE(*f1 == *f1);
  ASSERT_FALSE(*f0 == *f1);
  ASSERT_FALSE(*f0 != *f0);
  ASSERT_FALSE(*f1 != *f1);
  ASSERT_TRUE(*f0 != *f1);
}
