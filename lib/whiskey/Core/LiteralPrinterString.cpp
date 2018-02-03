#include <whiskey/Core/LiteralPrinterString.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterChar.hpp>

namespace whiskey {
void LiteralPrinterString::onPrint(std::ostream &os) const {
  if (useQuotes) {
    os << quote;
  }

  for (char i : value) {
    LiteralPrinterChar(i, '\"', false).print(os);
  }

  if (useQuotes) {
    os << quote;
  }
}

LiteralPrinterString::LiteralPrinterString(std::string value,
                                           char quote,
                                           bool useQuotes)
    : value(value), quote(quote), useQuotes(useQuotes) {
}

LiteralPrinterString::~LiteralPrinterString() {
}

std::string &LiteralPrinterString::getValue() {
  return value;
}

const std::string &LiteralPrinterString::getValue() const {
  return value;
}

void LiteralPrinterString::setValue(std::string value) {
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
} // namespace whiskey
