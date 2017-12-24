#include "Module.inc"

#include <whiskey/AST/DeclVariable.hpp>

#include <whiskey/AST/StmtFor.hpp>

namespace whiskey {
AST *StmtFor::onClone() const {
	return new StmtFor(getRange(), decls, condition, steps, bodyClause);
}

bool StmtFor::onCompareStmt(const Stmt &other) const {
	const StmtFor &casted = static_cast<const StmtFor &>(other);

	if (!AST::compare(decls, casted.decls)) {
		return false;
	}

	if (!AST::compare(condition, casted.condition)) {
		return false;
	}

	if (!AST::compare(steps, casted.steps)) {
		return false;
	}

	if (!AST::compare(bodyClause, casted.bodyClause)) {
		return false;
	}

	if (!onCompareStmtFor(casted)) {
		return false;
	}

	return true;
}

void StmtFor::onGetChildrenStmt(std::queue<ContainerRef<AST>> &children) {
	for (Container<Decl> &i : decls) {
		children.push(ContainerRef<AST>(i));
	}
	children.push(ContainerRef<AST>(condition));
	for (Container<Expr> &i : steps) {
		children.push(ContainerRef<AST>(i));
	}
	children.push(ContainerRef<AST>(bodyClause));
	onGetChildrenStmtFor(children);
}

bool StmtFor::onCompareStmtFor(const StmtFor &other) const {
	return true;
}

void StmtFor::onGetChildrenStmtFor(std::queue<ContainerRef<AST>> &children) {}

StmtFor::StmtFor(Range range) : Stmt(AST::ID::StmtFor, range) {}

StmtFor::StmtFor(std::vector<Container<Decl>> decls, Container<Expr> condition, std::vector<Container<Expr>> steps, Container<Stmt> bodyClause) : Stmt(AST::ID::StmtFor, Range()), decls(decls), condition(condition), steps(steps), bodyClause(bodyClause) {}

StmtFor::StmtFor(Range range, std::vector<Container<Decl>> decls, Container<Expr> condition, std::vector<Container<Expr>> steps, Container<Stmt> bodyClause) : Stmt(AST::ID::StmtFor, range), decls(decls), condition(condition), steps(steps), bodyClause(bodyClause) {}

std::vector<Container<Decl>> &StmtFor::getDecls() {
	return decls;
}

const std::vector<Container<Decl>> &StmtFor::getDecls() const {
	return decls;
}

Ref<Expr> StmtFor::getCondition() {
	return condition;
}

CRef<Expr> StmtFor::getCondition() const {
	return condition;
}

void StmtFor::setCondition(Container<Expr> value) {
	condition = value;
}

std::vector<Container<Expr>> &StmtFor::getSteps() {
	return steps;
}

const std::vector<Container<Expr>> &StmtFor::getSteps() const {
	return steps;
}

Ref<Stmt> StmtFor::getBodyClause() {
	return bodyClause;
}

CRef<Stmt> StmtFor::getBodyClause() const {
	return bodyClause;
}

void StmtFor::setBodyClause(Container<Stmt> value) {
	bodyClause = value;
}
}
