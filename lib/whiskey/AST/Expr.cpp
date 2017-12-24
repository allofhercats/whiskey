#include "Module.inc"

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
bool Expr::onCompare(const AST &other) const {
	const Expr &casted = static_cast<const Expr &>(other);

	if (!onCompareExpr(casted)) {
		return false;
	}

	return true;
}

void Expr::onGetChildren(std::queue<ContainerRef<AST>> &children) {
	onGetChildrenExpr(children);
}

Expr::Expr(AST::ID id, Range range) : AST(id, range) {}
}
