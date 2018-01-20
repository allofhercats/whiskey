#include <whiskey/Core/LiteralPrinterBool.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void LiteralPrinterBool::onPrint(std::ostream &os) const {
	if (value) {
		os << "true";
	} else {
		os << "false";
	}
}

LiteralPrinterBool::LiteralPrinterBool(bool value) : value(value) {}

LiteralPrinterBool::~LiteralPrinterBool() {}

bool LiteralPrinterBool::getValue() const {
	return value;
}

void LiteralPrinterBool::setValue(bool value) {
	this->value = value;
}
}
