#include <gtest/gtest.h>

#include <whiskey/Passes/Pass.hpp>
#include <whiskey/Passes/PassManager.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/Field.hpp>

using namespace whiskey;

class Echo : public Pass {
protected:
  Node *onRunPre(Node *node) {
    return node;
  }

  Node *onRunPost(Node *node) {
    return nullptr;
  }

public:
  Echo() : Pass("echo") {
  }
};

TEST(Integration_Passes, Echo) {
  PassManager pm;
  pm.addPass(new Echo());

  ASSERT_TRUE(pm.hasPass("echo"));

  Node *orig = Node::createDeclVariable(
      Node::createTypeAtomicInt32(),
      Field::createString8("x"),
      Node::createExprSymbol(Field::createString8("y")));

  Node *final = orig;

  pm.run(&final);

  ASSERT_EQ(final, orig);

  delete orig;
}

class Clone : public Pass {
protected:
  Node *onRunPre(Node *node) {
    return node->clone();
  }

  Node *onRunPost(Node *node) {
    return node->clone();
  }

public:
  Clone() : Pass("clone") {
  }
};

TEST(Integration_Passes, Clone) {
  PassManager pm;
  pm.addPass(new Clone());

  ASSERT_TRUE(pm.hasPass("clone"));
  ASSERT_FALSE(pm.hasPass("echo"));

  Node *orig = Node::createDeclVariable(
      Node::createTypeAtomicInt32(),
      Field::createString8("x"),
      Node::createExprSymbol(Field::createString8("y")));

  Node *final = orig;

  pm.run(&final);

  ASSERT_NE(final, orig);
  ASSERT_TRUE(orig->compare(final));

  delete orig;
  delete final;
}
