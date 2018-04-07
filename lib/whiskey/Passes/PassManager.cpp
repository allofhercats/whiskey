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

bool PassManager::run(Node &node, MessageContext &msgs) {
  if (node.getType() == NodeType::None) {
    return true;
  }

  for (auto &pass : passes) {
    if (!pass->runPre(node, msgs)) {
      return false;
    }
  }

  for (FieldTag i : NodeTypeInfo::get(node.getType()).getFields()) {
    if (node.hasField(i)) {
      if (node.getField(i).getFormat() == FieldFormat::Node) {
        if (!run(node.getField(i).as<FieldNode>().getValue(), msgs)) {
          return false;
        }
      } else if (node.getField(i).getFormat() == FieldFormat::NodeVector) {
        for (Node &j : node.getField(i).as<FieldNodeVector>().getValue()) {
          if (!run(j, msgs)) {
            return false;
          }
        }
      }
    }
  }

  for (auto &pass : passes) {
    if (!pass->runPost(node, msgs)) {
      return false;
    }
  }

  return true;
}
} // namespace whiskey
