#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

using namespace whiskey;

TEST(Unit_AST2_Node, StmtFor_0) {
	Node *n0 = Node::createStmtEmpty();
	Node *n1 = n0->clone();

	ASSERT_EQ(n0->getKind(), Node::Kind::StmtEmpty);
	ASSERT_EQ(n1->getKind(), Node::Kind::StmtEmpty);

	ASSERT_EQ(Node::getKindInfo(n0->getKind()).getNFields(), 0);
	ASSERT_EQ(Node::getKindInfo(n1->getKind()).getNFields(), 0);

	ASSERT_EQ(n0->getNext(), nullptr);
	ASSERT_EQ(n1->getNext(), nullptr);

	ASSERT_TRUE(n0->compare(n1));
}
