#include <whiskey/AST/PassGroup.hpp>

#include <whiskey/AST/Node.hpp>
#include <whiskey/AST/FieldNode.hpp>
#include <whiskey/AST/FieldNodeVector.hpp>
#include <whiskey/AST/Pass.hpp>
#include <whiskey/AST/PassManager.hpp>

namespace whiskey {
PassGroup::PassGroup() {
}

bool PassGroup::hasPass(const std::string &name) const {
  for (const std::unique_ptr<Pass> &pass : children) {
    if (pass->getName() == name) {
      return true;
    }
  }

  return false;
}

void PassGroup::addPass(const PassManager &mgr, std::unique_ptr<Pass> pass) {
  W_ASSERT_TRUE(pass, "Cannot add null pass.");

  for (const std::string &dep : pass->getDependencies()) {
    W_ASSERT_TRUE(mgr.hasPass(dep),
                  "Pass '" << pass->getName() << "' depends on missing pass '"
                           << dep << "'.");
  }

  children.push_back(std::move(pass));
}

PassResult PassGroup::run(Node &node, MessageContext &msgs) {
  if (node.getType() == NodeType::None) {
    return PassResult::Good;
  }

  bool isBlocked = false;

  for (auto &pass : children) {
    PassResult result = pass->runPre(node, msgs);
    if (result == PassResult::Block) {
      isBlocked = true;
    } else if (result == PassResult::Halt) {
      return PassResult::Halt;
    }
  }

  if (isBlocked) {
    return PassResult::Good;
  }

  for (FieldTag i : NodeTypeInfo::get(node.getType()).getFields()) {
    if (node.hasField(i)) {
      if (node.getField(i).getFormat() == FieldFormat::Node) {
        PassResult result = run(node.getField(i).as<FieldNode>().getValue(), msgs);
        if (result == PassResult::Block) {
          isBlocked = true;
        } else if (result == PassResult::Halt) {
          return PassResult::Halt;
        }
      } else if (node.getField(i).getFormat() == FieldFormat::NodeVector) {
        for (Node &j : node.getField(i).as<FieldNodeVector>().getValue()) {
          PassResult result = run(j, msgs);
          if (result == PassResult::Block) {
            isBlocked = true;
          } else if (result == PassResult::Halt) {
            return PassResult::Halt;
          }
        }
      }

      if (isBlocked) {
        return PassResult::Good;
      }
    }
  }

  for (auto &pass : children) {
    PassResult result = pass->runPost(node, msgs);
    if (result == PassResult::Halt) {
      return PassResult::Halt;
    }
  }

  return PassResult::Good;
}
} // namespace whiskey
