#include "Module.inc"

#include <whiskey/AST/TypeFunction.hpp>

namespace whiskey {
AST *TypeFunction::onClone() const {
	return new TypeFunction(getRange(), ret, args);
}

bool TypeFunction::onCompare(const AST &other) const {
	const TypeFunction &casted = static_cast<const TypeFunction &>(other);

	if (!AST::compare(ret, casted.ret)) {
		return false;
	}

	if (!AST::compare(args, casted.args)) {
		return false;
	}

	if (!onCompareTypeFunction(casted)) {
		return false;
	}

	return true;
}

bool TypeFunction::onCompareTypeFunction(const TypeFunction &other) const {
	return true;
}

TypeFunction::TypeFunction(Container<Type> ret, std::vector<Container<Type>> args) : Type(AST::ID::TypeFunction, Range()), ret(ret), args(args) {}

TypeFunction::TypeFunction(Range range, Container<Type> ret, std::vector<Container<Type>> args) : Type(AST::ID::TypeFunction, range), ret(ret), args(args) {}

Ref<Type> TypeFunction::getRet() {
	return ret;
}

CRef<Type> TypeFunction::getRet() const {
	return ret;
}

void TypeFunction::setRet(Container<Type> value) {
	ret = value;
}

std::vector<Container<Type>> &TypeFunction::getArgs() {
	return args;
}

const std::vector<Container<Type>> &TypeFunction::getArgs() const {
	return args;
}
}
