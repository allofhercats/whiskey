#include <whiskey/Core/LiteralPrinterBool.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void LiteralPrinterBool::onPrint(CharOutStream &os) const {
	if (value) {
		os.write("true");
	} else {
		os.write("false");
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
