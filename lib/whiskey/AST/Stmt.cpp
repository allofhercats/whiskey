#include "Module.inc"

#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
bool Stmt::onCompare(const AST &other) const {
	const Stmt &casted = static_cast<const Stmt &>(other);

	if (!onCompareStmt(casted)) {
		return false;
	}

	return true;
}

void Stmt::onGetChildren(std::queue<ContainerRef<AST>> &children) {
	onGetChildrenStmt(children);
}

Stmt::Stmt(AST::ID id, Range range) : AST(id, range) {}
}
