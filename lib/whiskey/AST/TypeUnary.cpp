#include "Module.inc"

#include <whiskey/AST/TypeUnary.hpp>

namespace whiskey {
AST *TypeUnary::onClone() const {
	return new TypeUnary(getID(), getRange(), arg);
}

bool TypeUnary::onCompare(const AST &other) const {
	const TypeUnary &casted = static_cast<const TypeUnary &>(other);

	if (!AST::compare(arg, casted.arg)) {
		return false;
	}

	if (!onCompareTypeUnary(casted)) {
		return false;
	}

	return true;
}

bool TypeUnary::onCompareTypeUnary(const TypeUnary &other) const {
	return true;
}

TypeUnary::TypeUnary(AST::ID id, Container<Type> arg) : Type(id, Range()), arg(arg) {}

TypeUnary::TypeUnary(AST::ID id, Range range, Container<Type> arg) : Type(id, range), arg(arg) {}

Ref<Type> TypeUnary::getArg() {
	return arg;
}

CRef<Type> TypeUnary::getArg() const {
	return arg;
}

void TypeUnary::setArg(Container<Type> value) {
	arg = value;
}
}