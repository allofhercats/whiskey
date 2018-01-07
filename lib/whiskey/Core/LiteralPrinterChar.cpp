#include <whiskey/Core/LiteralPrinterChar.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterInt.hpp>

namespace whiskey {
void LiteralPrinterChar::onPrint(std::ostream &os) const {
	if (value == quote) {
    os << "\\" << quote;
  } else if (getChar32MinWidth(value) == 4) {
    os << "\\U";
    LiteralPrinterInt(value, 16, false, 8).print(os);
  } else if (getChar32MinWidth(value) == 2) {
    os << "\\u";
    LiteralPrinterInt(value, 16, false, 4).print(os);
  } else if (value == '\a') {
    os << "\\a";
  } else if (value == '\b') {
    os << "\\b";
  } else if (value == '\033') {
    os << "\\e";
  } else if (value == '\f') {
    os << "\\f";
  } else if (value == '\n') {
    os << "\\n";
  } else if (value == '\r') {
    os << "\\r";
  } else if (value == '\t') {
    os << "\\t";
  } else if (value == '\v') {
    os << "\\v";
  } else if (value == '\0') {
    os << "\\0";
  } else if (value == '\\') {
    os << "\\\\";
  } else if (isprint(value)) {
    os << (char)value;
  } else {
    os << "\\x";
    LiteralPrinterInt(value, 16, false, 2).print(os);
  }
}

LiteralPrinterChar::LiteralPrinterChar(Char32 value, char quote, bool useQuotes) : value(value), quote(quote), useQuotes(useQuotes) {}

LiteralPrinterChar::~LiteralPrinterChar() {}

Char32 LiteralPrinterChar::getValue() const {
	return value;
}

void LiteralPrinterChar::setValue(Char32 value) {
	this->value = value;
}

char LiteralPrinterChar::getQuote() const {
	return quote;
}

void LiteralPrinterChar::setQuote(char value) {
	quote = value;
}

bool LiteralPrinterChar::getUseQuotes() const {
	return useQuotes;
}

void LiteralPrinterChar::setUseQuotes(bool value) {
	useQuotes = value;
}
}
