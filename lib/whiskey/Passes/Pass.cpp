#include <whiskey/Passes/Pass.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
Pass::Pass(std::string name, std::initializer_list<std::string> dependencies)
    : name(name), dependencies(dependencies) {
  W_ASSERT_GT(name.size(), 0, "Cannot have pass with empty name.");
}

Pass::~Pass() {
}

const std::string &Pass::getName() const {
  return name;
}

const std::vector<std::string> &Pass::getDependencies() const {
  return dependencies;
}

Node *Pass::runPre(Node *node) {
  return onRunPre(node);
}

Node *Pass::runPost(Node *node) {
  return onRunPost(node);
}
} // namespace whiskey
