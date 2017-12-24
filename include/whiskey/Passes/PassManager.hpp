#ifndef __WHISKEY_Passes_PassManager_HPP
#define __WHISKEY_Passes_PassManager_HPP

#include <whiskey/Passes/Module.inc>

#include <whiskey/Passes/Pass.hpp>

namespace whiskey {
class PassManager {
private:
	std::vector<std::unique_ptr<Pass>> passes;

	void runHelper(PassContext<AST> &ctx);

public:
	PassManager();
	PassManager(const PassManager &) = delete;

	bool hasPass(const std::string &name);
	void addPass(Pass *pass);

	void run(Container<AST> &ast);
};
}

#endif
