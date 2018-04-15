#include <whiskey/AST/FieldString.hpp>

#include <whiskey/Core/Literals.hpp>

namespace whiskey {
std::unique_ptr<Field> FieldString::onClone() const {
	return std::make_unique<FieldString>(value);
}

void FieldString::onPrintAsLiteral(std::ostream &os) const {
	printLiteralString(os, value);
}

bool FieldString::onCompare(const Field &other) const {
	return value == static_cast<const FieldString &>(other).value;
}

void FieldString::onPrint(std::ostream &os, int indent) const {
	printLiteralString(os, value);
}

FieldString::FieldString(std::string value) : Field(FieldFormat::String), value(value) {}

std::string &FieldString::getValue() {
	return value;
}

const std::string &FieldString::getValue() const {
	return value;
}

void FieldString::setValue(std::string value) {
	this->value = value;
}
}
