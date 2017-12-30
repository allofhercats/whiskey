#include "Module.inc"

#include <whiskey/Passes/PassManager.hpp>

namespace whiskey {
PassManager::PassManager() {
}

bool PassManager::hasPass(const std::string &name) {
  for (const std::unique_ptr<Pass> &pass : passes) {
    if (pass->getName() == name) {
      return true;
    }
  }

  return false;
}

void PassManager::addPass(Pass *pass) {
  W_ASSERT_NONNULL(pass, "Cannot add null pass.");

  for (const std::string &dep : pass->getDependencies()) {
    W_ASSERT_TRUE(hasPass(dep),
                  "Pass '" << pass->getName() << "' depends on missing pass '"
                           << dep << "'.");
  }

  passes.push_back(std::unique_ptr<Pass>(pass));
}

void PassManager::run(Node **node) {
  W_ASSERT_NONNULL(node, "Cannot run pass manager on null node reference.");

  if (*node == nullptr) {
    return;
  }

  for (auto &pass : passes) {
    Node *res = pass->runPre(*node);
    if (res != nullptr && res != *node) {
      // delete *node;
      *node = res;
    }
  }

  for (int i = 0; i < Node::getKindInfo((*node)->getKind()).getNFields(); i++) {
    if ((*node)->getField(i)->getKind() == Field::Kind::Node) {
      Node *orig = (*node)->getField(i)->getNode();
      Node *final = orig;
      if (final != nullptr) {
        run(&final);
      }
      if (final != nullptr && final != orig) {
        delete orig;
        (*node)->getField(i)->setNode(final);
      }
    }
  }

  for (auto &pass : passes) {
    Node *res = pass->runPost(*node);
    if (res != nullptr && res != *node) {
      // delete node;
      *node = res;
    }
  }
}
} // namespace whiskey
