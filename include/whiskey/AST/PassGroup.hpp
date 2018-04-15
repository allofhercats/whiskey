#ifndef __WHISKEY_AST_PassGroup_HPP
#define __WHISKEY_AST_PassGroup_HPP

#include <memory>
#include <vector>

#include <whiskey/AST/Pass.hpp>

namespace whiskey {
class Node;
class PassManager;

class PassGroup {
private:
  std::vector<std::unique_ptr<Pass>> children;

public:
  PassGroup();
  PassGroup(const PassGroup &) = delete;

  bool hasPass(const std::string &name) const;
  void addPass(const PassManager &mgr, std::unique_ptr<Pass> pass);

  PassResult run(Node &node, MessageContext &msgs);
};
} // namespace whiskey

#endif
