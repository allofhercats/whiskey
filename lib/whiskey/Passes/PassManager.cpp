#include <whiskey/Passes/PassManager.hpp>

#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/Passes/Pass.hpp>

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

void PassManager::addPass(std::unique_ptr<Pass> pass) {
  W_ASSERT_TRUE(pass, "Cannot add null pass.");

  for (const std::string &dep : pass->getDependencies()) {
    W_ASSERT_TRUE(hasPass(dep),
                  "Pass '" << pass->getName() << "' depends on missing pass '"
                           << dep << "'.");
  }

  passes.push_back(std::move(pass));
}

void PassManager::run(Node &node) {
  if (node.getType() == NodeType::None) {
    return;
  }

  for (auto &pass : passes) {
    pass->runPre(node);
  }

  for (FieldTag i : NodeTypeInfo::get(node.getType()).getFields()) {
    if (node.hasField(i)) {
      if (node.getField(i).getFormat() == FieldFormat::Node) {
        run(node.getField(i).as<FieldNode>().getValue());
      } else if (node.getField(i).getFormat() == FieldFormat::NodeVector) {
        for (Node &j : node.getField(i).as<FieldNodeVector>().getValue()) {
          run(j);
        }
      }
    }
  }

  for (auto &pass : passes) {
    pass->runPost(node);
  }
}
} // namespace whiskey
