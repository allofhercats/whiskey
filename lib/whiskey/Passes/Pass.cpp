#include <whiskey/Passes/Pass.hpp>

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

void Pass::runPre(Node &node) {
  return onRunPre(node);
}

void Pass::runPost(Node &node) {
  return onRunPost(node);
}
} // namespace whiskey
