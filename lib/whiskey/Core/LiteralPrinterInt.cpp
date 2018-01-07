#include <whiskey/Core/LiteralPrinterInt.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void LiteralPrinterInt::onPrint(std::ostream &os) const {
	if (usePrefix) {
		printBasePrefix(os, base);
	}

	DigitCount nDigits = getNDigits(value, base);

	if (width > nDigits) {
	  for (unsigned int i = 0; i < width - nDigits; i++) {
	  	os << '0';
	  }
	}

  int exp = (int)nDigits - 1;
  while (exp >= 0) {
    UInt fac = 1;
    for (int i = 0; i < exp; i++) {
      fac *= base;
    }
    UInt digit = (value / fac) % base;
    if (digit <= 9) {
      os << (char)('0' + digit);
    } else if (10 <= digit && digit <= 15) {
      os << (char)('a' + (digit - 10));
    } else {
      W_ASSERT_UNREACHABLE("Unsupported base " << base);
    }
    exp--;
  }
}

bool LiteralPrinterInt::isValidBase(unsigned int base) {
  return base == 2 || base == 8 || base == 10 || base == 16;
}

void LiteralPrinterInt::printBasePrefix(std::ostream &os, unsigned int base
                                           ) {
	if (base == 2) {
		os << "0b";
	} else if (base == 8) {
		os << "0";
	} else if (base == 16) {
		os << "0x";
	}
}

LiteralPrinterInt::LiteralPrinterInt(UInt value, unsigned int base, bool usePrefix, unsigned int width) : value(value), base(base), usePrefix(usePrefix), width(width) {
	W_ASSERT_TRUE(isValidBase(base), "Invalid base.");
}

LiteralPrinterInt::~LiteralPrinterInt() {}

UInt LiteralPrinterInt::getValue() const {
	return value;
}

void LiteralPrinterInt::setValue(UInt value) {
	this->value = value;
}

unsigned int LiteralPrinterInt::getBase() const {
	return base;
}

void LiteralPrinterInt::setBase(unsigned int value) {
	W_ASSERT_TRUE(isValidBase(base), "Invalid base.");
	base = value;
}

bool LiteralPrinterInt::getUsePrefix() const {
	return usePrefix;
}

void LiteralPrinterInt::setUsePrefix(bool value) {
	usePrefix = value;
}

unsigned int LiteralPrinterInt::getWidth() const {
	return width;
}

void LiteralPrinterInt::setWidth(unsigned int value) {
	width = value;
}
}
