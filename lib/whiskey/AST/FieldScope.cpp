#include <whiskey/AST/FieldScope.hpp>

#include <whiskey/Core/Literals.hpp>
#include <whiskey/AST/Scope.hpp>

namespace whiskey {
bool FieldScope::onCompare(const Field &other) const {
	return true;
}

void FieldScope::onPrint(std::ostream &os, int indent) const {
	value->print(os, indent);
}

FieldScope::FieldScope() : Field(FieldFormat::Scope), value(std::make_unique<Scope>()) {}

Scope &FieldScope::getValue() {
	return *value;
}

const Scope &FieldScope::getValue() const {
	return *value;
}
}
