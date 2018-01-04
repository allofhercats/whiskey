// #include "Module.inc"

#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
LiteralPrinter::LiteralPrinter() {}

LiteralPrinter::~LiteralPrinter() {}

void LiteralPrinter::print(std::ostream &os) const {
	onPrint(os);
}
}
