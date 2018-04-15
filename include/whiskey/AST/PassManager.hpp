#ifndef __WHISKEY_AST_PassManager_HPP
#define __WHISKEY_AST_PassManager_HPP

#include <memory>
#include <vector>

#include <whiskey/AST/PassResult.hpp>

namespace whiskey {
class Node;
class Pass;
class PassGroup;
class MessageContext;

class PassManager {
private:
	std::vector<std::unique_ptr<PassGroup>> children;

public:
	PassManager();
	PassManager(const PassManager &) = delete;

	bool hasPass(const std::string &name) const;
	void addGroup();
	void addPass(std::unique_ptr<Pass> pass);

	PassResult run(Node &node, MessageContext &msgs);
};
}

#endif
