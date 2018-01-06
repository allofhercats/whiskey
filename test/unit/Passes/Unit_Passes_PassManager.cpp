#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/Passes/PassManager.hpp>

using namespace whiskey;

TEST(Unit_Passes_PassManager, Empty) {
  PassManager pm;

  ASSERT_FALSE(pm.hasPass("asdf"));

  Node *orig = Node::createDeclVariable(
      Node::createTypeAtomicInt32(),
      Field::createString8("x"),
      Node::createExprSymbol(Field::createString8("y")));

  Node *final = orig;

  pm.run(&final);

  ASSERT_EQ(final, orig);

  delete orig;
}
