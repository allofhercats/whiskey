#include <gtest/gtest.h>

#include <whiskey/AST/Field.hpp>
#include <whiskey/AST/Node.hpp>
#include <whiskey/CodeGen/Generator.hpp>
#include <whiskey/CodeGen/LLVMGenerator.hpp>

using namespace whiskey;

TEST(Integration_CodeGen_ObjectFile, Simple) {
  Node *node = Node::createDeclFunction(
      Node::createTypeAtomicInt32(),
      Field::createString8("f"),
      {},
      Node::createStmtBlock({Node::createStmtReturn(
          Node::createExprLiteralUInt(Node::createTypeAtomicInt32(), 0))}));

  LLVMGenerator gen;
  gen.generateObjectFile(node, "ThisIsATestObjectFile.o");
}
