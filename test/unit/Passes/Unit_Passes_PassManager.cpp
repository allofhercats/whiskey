#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#include <gtest/gtest.h>
#pragma clang diagnostic pop
#pragma clang diagnostic ignored "-Wcovered-switch-default"

#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/Passes/PassManager.hpp>

using namespace whiskey;

TEST(Unit_Passes_PassManager, Empty) {
  PassManager pm;

  ASSERT_FALSE(pm.hasPass("asdf"));

  Node orig(NodeType::ExprCall);
  orig.setField(FieldTag::ExprCall_Callee, std::make_unique<FieldNode>(Node(NodeType::ExprSymbol)));
  orig.setField(FieldTag::ExprCall_Args, std::make_unique<FieldNodeVector>());
  orig.getField(FieldTag::ExprCall_Args).as<FieldNodeVector>().getValue().push_back(Node(NodeType::ExprSymbol));
  orig.getField(FieldTag::ExprCall_Args).as<FieldNodeVector>().getValue().push_back(Node(NodeType::ExprSymbol));

  Node final = orig;

  pm.run(final);

  ASSERT_EQ(final, orig);
}
