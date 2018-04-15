#include <whiskey/AST/Pass.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
Pass::Pass(std::string name, std::initializer_list<std::string> dependencies)
    : name(name), dependencies(dependencies) {
  W_ASSERT_GT(name.size(), 0u, "Cannot have pass with empty name.");
}

Pass::~Pass() {
}

const std::string &Pass::getName() const {
  return name;
}

const std::vector<std::string> &Pass::getDependencies() const {
  return dependencies;
}

PassResult Pass::runPre(Node &node, MessageContext &msgs) {
  return onRunPre(node, msgs);
}

PassResult Pass::runPost(Node &node, MessageContext &msgs) {
  return onRunPost(node, msgs);
}
} // namespace whiskey
