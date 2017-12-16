#include "Module.inc"

#include <whiskey/AST/StmtWhile.hpp>

namespace whiskey {
AST *StmtWhile::onClone() const {
	return new StmtWhile(getRange(), condition, bodyClause);
}

bool StmtWhile::onCompare(const AST &other) const {
	const StmtWhile &casted = static_cast<const StmtWhile &>(other);

	if (!AST::compare(condition, casted.condition)) {
		return false;
	}

	if (!AST::compare(bodyClause, casted.bodyClause)) {
		return false;
	}

	if (!onCompareStmtWhile(casted)) {
		return false;
	}

	return true;
}

bool StmtWhile::onCompareStmtWhile(const StmtWhile &other) const {
	return true;
}

StmtWhile::StmtWhile(Container<Expr> condition, Container<Stmt> bodyClause) : Stmt(AST::ID::StmtWhile, Range()), condition(condition), bodyClause(bodyClause) {}

StmtWhile::StmtWhile(Range range, Container<Expr> condition, Container<Stmt> bodyClause) : Stmt(AST::ID::StmtWhile, range), condition(condition), bodyClause(bodyClause) {}

Ref<Expr> StmtWhile::getCondition() {
	return condition;
}

CRef<Expr> StmtWhile::getCondition() const {
	return condition;
}

void StmtWhile::setCondition(Container<Expr> value) {
	condition = value;
}

Ref<Stmt> StmtWhile::getBodyClause() {
	return bodyClause;
}

CRef<Stmt> StmtWhile::getBodyClause() const {
	return bodyClause;
}

void StmtWhile::setBodyClause(Container<Stmt> value) {
	bodyClause = value;
}
}
