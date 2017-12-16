#include "Module.inc"

#include <whiskey/AST/StmtExpr.hpp>

namespace whiskey {
AST *StmtExpr::onClone() const {
	return new StmtExpr(getID(), getRange(), value);
}

bool StmtExpr::onCompare(const AST &other) const {
	const StmtExpr &casted = static_cast<const StmtExpr &>(other);

	if (!AST::compare(value, casted.value)) {
		return false;
	}

	if (!onCompareStmtExpr(casted)) {
		return false;
	}

	return true;
}

bool StmtExpr::onCompareStmtExpr(const StmtExpr &other) const {
	return true;
}

StmtExpr::StmtExpr(AST::ID id, Container<Expr> value) : Stmt(id, Range()), value(value) {}

StmtExpr::StmtExpr(AST::ID id, Range range, Container<Expr> value) : Stmt(id, range), value(value) {}

Ref<Expr> StmtExpr::getValue() {
	return value;
}

CRef<Expr> StmtExpr::getValue() const {
	return value;
}

void StmtExpr::setValue(Container<Expr> value) {
	this->value = value;
}
}
