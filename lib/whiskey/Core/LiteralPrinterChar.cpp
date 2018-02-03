#include <whiskey/Core/LiteralPrinterChar.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterUInt.hpp>

namespace whiskey {
void LiteralPrinterChar::onPrint(std::ostream &os) const {
  if (useQuotes) {
    os << quote;
  }

  if (value == quote) {
    os << '\\';
    os << quote;
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
    os << value;
  } else {
    os << "\\x";
    LiteralPrinterUInt(value & 0xff, 16, false, 2).print(os);
  }

  if (useQuotes) {
    os << quote;
  }
}

LiteralPrinterChar::LiteralPrinterChar(char value, char quote, bool useQuotes)
    : value(value), quote(quote), useQuotes(useQuotes) {
}

LiteralPrinterChar::~LiteralPrinterChar() {
}

char LiteralPrinterChar::getValue() const {
  return value;
}

void LiteralPrinterChar::setValue(char value) {
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
} // namespace whiskey
