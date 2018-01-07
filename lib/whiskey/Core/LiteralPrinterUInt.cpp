#include <whiskey/Core/LiteralPrinterUInt.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void LiteralPrinterUInt::onPrint(std::ostream &os) const {
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

bool LiteralPrinterUInt::isValidBase(unsigned int base) {
  return base == 2 || base == 8 || base == 10 || base == 16;
}

void LiteralPrinterUInt::printBasePrefix(std::ostream &os, unsigned int base
                                           ) {
	if (base == 2) {
		os << "0b";
	} else if (base == 8) {
		os << "0";
	} else if (base == 16) {
		os << "0x";
	}
}

LiteralPrinterUInt::LiteralPrinterUInt(UInt value, unsigned int base, bool usePrefix, unsigned int width) : value(value), base(base), usePrefix(usePrefix), width(width) {
	W_ASSERT_TRUE(isValidBase(base), "Invalid base.");
}

LiteralPrinterUInt::~LiteralPrinterUInt() {}

UInt LiteralPrinterUInt::getValue() const {
	return value;
}

void LiteralPrinterUInt::setValue(UInt value) {
	this->value = value;
}

unsigned int LiteralPrinterUInt::getBase() const {
	return base;
}

void LiteralPrinterUInt::setBase(unsigned int value) {
	W_ASSERT_TRUE(isValidBase(base), "Invalid base.");
	base = value;
}

bool LiteralPrinterUInt::getUsePrefix() const {
	return usePrefix;
}

void LiteralPrinterUInt::setUsePrefix(bool value) {
	usePrefix = value;
}

unsigned int LiteralPrinterUInt::getWidth() const {
	return width;
}

void LiteralPrinterUInt::setWidth(unsigned int value) {
	width = value;
}
}
