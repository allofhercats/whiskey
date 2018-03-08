#ifndef __WHISKEY_Core_Assert_HPP
#define __WHISKEY_Core_Assert_HPP

#include <ostream>

#define _W_ASSERT_PRINT(desc, req) { \
  ::whiskey::printAssertPrefix(__FILE__, __LINE__); \
  ::whiskey::getAssertOStream() << desc; \
  ::whiskey::printAssertSuffix((req)); \
}

#define _W_ASSERT_PRINT_VALUE(label, text, value) { \
  ::whiskey::printAssertValue<decltype((value))>((label), text, (value)); \
}

#define _W_ASSERT_DIE() { \
  ::whiskey::dieOnAssertFail(); \
}

#define _W_ASSERT_COMPARE(lhs, rhs) ::whiskey::compareOnAssert<decltype((lhs)), decltype((rhs))>((lhs), (rhs))

#define W_ASSERT_UNREACHABLE(desc) { \
  _W_ASSERT_PRINT(desc, "Code is unreachable"); \
  _W_ASSERT_DIE(); \
}

#define W_ASSERT_TRUE(value, desc) { \
  bool _w_assertValue = static_cast<bool>(value); \
  if (!_w_assertValue) { \
    _W_ASSERT_PRINT(desc, "Value is true"); \
    _W_ASSERT_PRINT_VALUE("Value", #value, _w_assertValue ? "true" : "false"); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_FALSE(value, desc) { \
  bool _w_assertValue = static_cast<bool>(value); \
  if (_w_assertValue) { \
    _W_ASSERT_PRINT(desc, "Value is false"); \
    _W_ASSERT_PRINT_VALUE("Value", #value, _w_assertValue ? "true" : "false"); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_NONNULL(value, desc) { \
  decltype((value)) _w_assertValue = (value); \
  if (_w_assertValue == nullptr) { \
    _W_ASSERT_PRINT(desc, "Value is nonnull"); \
    _W_ASSERT_PRINT_VALUE("Value", #value, _w_assertValue); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_NULL(value, desc) { \
  decltype((value)) _w_assertValue = (value); \
  if (!(_w_assertValue == nullptr)) { \
    _W_ASSERT_PRINT(desc, "Value is null"); \
    _W_ASSERT_PRINT_VALUE("Value", #value, _w_assertValue); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_LT(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) < 0)) { \
    _W_ASSERT_PRINT(desc, "Lhs < Rhs"); \
    _W_ASSERT_PRINT_VALUE("Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE("Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_LE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) <= 0)) { \
    _W_ASSERT_PRINT(desc, "Lhs <= Rhs"); \
    _W_ASSERT_PRINT_VALUE("Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE("Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_GT(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) > 0)) { \
    _W_ASSERT_PRINT(desc, "Lhs > Rhs"); \
    _W_ASSERT_PRINT_VALUE("Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE("Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_GE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) >= 0)) { \
    _W_ASSERT_PRINT(desc, "Lhs >= Rhs"); \
    _W_ASSERT_PRINT_VALUE("Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE("Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_NE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) != 0)) { \
    _W_ASSERT_PRINT(desc, "Lhs != Rhs"); \
    _W_ASSERT_PRINT_VALUE("Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE("Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_EQ(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) == 0)) { \
    _W_ASSERT_PRINT(desc, "Lhs == Rhs"); \
    _W_ASSERT_PRINT_VALUE("Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE("Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

namespace whiskey {
std::ostream &getAssertOStream();
void setAssertOStream(std::ostream &os);

void printAssertPrefix(const char *file, unsigned int line);
void printAssertSuffix(const char *requirement);

template<typename T>
void printAssertValue(const char *label, const char *text, const T value);

[[noreturn]] void dieOnAssertFail();

template<typename T, typename U>
int compareOnAssert(const T lhs, const U rhs);
}

#include <whiskey/Core/Assert.tpp>

#endif
