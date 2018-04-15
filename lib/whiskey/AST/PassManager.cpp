#include <whiskey/AST/PassManager.hpp>

#include <whiskey/AST/PassGroup.hpp>

namespace whiskey {
PassManager::PassManager() {}

bool PassManager::hasPass(const std::string &name) const {
  for (const std::unique_ptr<PassGroup> &child : children) {
    if (child->hasPass(name)) {
      return true;
    }
  }

  return false;
}

void PassManager::addGroup() {
	children.push_back(std::make_unique<PassGroup>());
}

void PassManager::addPass(std::unique_ptr<Pass> pass) {
	children.back()->addPass(*this, std::move(pass));
}

PassResult PassManager::run(Node &node, MessageContext &msgs) {
	for (const std::unique_ptr<PassGroup> &child : children) {
		PassResult result = child->run(node, msgs);
		if (result == PassResult::Block) {
			return PassResult::Good;
		} else if (result == PassResult::Halt) {
			return PassResult::Halt;
		}
	}

	return PassResult::Good;
}
}
