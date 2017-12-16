#include "Module.inc"

#include <whiskey/AST/DeclVariable.hpp>

#include <whiskey/AST/DeclClass.hpp>

namespace whiskey {
AST *DeclClass::onClone() const {
	return new DeclClass(getRange(), getName(), inherits, members);
}

bool DeclClass::onCompareDecl(const Decl &other) const {
	const DeclClass &casted = static_cast<const DeclClass &>(other);

	if (!AST::compare(inherits, casted.inherits)) {
		return false;
	}

	if (!AST::compare(members, casted.members)) {
		return false;
	}

	if (!onCompareDeclClass(casted)) {
		return false;
	}

	return true;
}

bool DeclClass::onCompareDeclClass(const DeclClass &other) const {
	return true;
}

DeclClass::DeclClass(std::string name, std::vector<Container<Type>> inherits, std::vector<Container<Decl>> members) : Decl(AST::ID::DeclClass, Range(), name), inherits(inherits), members(members) {}

DeclClass::DeclClass(Range range, std::string name, std::vector<Container<Type>> inherits, std::vector<Container<Decl>> members) : Decl(AST::ID::DeclClass, range, name), inherits(inherits), members(members) {}

std::vector<Container<Type>> &DeclClass::getInherits() {
	return inherits;
}

const std::vector<Container<Type>> &DeclClass::getInherits() const {
	return inherits;
}

std::vector<Container<Decl>> &DeclClass::getMembers() {
	return members;
}

const std::vector<Container<Decl>> &DeclClass::getMembers() const {
	return members;
}
}
