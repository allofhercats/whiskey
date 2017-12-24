#include "Module.inc"

#include <whiskey/AST/StmtEmpty.hpp>

namespace whiskey {
AST *StmtEmpty::onClone() const {
	return new StmtEmpty(getRange());
}

bool StmtEmpty::onCompareStmt(const Stmt &other) const {
	const StmtEmpty &casted = static_cast<const StmtEmpty &>(other);

	if (!onCompareStmtEmpty(casted)) {
		return false;
	}

	return true;
}

void StmtEmpty::onGetChildrenStmt(std::queue<ContainerRef<AST>> &children) {
	onGetChildrenStmtEmpty(children);
}

bool StmtEmpty::onCompareStmtEmpty(const StmtEmpty &other) const {
	return true;
}

void StmtEmpty::onGetChildrenStmtEmpty(std::queue<ContainerRef<AST>> &children) {}

StmtEmpty::StmtEmpty(Range range) : Stmt(AST::ID::StmtEmpty, range) {}
}
