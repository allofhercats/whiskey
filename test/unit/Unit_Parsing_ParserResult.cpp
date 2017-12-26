#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Unit_Parsing_ParserResult, Empty) {
	ParserResult res;

	ASSERT_FALSE(res.isGood());
}

TEST(Unit_Parsing_ParserResult, Filled) {
	ParserResult res(new TypeAtomic(AST::ID::TypeAtomicBool, Range()));

	ASSERT_TRUE(res.isGood());
}
