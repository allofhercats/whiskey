#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/Node.hpp>

using namespace whiskey;

TEST(Unit_AST_Node, StmtEmpty_0) {
  Node n0(NodeType::StmtEmpty);
  Node n1 = n0;

  ASSERT_EQ(n0.getType(), NodeType::StmtEmpty);
  ASSERT_EQ(n1.getType(), NodeType::StmtEmpty);

  ASSERT_EQ(NodeTypeInfo::get(n0.getType()).getFields().size(), 0);
  ASSERT_EQ(NodeTypeInfo::get(n1.getType()).getFields().size(), 0);

  ASSERT_TRUE(n0 == n1);
}
