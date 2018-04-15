#include <whiskey/AST/FieldReal.hpp>

#include <whiskey/Core/Literals.hpp>

namespace whiskey {
void FieldReal::onPrintAsLiteral(std::ostream &os) const {
	printLiteralReal(os, value);
}

bool FieldReal::onCompare(const Field &other) const {
	return value == static_cast<const FieldReal &>(other).value;
}

void FieldReal::onPrint(std::ostream &os, int indent) const {
	printLiteralReal(os, value);
}

FieldReal::FieldReal(Real value) : Field(FieldFormat::Real), value(value) {}

Real &FieldReal::getValue() {
	return value;
}

const Real &FieldReal::getValue() const {
	return value;
}

void FieldReal::setValue(Real value) {
	this->value = value;
}
}
