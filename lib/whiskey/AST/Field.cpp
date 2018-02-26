#include <whiskey/AST/Field.hpp>

namespace whiskey {
void Field::onPrintAsLiteral(std::ostream &os) const {
	W_ASSERT_UNREACHABLE("Printing as literal is not supported for field format.");
}

Field::Field(FieldFormat format) : format(format) {}

FieldFormat Field::getFormat() const {
	return format;
}

void Field::printAsLiteral(std::ostream &os) const {
	onPrintAsLiteral(os);
}

bool Field::operator==(const Field &other) const {
	if (format != other.format) {
		return false;
	}

	return onCompare(other);
}

bool Field::operator!=(const Field &other) const {
	return !(*this == other);
}

void Field::print(std::ostream &os, int indent) const {
	onPrint(os, indent);
}

std::ostream &operator<<(std::ostream &os, const Field &value) {
	value.print(os);
	return os;
}
}
