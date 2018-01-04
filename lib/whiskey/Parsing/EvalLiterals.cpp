// #include "Module.inc"

#include <whiskey/Parsing/EvalLiterals.hpp>

#include <whiskey/Core/PrintLiterals.hpp>
#include <whiskey/Source/Range.hpp>

namespace whiskey {
void appendChar16ToString8(std::string &value, char16_t chr) {
  appendChar32ToString8(value, chr);
}

void appendChar32ToString8(std::string &value, char32_t chr) {
  int width = getChar32MinWidth(chr);
  if (width == 1) {
    value.push_back((char)chr);
  } else if (width == 2) {
    char16_t tmp = (char16_t)chr;
    const char *ptr = (const char *)&tmp;
    value.push_back(ptr[0]);
    value.push_back(ptr[1]);
  } else if (width == 4) {
    const char *ptr = (const char *)&chr;
    value.push_back(ptr[0]);
    value.push_back(ptr[1]);
    value.push_back(ptr[2]);
    value.push_back(ptr[3]);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported min character width " << width << ".");
  }
}

void appendChar32ToString16(std::u16string &value, char32_t chr) {
  int width = getChar32MinWidth(chr);
  if (width == 1 || width == 2) {
    value.push_back((char16_t)chr);
  } else if (width == 4) {
    const char16_t *ptr = (const char16_t *)&chr;
    value.push_back(ptr[0]);
    value.push_back(ptr[1]);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported min character width " << width << ".");
  }
}

bool evalLiteralUInt(const Range &range, uint64_t &value) {
  value = 0;

  Location i = range.getStart();
  size_t n = 0;

  if (n >= range.getLength()) {
    return false;
  }

  if (i.getChar() == '0') {
    i.eatChar();
    n++;

    if (n >= range.getLength()) {
      value = 0;
      return true;
    }

    if (i.getChar() == 'b') {
      i.eatChar();
      n++;

      if (!i.areMoreChars()) {
        return false;
      }

      while (n < range.getLength()) {
        if (i.getChar() >= '0' && i.getChar() <= '1') {
          value *= 2;
          value += i.getChar() - '0';
          i.eatChar();
          n++;
        } else {
          return false;
        }
      }

      return true;
    } else if (i.getChar() == 'x') {
      i.eatChar();
      n++;

      if (!i.areMoreChars()) {
        return false;
      }

      while (n < range.getLength()) {
        if (i.getChar() >= '0' && i.getChar() <= '9') {
          value *= 16;
          value += i.getChar() - '0';
          i.eatChar();
          n++;
        } else if (i.getChar() >= 'a' && i.getChar() <= 'f') {
          value *= 16;
          value += 10 + i.getChar() - 'a';
          i.eatChar();
          n++;
        } else if (i.getChar() >= 'A' && i.getChar() <= 'F') {
          value *= 16;
          value += 10 + i.getChar() - 'A';
          i.eatChar();
          n++;
        } else {
          return false;
        }
      }

      return true;
    } else {
      while (n < range.getLength()) {
        if (i.getChar() >= '0' && i.getChar() <= '7') {
          value *= 8;
          value += i.getChar() - '0';
          i.eatChar();
          n++;
        } else {
          return false;
        }
      }

      return true;
    }
  } else if (i.getChar() >= '1' && i.getChar() <= '9') {
    while (n < range.getLength()) {
      if (i.getChar() >= '0' && i.getChar() <= '9') {
        value *= 10;
        value += i.getChar() - '0';
        i.eatChar();
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

bool evalLiteralReal(const Range &range, long double &value) {
  long double _int = 0.0;
  long double _dec = 0.0;
  long double _fac = 1.0;

  value = 0.0;

  Location i = range.getStart();
  size_t n = 0;

  if (n >= range.getLength()) {
    return false;
  }

  bool endedCorrectly = false;

  while (n < range.getLength()) {
    if (i.getChar() >= '0' && i.getChar() <= '9') {
      _int *= 10.0;
      _int += i.getChar() - '0';
      i.eatChar();
      n++;
    } else if (i.getChar() == '.') {
      endedCorrectly = true;
      i.eatChar();
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

  while (n < range.getLength()) {
    if (i.getChar() >= '0' && i.getChar() <= '9') {
      _dec *= 10.0;
      _dec += i.getChar() - '0';
      _fac *= 0.1;
      i.eatChar();
      n++;
    } else {
      return false;
    }
  }

  value = _int + (_dec * _fac);
  return true;
}

namespace {
bool evalLiteralCharHelper(Location &loc, size_t length, char32_t &value) {
  value = 0;

  size_t n = 0;

  if (n >= length) {
    return false;
  }

  if (loc.getChar() == '\\') {
    loc.eatChar();
    n++;

    if (n >= length) {
      return false;
    }

    if (loc.getChar() == 'a') {
      loc.eatChar();
      value = '\a';
      return true;
    } else if (loc.getChar() == 'b') {
      loc.eatChar();
      value = '\b';
      return true;
    } else if (loc.getChar() == 'e') {
      loc.eatChar();
      value = '\033';
      return true;
    } else if (loc.getChar() == 'f') {
      loc.eatChar();
      value = '\f';
      return true;
    } else if (loc.getChar() == 'n') {
      loc.eatChar();
      value = '\n';
      return true;
    } else if (loc.getChar() == 'r') {
      loc.eatChar();
      value = '\r';
      return true;
    } else if (loc.getChar() == 't') {
      loc.eatChar();
      value = '\t';
      return true;
    } else if (loc.getChar() == 'u') {
      for (int i = 0; i < 4; i++) {
        value *= 16;
        loc.eatChar();
        n++;

        if (n >= length) {
          return false;
        } else if (loc.getChar() >= '0' && loc.getChar() <= '9') {
          value += loc.getChar() - '0';
        } else if (loc.getChar() >= 'a' && loc.getChar() <= 'f') {
          value += 10 + loc.getChar() - 'a';
        } else if (loc.getChar() >= 'A' && loc.getChar() <= 'F') {
          value += 10 + loc.getChar() - 'A';
        } else {
          return false;
        }
      }

      loc.eatChar();
      return true;
    } else if (loc.getChar() == 'U') {
      for (int i = 0; i < 8; i++) {
        value *= 16;
        loc.eatChar();
        n++;

        if (n >= length) {
          return false;
        } else if (loc.getChar() >= '0' && loc.getChar() <= '9') {
          value += loc.getChar() - '0';
        } else if (loc.getChar() >= 'a' && loc.getChar() <= 'f') {
          value += 10 + loc.getChar() - 'a';
        } else if (loc.getChar() >= 'A' && loc.getChar() <= 'F') {
          value += 10 + loc.getChar() - 'A';
        } else {
          return false;
        }
      }

      loc.eatChar();
      return true;
    } else if (loc.getChar() == 'v') {
      loc.eatChar();
      value = '\v';
      return true;
    } else if (loc.getChar() == 'x') {
      for (int i = 0; i < 2; i++) {
        value *= 16;
        loc.eatChar();
        n++;

        if (n >= length) {
          return false;
        } else if (loc.getChar() >= '0' && loc.getChar() <= '9') {
          value += loc.getChar() - '0';
        } else if (loc.getChar() >= 'a' && loc.getChar() <= 'f') {
          value += 10 + loc.getChar() - 'a';
        } else if (loc.getChar() >= 'A' && loc.getChar() <= 'F') {
          value += 10 + loc.getChar() - 'A';
        } else {
          return false;
        }
      }

      loc.eatChar();
      return true;
    } else if (loc.getChar() >= '0' && loc.getChar() <= '7') {
      value = loc.eatChar() - '0';
      n++;

      if (n >= length) {
        return true;
      } else if (loc.getChar() >= '0' && loc.getChar() <= '7') {
        value *= 8;
        value += loc.eatChar() - '0';
        n++;

        if (n >= length) {
          return true;
        } else if (loc.getChar() >= '0' && loc.getChar() <= '8') {
          value *= 8;
          value += loc.eatChar() - '0';
          n++;
          return true;
        } else {
          return true;
        }
      } else {
        return true;
      }
    } else {
      value = loc.eatChar();
      return true;
    }
  } else {
    value = loc.eatChar();
    return true;
  }
}
} // namespace

bool evalLiteralChar(const Range &range, char32_t &value) {
  value = '\0';

  Location i = range.getStart();
  size_t n = 0;

  if (n >= range.getLength()) {
    return false;
  }

  if (i.getChar() != '\'') {
    return false;
  }

  i.eatChar();
  n++;

  if (n >= range.getLength()) {
    return false;
  }

  if (evalLiteralCharHelper(i, range.getLength() - n, value)) {
    if (i.getChar() != '\'') {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool evalLiteralString8(const Range &range, std::string &value) {
  value = "";

  Location i = range.getStart();
  size_t n = 0;

  if (n >= range.getLength()) {
    return false;
  }

  if (i.getChar() != '\"') {
    return false;
  }

  i.eatChar();
  n++;

  bool endedCorrectly = false;

  while (i.getOffset() - range.getStart().getOffset() < range.getLength()) {
    if (i.getChar() == '\"') {
      endedCorrectly = true;
      break;
    } else {
      char32_t tmp;
      if (!evalLiteralCharHelper(
              i,
              range.getLength() -
                  (i.getOffset() - range.getStart().getOffset()),
              tmp)) {
        return false;
      }

      appendChar32ToString8(value, tmp);
    }
  }

  return endedCorrectly;
}

bool evalLiteralString16(const Range &range, std::u16string &value) {
  value = u"";

  Location i = range.getStart();
  size_t n = 0;

  if (n >= range.getLength()) {
    return false;
  }

  if (i.getChar() != '\"') {
    return false;
  }

  i.eatChar();
  n++;

  bool endedCorrectly = false;

  while (i.getOffset() - range.getStart().getOffset() < range.getLength()) {
    if (i.getChar() == '\"') {
      endedCorrectly = true;
      break;
    } else {
      char32_t tmp;
      if (!evalLiteralCharHelper(
              i,
              range.getLength() -
                  (i.getOffset() - range.getStart().getOffset()),
              tmp)) {
        return false;
      }

      appendChar32ToString16(value, tmp);
    }
  }

  return endedCorrectly;
}

bool evalLiteralString32(const Range &range, std::u32string &value) {
  value = U"";

  Location i = range.getStart();
  size_t n = 0;

  if (n >= range.getLength()) {
    return false;
  }

  if (i.getChar() != '\"') {
    return false;
  }

  i.eatChar();
  n++;

  bool endedCorrectly = false;

  while (i.getOffset() - range.getStart().getOffset() < range.getLength()) {
    if (i.getChar() == '\"') {
      endedCorrectly = true;
      break;
    } else {
      char32_t tmp;
      if (!evalLiteralCharHelper(
              i,
              range.getLength() -
                  (i.getOffset() - range.getStart().getOffset()),
              tmp)) {
        return false;
      }

      // appendChar32ToString8(value, tmp);
      value.push_back(tmp);
    }
  }

  return endedCorrectly;
}
} // namespace whiskey
