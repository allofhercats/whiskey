#include <whiskey/Core/LiteralPrinterChar.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterUInt.hpp>

namespace whiskey {
void LiteralPrinterChar::onPrint(CharOutStream &os) const {
  if (useQuotes) {
    os.write(quote);
  }
	
  if (value == quote) {
    os.write('\\');
    os.write(quote);
  } else if (getChar32MinWidth(value) == 4) {
    os.write('\\');
    os.write('U');
    LiteralPrinterUInt(value, 16, false, 8).print(os);
  } else if (getChar32MinWidth(value) == 2) {
    os.write('\\');
    os.write('u');
    LiteralPrinterUInt(value, 16, false, 4).print(os);
  } else if (value == '\a') {
    os.write('\\');
    os.write('a');
  } else if (value == '\b') {
    os.write('\\');
    os.write('b');
  } else if (value == '\033') {
    os.write('\\');
    os.write('e');
  } else if (value == '\f') {
    os.write('\\');
    os.write('f');
  } else if (value == '\n') {
    os.write('\\');
    os.write('n');
  } else if (value == '\r') {
    os.write('\\');
    os.write('r');
  } else if (value == '\t') {
    os.write('\\');
    os.write('t');
  } else if (value == '\v') {
    os.write('\\');
    os.write('v');
  } else if (value == '\0') {
    os.write('\\');
    os.write('0');
  } else if (value == '\\') {
    os.write('\\');
    os.write('\\');
  } else if (isprint(value)) {
    os.write(value);
  } else {
    os.write('\\');
    os.write('x');
    LiteralPrinterUInt(value, 16, false, 2).print(os);
  }

  if (useQuotes) {
    os.write(quote);
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
