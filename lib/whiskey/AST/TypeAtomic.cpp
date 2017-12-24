#include "Module.inc"

#include <whiskey/AST/TypeAtomic.hpp>

namespace whiskey {
AST *TypeAtomic::onClone() const {
	return new TypeAtomic(getID(), getRange());
}

bool TypeAtomic::onCompareType(const Type &other) const {
	const TypeAtomic &casted = static_cast<const TypeAtomic &>(other);

	if (!onCompareTypeAtomic(casted)) {
		return false;
	}

	return true;
}

void TypeAtomic::onGetChildrenType(std::queue<ContainerRef<AST>> &children) {
	onGetChildrenTypeAtomic(children);
}

bool TypeAtomic::onCompareTypeAtomic(const TypeAtomic &other) const {
	return true;
}

void TypeAtomic::onGetChildrenTypeAtomic(std::queue<ContainerRef<AST>> &children) {}

TypeAtomic::TypeAtomic(AST::ID id, Range range) : Type(id, range) {}
}
