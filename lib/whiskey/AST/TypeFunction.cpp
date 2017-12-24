#include "Module.inc"

#include <whiskey/AST/TypeFunction.hpp>

namespace whiskey {
AST *TypeFunction::onClone() const {
	return new TypeFunction(getRange(), ret, args);
}

bool TypeFunction::onCompareType(const Type &other) const {
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

void TypeFunction::onGetChildrenType(std::queue<ContainerRef<AST>> &children) {
	children.push(ContainerRef<AST>(ret));
	for (Container<Type> &i : args) {
		children.push(ContainerRef<AST>(i));
	}
	onGetChildrenTypeFunction(children);
}

bool TypeFunction::onCompareTypeFunction(const TypeFunction &other) const {
	return true;
}

void TypeFunction::onGetChildrenTypeFunction(std::queue<ContainerRef<AST>> &children) {}

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
