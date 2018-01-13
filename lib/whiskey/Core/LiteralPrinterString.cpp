#include <whiskey/Core/LiteralPrinterString.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterChar.hpp>
#include <whiskey/Unicode/StringRef.hpp>

namespace whiskey {
void LiteralPrinterString::onPrint(CharOutStream &os) const {
  if (useQuotes) {
    os.write(quote);
  }
	
  for (size_t i = 0; i < value.getLength(); i++) {
    LiteralPrinterChar(value.getCharAt(i), '\"', false).print(os);
  }

  if (useQuotes) {
    os.write(quote);
  }
}

LiteralPrinterString::LiteralPrinterString(StringRef value, char quote, bool useQuotes) : value(value), quote(quote), useQuotes(useQuotes) {}

LiteralPrinterString::~LiteralPrinterString() {}

StringRef &LiteralPrinterString::getValue() {
  return value;
}

const StringRef &LiteralPrinterString::getValue() const {
	return value;
}

void LiteralPrinterString::setValue(StringRef value) {
	this->value = value;
}

char LiteralPrinterString::getQuote() const {
	return quote;
}

void LiteralPrinterString::setQuote(char value) {
	quote = value;
}

bool LiteralPrinterString::getUseQuotes() const {
	return useQuotes;
}

void LiteralPrinterString::setUseQuotes(bool value) {
	useQuotes = value;
}
}
