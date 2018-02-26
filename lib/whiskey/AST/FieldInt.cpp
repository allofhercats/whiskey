#include <whiskey/AST/FieldInt.hpp>

#include <whiskey/Core/Literals.hpp>

namespace whiskey {
void FieldInt::onPrintAsLiteral(std::ostream &os) const {
	printLiteralInt(os, value);
}

bool FieldInt::onCompare(const Field &other) const {
	return value == static_cast<const FieldInt &>(other).value;
}

void FieldInt::onPrint(std::ostream &os, int indent) const {
	printLiteralInt(os, value);
}

FieldInt::FieldInt(Int64 value) : Field(FieldFormat::Int), value(value) {}

Int64 FieldInt::getValue() const {
	return value;
}

void FieldInt::setValue(Int64 value) {
	this->value = value;
}
}
