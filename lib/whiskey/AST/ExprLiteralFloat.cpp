#include "Module.inc"

#include <whiskey/AST/ExprLiteralFloat.hpp>

namespace whiskey {
AST *ExprLiteralFloat::onClone() const {
	return new ExprLiteralFloat(getRange(), getType()->cloneAs<Type>(), getValue());
}

ExprLiteralFloat::ExprLiteralFloat(Container<Type> type, long double value) : ExprLiteral<long double>(AST::ID::ExprLiteralFloat, Range(), type, value) {}

ExprLiteralFloat::ExprLiteralFloat(Range range, Container<Type> type, long double value) : ExprLiteral<long double>(AST::ID::ExprLiteralFloat, range, type, value) {}
}