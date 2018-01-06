#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/AST/Node.hpp>
#include <whiskey/Parsing/ParserResult.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserResult, Empty) {
  ParserResult res;

  ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserResult, Filled) {
  ParserResult res(Node::createTypeAtomicInt32());

  ASSERT_TRUE(res.isGood());
}
