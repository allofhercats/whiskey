#include "Module.inc"

#include <whiskey/AST/ExprUnary.hpp>

namespace whiskey {
AST *ExprUnary::onClone() const {
	return new ExprUnary(getID(), getRange(), arg);
}

bool ExprUnary::onCompare(const AST &other) const {
	const ExprUnary &casted = static_cast<const ExprUnary &>(other);

	if (!AST::compare(arg, casted.arg)) {
		return false;
	}

	if (!onCompareExprUnary(casted)) {
		return false;
	}

	return true;
}

bool ExprUnary::onCompareExprUnary(const ExprUnary &other) const {
	return true;
}

ExprUnary::ExprUnary(AST::ID id, Container<Expr> arg) : Expr(id, Range()), arg(arg) {}

ExprUnary::ExprUnary(AST::ID id, Range range, Container<Expr> arg) : Expr(id, range), arg(arg) {}

Ref<Expr> ExprUnary::getArg() {
	return arg;
}

CRef<Expr> ExprUnary::getArg() const {
	return arg;
}

void ExprUnary::setArg(Container<Expr> value) {
	arg = value;
}
}
