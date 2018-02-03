#include <whiskey/Parsing/EvalLiterals.hpp>

// #include <whiskey/Core/PrintLiterals.hpp>
// #include <whiskey/Source/Range.hpp>

namespace whiskey {
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
bool evalLiteralCharHelper(std::string::const_iterator &i, std::string::const_iterator end, char &value) {
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
        } else if (*i >= '0' && *i <= '8') {
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

bool evalLiteralChar(const std::string &text, char &value) {
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
      char tmp;
      if (!evalLiteralCharHelper(
              i,
              text.cend(),
              tmp)) {
        return false;
      }

      value.push_back(tmp);
    }
  }

  return endedCorrectly;
}
} // namespace whiskey
