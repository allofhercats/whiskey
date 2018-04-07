#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/FieldString.hpp>

using namespace whiskey;

TEST(Unit_AST_FieldString, Format) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldString>("");
  ASSERT_EQ(f0->getFormat(), FieldFormat::String);
}

TEST(Unit_AST_FieldString, Value) {
  std::unique_ptr<FieldString> f0 = std::make_unique<FieldString>("");
  ASSERT_STREQ(f0->getValue().c_str(), "");
  f0->setValue("hi");
  ASSERT_STREQ(f0->getValue().c_str(), "hi");
  f0->setValue("bye");
  ASSERT_STREQ(f0->getValue().c_str(), "bye");
}

TEST(Unit_AST_FieldString, ValueFromField) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldString>("");
  ASSERT_STREQ(f0->getString().c_str(), "");
  static_cast<FieldString &>(*f0).setValue("hi");
  ASSERT_STREQ(f0->getString().c_str(), "hi");
  static_cast<FieldString &>(*f0).setValue("bye");
  ASSERT_STREQ(f0->getString().c_str(), "bye");
}

TEST(Unit_AST_FieldString, Compare) {
  std::unique_ptr<Field> f0 = std::make_unique<FieldString>("");
  std::unique_ptr<Field> f1 = std::make_unique<FieldString>("hi");
  std::unique_ptr<Field> f2 = std::make_unique<FieldString>("bye");
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
