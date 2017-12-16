#include "Module.inc"

#include <whiskey/AST/ExprBinary.hpp>

namespace whiskey {
AST *ExprBinary::onClone() const {
	return new ExprBinary(getID(), getRange(), lhs, rhs);
}

bool ExprBinary::onCompare(const AST &other) const {
	const ExprBinary &casted = static_cast<const ExprBinary &>(other);

	if (!AST::compare(lhs, casted.lhs)) {
		return false;
	}

	if (!AST::compare(rhs, casted.rhs)) {
		return false;
	}

	if (!onCompareExprBinary(casted)) {
		return false;
	}

	return true;
}

bool ExprBinary::onCompareExprBinary(const ExprBinary &other) const {
	return true;
}

ExprBinary::ExprBinary(AST::ID id, Container<Expr> lhs, Container<Expr> rhs) : Expr(id, Range()), lhs(lhs), rhs(rhs) {}

ExprBinary::ExprBinary(AST::ID id, Range range, Container<Expr> lhs, Container<Expr> rhs) : Expr(id, range), lhs(lhs), rhs(rhs) {}

Ref<Expr> ExprBinary::getLHS() {
	return lhs;
}

CRef<Expr> ExprBinary::getLHS() const {
	return lhs;
}

void ExprBinary::setLHS(Container<Expr> value) {
	lhs = value;
}

Ref<Expr> ExprBinary::getRHS() {
	return rhs;
}

CRef<Expr> ExprBinary::getRHS() const {
	return rhs;
}

void ExprBinary::setRHS(Container<Expr> value) {
	rhs = value;
}
}
