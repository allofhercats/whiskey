// #include "Module.inc"

#include <whiskey/Core/PrintLiterals.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
int getChar32MinWidth(char32_t value) {
  if ((value & 0xff) == value) {
    return 1;
  } else if ((value & 0xffff) == value) {
    return 2;
  } else {
    return 4;
  }
}

unsigned int getNDigits(uint64_t value, unsigned int base) {
  if (value == 0) {
    return 1;
  } else {
    unsigned int n = 0;
    while (value != 0) {
      value /= base;
      n++;
    }
    return n;
  }
}

void printLiteralBool(std::ostream &os, bool value) {
  if (value) {
    os << "true";
  } else {
    os << "false";
  }
}

void printLiteralInt(std::ostream &os,
                     int64_t value,
                     unsigned int base,
                     bool prefix,
                     unsigned int width) {
  if (value < 0 && base == 10) {
    os << "-";
    printLiteralUInt(os, -value, base, prefix, width);
  } else {
    printLiteralUInt(os, value, base, prefix, width);
  }
}

void printLiteralUInt(std::ostream &os,
                      uint64_t value,
                      unsigned int base,
                      bool prefix,
                      unsigned int width) {
  if (prefix) {
    switch (base) {
    case 2:
      os << "0b";
      break;
    case 8:
      os << "0";
      break;
    case 16:
      os << "0x";
      break;
    default:
      break;
    }
  }

  unsigned int nDigits = getNDigits(value, base);

  while (width > nDigits) {
    os << '0';
    width--;
  }

  int exp = (int)nDigits - 1;
  while (exp >= 0) {
    uint64_t fac = 1;
    for (int i = 0; i < exp; i++) {
      fac *= base;
    }
    uint64_t digit = (value / fac) % base;
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

void printLiteralReal(std::ostream &os,
                      long double value,
                      unsigned int precision,
                      bool truncate) {
  printLiteralInt(os, (int64_t)value);
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

namespace {
void printLiteralCharHelper(std::ostream &os, char32_t value, char quote) {
  if (value == quote) {
    os << "\\" << quote;
  } else if (getChar32MinWidth(value) == 4) {
    os << "\\U";
    printLiteralUInt(os, value, 16, false, 8);
  } else if (getChar32MinWidth(value) == 2) {
    os << "\\u";
    printLiteralUInt(os, value, 16, false, 4);
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
    printLiteralUInt(os, value, 16, false, 2);
  }
}
} // namespace

void printLiteralChar(std::ostream &os, char32_t value) {
  os << "'";
  printLiteralCharHelper(os, value, '\'');
  os << "'";
}

void printLiteralString(std::ostream &os, const std::string &value) {
  os << "\"";
  for (char i : value) {
    printLiteralCharHelper(os, 0xff & i, '\"');
  }
  os << "\"";
}

void printLiteralString(std::ostream &os, const std::u16string &value) {
  os << "\"";
  for (char16_t i : value) {
    printLiteralCharHelper(os, 0xffff & i, '\"');
  }
  os << "\"";
}

void printLiteralString(std::ostream &os, const std::u32string &value) {
  os << "\"";
  for (char32_t i : value) {
    printLiteralCharHelper(os, i, '\"');
  }
  os << "\"";
}
} // namespace whiskey
