#include <whiskey/Core/LiteralPrinterReal.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/LiteralPrinterInt.hpp>

namespace whiskey {
void LiteralPrinterReal::onPrint(std::ostream &os) const {
	if (value < 0) {
		os << "-";
		LiteralPrinterInt((UInt)(-(Int)value)).print(os);
	} else {
		LiteralPrinterInt((UInt)(Int)value).print(os);
	}
	
  long double dec = value - floor(value);

  os << '.';

  if (truncate) {
    unsigned int nDigits = 0;
    long double decP = dec;
    for (unsigned int i = 0; i < precision; i++) {
      decP *= 10.0;
      unsigned int digit = (unsigned int)decP % 10;
      if (digit != 0) {
        nDigits = i;
      }
    }

    for (unsigned int i = 0; i <= nDigits; i++) {
      dec *= 10.0;
      unsigned int digit = (unsigned int)dec % 10;
      if (digit <= 9) {
        os << (char)('0' + digit);
      } else {
        W_ASSERT_UNREACHABLE("Unexpected digit in real value " << digit);
      }

      if (digit != 0) {
        nDigits = i;
      }
    }
  } else {
    for (unsigned int i = 0; i < precision; i++) {
      dec *= 10.0;
      unsigned int digit = (unsigned int)dec % 10;
      if (digit <= 9) {
        os << (char)('0' + digit);
      } else {
        W_ASSERT_UNREACHABLE("Unexpected digit in real value " << digit);
      }
    }
  }
}

LiteralPrinterReal::LiteralPrinterReal(Real value, unsigned int precision, bool truncate) : value(value), precision(precision), truncate(truncate) {}

LiteralPrinterReal::~LiteralPrinterReal() {}

Real LiteralPrinterReal::getValue() const {
	return value;
}

void LiteralPrinterReal::setValue(Real value) {
	this->value = value;
}

unsigned int LiteralPrinterReal::getPrecision() const {
	return precision;
}

void LiteralPrinterReal::setPrecision(unsigned int value) {
	precision = value;
}

bool LiteralPrinterReal::getTruncate() const {
	return truncate;
}

void LiteralPrinterReal::setTruncate(bool value) {
	truncate = value;
}
}
