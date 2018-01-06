#include <gtest/gtest.h>

// #include <whiskey/Whiskey.hpp>

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/CodeGen/Generator.hpp>
#include <whiskey/CodeGen/LLVMGenerator.hpp>

using namespace whiskey;

TEST(Integration_CodeGen_JIT, ReturnZero) {
  Node *node = Node::createDeclFunction(
      Node::createTypeAtomicInt32(),
      Field::createString8("f"),
      {},
      Node::createStmtBlock({Node::createStmtReturn(
          Node::createExprLiteralUInt(Node::createTypeAtomicInt32(), 0))}));

  LLVMGenerator gen;
  int (*f)() = (int (*)())gen.generateFunctionPointer(node);

  ASSERT_NE(f, nullptr);

  int r = f();

  ASSERT_EQ(r, 0);
}

TEST(Integration_CodeGen_JIT, ReturnFive) {
  Node *node = Node::createDeclFunction(
      Node::createTypeAtomicInt32(),
      Field::createString8("f"),
      {},
      Node::createStmtBlock({Node::createStmtReturn(
          Node::createExprLiteralUInt(Node::createTypeAtomicInt32(), 5))}));

  LLVMGenerator gen;
  int (*f)() = (int (*)())gen.generateFunctionPointer(node);

  ASSERT_NE(f, nullptr);

  int r = f();

  ASSERT_EQ(r, 5);
}
