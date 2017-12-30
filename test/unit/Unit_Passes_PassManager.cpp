#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Unit_Passes_PassManager, Empty) {
	PassManager pm;

	ASSERT_FALSE(pm.hasPass("asdf"));

	Node *orig = Node::createDeclVariable(
		Node::createTypeAtomicInt32(),
		Field::createString8("x"),
		Node::createExprSymbol(Field::createString8("y"))
	);

	Node *final = orig;

	pm.run(&final);

	ASSERT_EQ(final, orig);

	delete orig;
}
