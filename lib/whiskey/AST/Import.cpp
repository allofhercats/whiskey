#include "Module.inc"

#include <whiskey/AST/Import.hpp>

namespace whiskey {
AST *Import::onClone() const {
	return new Import(getRange(), path);
}

bool Import::onCompare(const AST &other) const {
	const Import &casted = static_cast<const Import &>(other);

	if (path != casted.path) {
		return false;
	}

	if (!onCompareImport(casted)) {
		return false;
	}

	return true;
}

bool Import::onCompareImport(const Import &other) const {
	return true;
}

Import::Import(std::string path) : AST(AST::ID::Import, Range()), path(path) {}

Import::Import(Range range, std::string path) : AST(AST::ID::Import, range), path(path) {}

const std::string &Import::getPath() const {
	return path;
}

void Import::setPath(std::string value) {
	path = value;
}
}
