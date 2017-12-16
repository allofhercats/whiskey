#include "Module.inc"

#include <whiskey/AST/StmtIf.hpp>

namespace whiskey {
AST *StmtIf::onClone() const {
	return new StmtIf(getRange(), condition, thenClause, elseClause);
}

bool StmtIf::onCompare(const AST &other) const {
	const StmtIf &casted = static_cast<const StmtIf &>(other);

	if (!AST::compare(condition, casted.condition)) {
		return false;
	}

	if (!AST::compare(thenClause, casted.thenClause)) {
		return false;
	}

	if (!AST::compare(elseClause, casted.elseClause)) {
		return false;
	}

	if (!onCompareStmtIf(casted)) {
		return false;
	}

	return true;
}

bool StmtIf::onCompareStmtIf(const StmtIf &other) const {
	return true;
}

StmtIf::StmtIf(Container<Expr> condition, Container<Stmt> thenClause, Container<Stmt> elseClause) : Stmt(AST::ID::StmtIf, Range()), condition(condition), thenClause(thenClause), elseClause(elseClause) {}

StmtIf::StmtIf(Range range, Container<Expr> condition, Container<Stmt> thenClause, Container<Stmt> elseClause) : Stmt(AST::ID::StmtIf, range), condition(condition), thenClause(thenClause), elseClause(elseClause) {}

Ref<Expr> StmtIf::getCondition() {
	return condition;
}

CRef<Expr> StmtIf::getCondition() const {
	return condition;
}

void StmtIf::setCondition(Container<Expr> value) {
	condition = value;
}

Ref<Stmt> StmtIf::getThenClause() {
	return thenClause;
}

CRef<Stmt> StmtIf::getThenClause() const {
	return thenClause;
}

void StmtIf::setThenClause(Container<Stmt> value) {
	thenClause = value;
}

Ref<Stmt> StmtIf::getElseClause() {
	return elseClause;
}

CRef<Stmt> StmtIf::getElseClause() const {
	return elseClause;
}

void StmtIf::setElseClause(Container<Stmt> value) {
	elseClause = value;
}
}
