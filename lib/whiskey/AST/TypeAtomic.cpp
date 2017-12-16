#include "Module.inc"

#include <whiskey/AST/TypeAtomic.hpp>

namespace whiskey {
AST *TypeAtomic::onClone() const {
	return new TypeAtomic(getID(), getRange());
}

bool TypeAtomic::onCompare(const AST &other) const {
	const TypeAtomic &casted = static_cast<const TypeAtomic &>(other);

	if (!onCompareTypeAtomic(casted)) {
		return false;
	}

	return true;
}

bool TypeAtomic::onCompareTypeAtomic(const TypeAtomic &other) const {
	return true;
}

TypeAtomic::TypeAtomic(AST::ID id, Range range) : Type(id, range) {}
}
