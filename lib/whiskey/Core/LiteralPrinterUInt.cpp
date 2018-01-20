#include <whiskey/Core/LiteralPrinterUInt.hpp>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void LiteralPrinterUInt::onPrint(std::ostream &os) const {
	if (usePrefix) {
		printBasePrefix(os, base);
	}

	int nDigits = getNDigits(value, base);

	if (width > nDigits) {
	  for (int i = 0; i < width - nDigits; i++) {
	  	os << '0';
	  }
	}

  int exp = (int)nDigits - 1;
  while (exp >= 0) {
    UInt64 fac = 1;
    for (int i = 0; i < exp; i++) {
      fac *= base;
    }
    UInt64 digit = (value / fac) % base;
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

bool LiteralPrinterUInt::isValidBase(int base) {
  return base == 2 || base == 8 || base == 10 || base == 16;
}

void LiteralPrinterUInt::printBasePrefix(std::ostream &os, int base
                                           ) {
	if (base == 2) {
		os << "0b";
	} else if (base == 8) {
		os << "0";
	} else if (base == 16) {
		os << "0x";
	}
}

LiteralPrinterUInt::LiteralPrinterUInt(UInt64 value, int base, bool usePrefix, int width) : value(value), base(base), usePrefix(usePrefix), width(width) {
	W_ASSERT_TRUE(isValidBase(base), "Invalid base.");
}

LiteralPrinterUInt::~LiteralPrinterUInt() {}

UInt64 LiteralPrinterUInt::getValue() const {
	return value;
}

void LiteralPrinterUInt::setValue(UInt64 value) {
	this->value = value;
}

int LiteralPrinterUInt::getBase() const {
	return base;
}

void LiteralPrinterUInt::setBase(int value) {
	W_ASSERT_TRUE(isValidBase(base), "Invalid base.");
	base = value;
}

bool LiteralPrinterUInt::getUsePrefix() const {
	return usePrefix;
}

void LiteralPrinterUInt::setUsePrefix(bool value) {
	usePrefix = value;
}

int LiteralPrinterUInt::getWidth() const {
	return width;
}

void LiteralPrinterUInt::setWidth(int value) {
	width = value;
}
}
