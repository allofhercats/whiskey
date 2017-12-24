#include "Module.inc"

#include <whiskey/Passes/PassManager.hpp>

namespace whiskey {
void PassManager::runHelper(PassContext<AST> &ctx) {
	for (const std::unique_ptr<Pass> &pass : passes) {
		PassContext<AST> ctxTmp;
		if (ctx.getReplacement()) {
			ctxTmp = PassContext<AST>(ctx.getParent(), ctx.getReplacement());
		} else {
			ctxTmp = PassContext<AST>(ctx.getParent(), ctx.getOriginal());
		}
		pass->run(ctxTmp);
		if (ctxTmp.getReplacement()) {
			ctx.setReplacement(ctxTmp.getReplacement());
		}
	}

	std::queue<ContainerRef<AST>> children;
	if (ctx.getReplacement()) {
		children = ctx.getReplacement()->getChildren();
	} else {
		children = ctx.getOriginal()->getChildren();
	}

	while (!children.empty()) {
		PassContext<AST> ctxTmp(ctx.getParent(), children.front());
		runHelper(ctxTmp);
		if (ctxTmp.getReplacement()) {
			ctx.setReplacement(ctxTmp.getReplacement());
		}
		children.pop();
	}

	for (const std::unique_ptr<Pass> &pass : passes) {
		PassContext<AST> ctxTmp;
		if (ctx.getReplacement()) {
			ctxTmp = PassContext<AST>(ctx.getParent(), ctx.getReplacement());
		} else {
			ctxTmp = PassContext<AST>(ctx.getParent(), ctx.getOriginal());
		}
		pass->runPost(ctx);
		if (ctxTmp.getReplacement()) {
			ctx.setReplacement(ctxTmp.getReplacement());
		}
	}
}

PassManager::PassManager() {}

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
		W_ASSERT_TRUE(hasPass(dep), "Pass '" << pass->getName() << "' depends on missing pass '" << dep << "'.");
	}

	passes.push_back(std::unique_ptr<Pass>(pass));
}

void PassManager::run(Container<AST> &ast) {
	PassContext<AST> ctx(nullptr, ast);

	runHelper(ctx);

	if (ctx.getReplacement()) {
		ast = ctx.getReplacement();
	}
}
}
