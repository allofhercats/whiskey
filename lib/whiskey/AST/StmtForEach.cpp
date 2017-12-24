#include "Module.inc"

#include <whiskey/AST/DeclVariable.hpp>

#include <whiskey/AST/StmtForEach.hpp>

namespace whiskey {
AST *StmtForEach::onClone() const {
	return new StmtForEach(getRange(), value, sequence, bodyClause);
}

bool StmtForEach::onCompareStmt(const Stmt &other) const {
	const StmtForEach &casted = static_cast<const StmtForEach &>(other);

	if (!AST::compare(value, casted.value)) {
		return false;
	}

	if (!AST::compare(sequence, casted.sequence)) {
		return false;
	}

	if (!AST::compare(bodyClause, casted.bodyClause)) {
		return false;
	}

	if (!onCompareStmtForEach(casted)) {
		return false;
	}

	return true;
}

void StmtForEach::onGetChildrenStmt(std::queue<ContainerRef<AST>> &children) {
	children.push(ContainerRef<AST>(value));
	children.push(ContainerRef<AST>(sequence));
	children.push(ContainerRef<AST>(bodyClause));
	onGetChildrenStmtForEach(children);
}

bool StmtForEach::onCompareStmtForEach(const StmtForEach &other) const {
	return true;
}

void StmtForEach::onGetChildrenStmtForEach(std::queue<ContainerRef<AST>> &children) {}

StmtForEach::StmtForEach(Container<Decl> value, Container<Expr> sequence, Container<Stmt> bodyClause) : Stmt(AST::ID::StmtForEach, Range()), value(value), sequence(sequence), bodyClause(bodyClause) {}

StmtForEach::StmtForEach(Range range, Container<Decl> value, Container<Expr> sequence, Container<Stmt> bodyClause) : Stmt(AST::ID::StmtForEach, range), value(value), sequence(sequence), bodyClause(bodyClause) {}

Ref<Decl> StmtForEach::getValue() {
	return value;
}

CRef<Decl> StmtForEach::getValue() const {
	return value;
}

void StmtForEach::setValue(Container<Decl> value) {
	this->value = value;
}

Ref<Expr> StmtForEach::getSequence() {
	return sequence;
}

CRef<Expr> StmtForEach::getSequence() const {
	return sequence;
}

void StmtForEach::setSequence(Container<Expr> value) {
	sequence = value;
}

Ref<Stmt> StmtForEach::getBodyClause() {
	return bodyClause;
}

CRef<Stmt> StmtForEach::getBodyClause() const {
	return bodyClause;
}

void StmtForEach::setBodyClause(Container<Stmt> value) {
	bodyClause = value;
}
}
