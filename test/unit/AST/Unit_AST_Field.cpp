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

TEST(Unit_AST_Field, Int) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldInt>(5);

  ASSERT_TRUE(f0);

  std::unique_ptr<Field> f1 = std::make_unique<FieldInt>(static_cast<FieldInt &>(*f0));

  ASSERT_TRUE(f1);

  ASSERT_EQ(f0->getFormat(), FieldFormat::Int);
  ASSERT_EQ(f1->getFormat(), FieldFormat::Int);

  ASSERT_EQ(static_cast<FieldInt &>(*f0).getValue(), 5);
  ASSERT_EQ(static_cast<FieldInt &>(*f1).getValue(), 5);

  static_cast<FieldInt &>(*f0).setValue(-5);

  ASSERT_EQ(static_cast<FieldInt &>(*f0).getValue(), -5);
  ASSERT_EQ(static_cast<FieldInt &>(*f1).getValue(), 5);

  ASSERT_FALSE(*f0 == *f1);

  static_cast<FieldInt &>(*f1).setValue(-5);
  ASSERT_TRUE(*f0 == *f1);
}
