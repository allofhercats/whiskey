#include <gtest/gtest.h>

#include <whiskey/Whiskey.hpp>

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
