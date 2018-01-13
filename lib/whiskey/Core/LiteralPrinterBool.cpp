#include <whiskey/Core/LiteralPrinterBool.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void LiteralPrinterBool::onPrint(CharOutStream &os) const {
	if (value) {
		//os << "true";
		os.write('t');
		os.write('r');
		os.write('u');
		os.write('e');
	} else {
		// os << "false";
		os.write('f');
		os.write('a');
		os.write('l');
		os.write('s');
		os.write('e');
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
