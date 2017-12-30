#include "Module.inc"

#include <whiskey/CodeGen/Generator.hpp>

namespace whiskey {
void *Generator::onGenerateFunctionPointer(const Node *node) {
  W_ASSERT_UNREACHABLE("Functionality not implemented.");
}

void Generator::onGenerateObjectFile(const Node *node,
                                     const std::string &path) {
  W_ASSERT_UNREACHABLE("Functionality not implemented.");
}

Generator::Generator() {
}

Generator::~Generator() {
}

void *Generator::generateFunctionPointer(const Node *node) {
  W_ASSERT_NONNULL(node, "Cannot generate from null AST.");
  W_ASSERT_EQ(node->getKind(),
              Node::Kind::DeclFunction,
              "Cannot generate function pointer from non-function AST.");

  return onGenerateFunctionPointer(node);
}

void Generator::generateObjectFile(const Node *node, const std::string &path) {
  W_ASSERT_NONNULL(node, "Cannot generate from null AST.");

  onGenerateObjectFile(node, path);
}
} // namespace whiskey
