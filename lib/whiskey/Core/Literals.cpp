#include <whiskey/Core/Literals.hpp>

#include <math.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
void printLiteralBool(std::ostream &os, bool value) {
	if (value) {
		os << "true";
	} else {
		os << "false";
	}
}

void printLiteralUInt(std::ostream &os, uint64_t value, int base, int width, bool usePrefix) {
	if (usePrefix) {
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
    }
  }

  int nDigits = getNDigits(value, base);

  if (width > nDigits) {
    for (int i = 0; i < width - nDigits; i++) {
      os << '0';
    }
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

void printLiteralInt(std::ostream &os, int64_t value, int base, int width, bool usePrefix) {
	if (value < 0) {
		if (base == 10) {
			os << "-";
		}

		printLiteralUInt(os, -value, base, width, usePrefix);
	} else {
		printLiteralUInt(os, value, base, width, usePrefix);
	}
}

void printLiteralReal(std::ostream &os, long double value, int precision, bool truncate) {
	if (value < 0) {
    os << '-';
    printLiteralUInt(os, (uint64_t)(-(int64_t)value), 10, 0, false);
  } else {
    printLiteralUInt(os, (uint64_t)(int64_t)value, 10, 0, false);
  }

  long double dec = (value < 0 ? -value : value) - floor(value);

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

void printLiteralChar(std::ostream &os, char32_t value, char quote, bool useQuotes) {
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
    os << (char)value;
  } else if (getCharWidth(value) == 1) {
    os << "\\x";
    printLiteralUInt(os, value & 0xff, 16, 2, false);
  } else if (getCharWidth(value) == 2) {
    os << "\\u";
    printLiteralUInt(os, value & 0xffff, 16, 4, false);
  } else {
  	os << "\\U";
    printLiteralUInt(os, value, 16, 8, false);
  }

  if (useQuotes) {
    os << quote;
  }
}

void printLiteralString(std::ostream &os, const std::string &value, char quote, bool useQuotes) {
	if (useQuotes) {
    os << quote;
  }

  for (char i : value) {
    printLiteralChar(os, 0xff & i, '\"', false);
  }

  if (useQuotes) {
    os << quote;
  }
}

bool evalLiteralBool(const std::string &text, bool &value) {
	if (text == "true") {
		value = true;
		return true;
	} else if (text == "false") {
		value = false;
		return true;
	} else {
		return false;
	}
}

bool evalLiteralUInt(const std::string &text, uint64_t &value) {
  value = 0;

  std::string::const_iterator i = text.cbegin();
  size_t n = 0;

  if (i == text.cend()) {
    return false;
  }

  if (*i == '0') {
    ++i;
    n++;

    if (i == text.cend()) {
      value = 0;
      return true;
    }

    if (*i == 'b') {
      ++i;
      n++;

      if (i == text.cend()) {
        return false;
      }

      while (i != text.cend()) {
        if (*i >= '0' && *i <= '1') {
          value *= 2;
          value += *i - '0';
          ++i;
          n++;
        } else {
          return false;
        }
      }

      return true;
    } else if (*i == 'x') {
      ++i;
      n++;

      if (i == text.cend()) {
        return false;
      }

      while (i != text.cend()) {
        if (*i >= '0' && *i <= '9') {
          value *= 16;
          value += *i - '0';
          ++i;
          n++;
        } else if (*i >= 'a' && *i <= 'f') {
          value *= 16;
          value += 10 + *i - 'a';
          ++i;
          n++;
        } else if (*i >= 'A' && *i <= 'F') {
          value *= 16;
          value += 10 + *i - 'A';
          ++i;
          n++;
        } else {
          return false;
        }
      }

      return true;
    } else {
      while (i != text.cend()) {
        if (*i >= '0' && *i <= '7') {
          value *= 8;
          value += *i - '0';
          ++i;
          n++;
        } else {
          return false;
        }
      }

      return true;
    }
  } else if (*i >= '1' && *i <= '9') {
    while (i != text.cend()) {
      if (*i >= '0' && *i <= '9') {
        value *= 10;
        value += *i - '0';
        ++i;
        n++;
      } else {
        return false;
      }
    }

    return true;
  } else {
    return false;
  }
}

bool evalLiteralReal(const std::string &text, long double &value) {
  long double _int = 0.0;
  long double _dec = 0.0;
  long double _fac = 1.0;

  value = 0.0;

  std::string::const_iterator i = text.cbegin();
  size_t n = 0;

  if (i == text.cend()) {
    return false;
  }

  bool endedCorrectly = false;

  while (i != text.cend()) {
    if (*i >= '0' && *i <= '9') {
      _int *= 10.0;
      _int += *i - '0';
      ++i;
      n++;
    } else if (*i == '.') {
      endedCorrectly = true;
      ++i;
      n++;
      break;
    } else {
      return false;
    }
  }

  if (!endedCorrectly) {
    value = _int;
    return true;
  }

  while (i != text.cend()) {
    if (*i >= '0' && *i <= '9') {
      _dec *= 10.0;
      _dec += *i - '0';
      _fac *= 0.1;
      ++i;
      n++;
    } else {
      return false;
    }
  }

  value = _int + (_dec * _fac);
  return true;
}

namespace {
bool evalLiteralCharHelper(std::string::const_iterator &i, std::string::const_iterator end, char32_t &value) {
  value = 0;

  size_t n = 0;

  if (i == end) {
    return false;
  }

  if (*i == '\\') {
    ++i;
    n++;

    if (i == end) {
      return false;
    }

    if (*i == 'a') {
      ++i;
      value = '\a';
      return true;
    } else if (*i == 'b') {
      ++i;
      value = '\b';
      return true;
    } else if (*i == 'e') {
      ++i;
      value = '\033';
      return true;
    } else if (*i == 'f') {
      ++i;
      value = '\f';
      return true;
    } else if (*i == 'n') {
      ++i;
      value = '\n';
      return true;
    } else if (*i == 'r') {
      ++i;
      value = '\r';
      return true;
    } else if (*i == 't') {
      ++i;
      value = '\t';
      return true;
    } else if (*i == 'v') {
      ++i;
      value = '\v';
      return true;
    } else if (*i == 'x') {
      for (int j = 0; j < 2; j++) {
        value *= 16;
        ++i;
        n++;

        if (i == end) {
          return false;
        } else if (*i >= '0' && *i <= '9') {
          value += *i - '0';
        } else if (*i >= 'a' && *i <= 'f') {
          value += 10 + *i - 'a';
        } else if (*i >= 'A' && *i <= 'F') {
          value += 10 + *i - 'A';
        } else {
          return false;
        }
      }

      ++i;
      return true;
    } else if (*i == 'u') {
      for (int j = 0; j < 4; j++) {
        value *= 16;
        ++i;
        n++;

        if (i == end) {
          return false;
        } else if (*i >= '0' && *i <= '9') {
          value += *i - '0';
        } else if (*i >= 'a' && *i <= 'f') {
          value += 10 + *i - 'a';
        } else if (*i >= 'A' && *i <= 'F') {
          value += 10 + *i - 'A';
        } else {
          return false;
        }
      }

      ++i;
      return true;
    } else if (*i == 'U') {
      for (int j = 0; j < 8; j++) {
        value *= 16;
        ++i;
        n++;

        if (i == end) {
          return false;
        } else if (*i >= '0' && *i <= '9') {
          value += *i - '0';
        } else if (*i >= 'a' && *i <= 'f') {
          value += 10 + *i - 'a';
        } else if (*i >= 'A' && *i <= 'F') {
          value += 10 + *i - 'A';
        } else {
          return false;
        }
      }

      ++i;
      return true;
    } else if (*i >= '0' && *i <= '7') {
      value = (*i++) - '0';
      n++;

      if (i == end) {
        return true;
      } else if (*i >= '0' && *i <= '7') {
        value *= 8;
        value += (*i++) - '0';
        n++;

        if (i == end) {
          return true;
        } else if (*i >= '0' && *i <= '7') {
          value *= 8;
          value += (*i++) - '0';
          n++;
          return true;
        } else {
          return true;
        }
      } else {
        return true;
      }
    } else {
      value = *i++;
      return true;
    }
  } else {
    value = *i++;
    return true;
  }
}
} // namespace

bool evalLiteralChar(const std::string &text, char32_t &value) {
  value = '\0';

  std::string::const_iterator i = text.cbegin();
  size_t n = 0;

  if (i == text.cend()) {
    return false;
  }

  if (*i != '\'') {
    return false;
  }

  ++i;
  n++;

  if (i == text.cend()) {
    return false;
  }

  if (evalLiteralCharHelper(i, text.cend(), value)) {
    if (*i != '\'') {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool evalLiteralString(const std::string &text, std::string &value) {
  value = "";

  std::string::const_iterator i = text.cbegin();
  size_t n = 0;

  if (i == text.cend()) {
    return false;
  }

  if (*i != '\"') {
    return false;
  }

  ++i;
  n++;

  bool endedCorrectly = false;

  while (i != text.cend()) {
    if (*i == '\"') {
      endedCorrectly = true;
      break;
    } else {
      char32_t tmp;
      if (!evalLiteralCharHelper(
              i,
              text.cend(),
              tmp)) {
        return false;
      }

      value.push_back(0xff & tmp);
    }
  }

  return endedCorrectly;
}
}
