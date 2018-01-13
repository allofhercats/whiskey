#include <whiskey/Core/LiteralPrinter.hpp>

namespace whiskey {
LiteralPrinter::LiteralPrinter() {
}

LiteralPrinter::~LiteralPrinter() {
}

void LiteralPrinter::print(CharOutStream &os) const {
  onPrint(os);
}
} // namespace whiskey
