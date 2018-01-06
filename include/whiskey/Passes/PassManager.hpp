#ifndef __WHISKEY_Passes_PassManager_HPP
#define __WHISKEY_Passes_PassManager_HPP

#include <vector>
#include <memory>

#include <whiskey/Passes/Pass.hpp>

namespace whiskey {
class Node;

class PassManager {
private:
  std::vector<std::unique_ptr<Pass>> passes;

public:
  PassManager();
  PassManager(const PassManager &) = delete;

  bool hasPass(const std::string &name);
  void addPass(Pass *pass);

  void run(Node **node);
};
} // namespace whiskey

#endif
