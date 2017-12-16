#include "Module.inc"

#include <whiskey/AST/ExprLiteralInt.hpp>

namespace whiskey {
AST *ExprLiteralInt::onClone() const {
	return new ExprLiteralInt(getRange(), getType()->cloneAs<Type>(), getValue());
}

ExprLiteralInt::ExprLiteralInt(Container<Type> type, int64_t value) : ExprLiteral<int64_t>(AST::ID::ExprLiteralInt, Range(), type, value) {}

ExprLiteralInt::ExprLiteralInt(Range range, Container<Type> type, int64_t value) : ExprLiteral<int64_t>(AST::ID::ExprLiteralInt, range, type, value) {}
}