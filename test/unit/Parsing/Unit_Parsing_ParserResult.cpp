#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Node.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserResult, Empty) {
  ParserResult res;

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserResult, Filled) {
  ParserResult res = ParserResult(Node());

  ASSERT_TRUE(res.isGood());
}
