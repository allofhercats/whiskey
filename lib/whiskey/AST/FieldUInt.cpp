#include <whiskey/AST/FieldUInt.hpp>

#include <whiskey/Core/Literals.hpp>

namespace whiskey {
void FieldUInt::onPrintAsLiteral(std::ostream &os) const {
	printLiteralUInt(os, value);
}

bool FieldUInt::onCompare(const Field &other) const {
	return value == static_cast<const FieldUInt &>(other).value;
}

void FieldUInt::onPrint(std::ostream &os, int indent) const {
	printLiteralUInt(os, value);
	os << "u";
}

FieldUInt::FieldUInt(UInt64 value) : Field(FieldFormat::UInt), value(value) {}

UInt64 FieldUInt::getValue() const {
	return value;
}

void FieldUInt::setValue(UInt64 value) {
	this->value = value;
}
}
