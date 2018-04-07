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
#include <whiskey/AST/FieldInt.hpp>

using namespace whiskey;

TEST(Unit_AST_Field, Compare) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldUInt>(0);
  std::unique_ptr<Field> f1 = std::make_unique<FieldInt>(0);
  ASSERT_FALSE(*f0 == *f1);
  ASSERT_TRUE(*f0 != *f1);
}

TEST(Unit_AST_Field, As) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldUInt>(0);
  ASSERT_EQ(f0->as<FieldUInt>().getValue(), 0);
}
