#ifndef __WHISKEY_Core_Assert_HPP
#define __WHISKEY_Core_Assert_HPP

#include <ostream>

#define _W_ASSERT_PRINT(mode, desc, req) { \
  ::whiskey::printAssertPrefix((mode), __FILE__, __LINE__); \
  ::whiskey::getAssertOStream((mode)) << desc; \
  ::whiskey::printAssertSuffix((mode), (req)); \
}

#define _W_ASSERT_PRINT_VALUE(mode, label, text, value) { \
  ::whiskey::printAssertValue<decltype((value))>((mode), (label), text, (value)); \
}

#define _W_ASSERT_DIE() { \
  _W_ASSERT_FAIL(::whiskey::AssertMode::Internal); \
  ::whiskey::failAssertDie(); \
}

#define _W_ASSERT_FAIL(mode) { \
  ::whiskey::failAssert((mode)); \
}

#define _W_ASSERT_COMPARE(lhs, rhs) ::whiskey::compareOnAssert<decltype((lhs)), decltype((rhs))>((lhs), (rhs))

#define W_ASSERT_UNREACHABLE(desc) { \
  _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Code is unreachable"); \
  _W_ASSERT_DIE(); \
}

#define W_ASSERT_TRUE(value, desc) { \
  bool _w_assertValue = static_cast<bool>(value); \
  if (!_w_assertValue) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Value is true"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Value", #value, _w_assertValue ? "true" : "false"); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_FALSE(value, desc) { \
  bool _w_assertValue = static_cast<bool>(value); \
  if (_w_assertValue) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Value is false"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Value", #value, _w_assertValue ? "true" : "false"); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_NONNULL(value, desc) { \
  decltype((value)) _w_assertValue = (value); \
  if (_w_assertValue == nullptr) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Value is nonnull"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Value", #value, _w_assertValue); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_NULL(value, desc) { \
  decltype((value)) _w_assertValue = (value); \
  if (!(_w_assertValue == nullptr)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Value is null"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Value", #value, _w_assertValue); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_LT(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) < 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Lhs < Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_LE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) <= 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Lhs <= Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_GT(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) > 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Lhs > Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_GE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) >= 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Lhs >= Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_NE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) != 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Lhs != Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_ASSERT_EQ(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) == 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Internal, desc, "Lhs == Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Internal, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_DIE(); \
  } \
}

#define W_TEST_ASSERT_UNREACHABLE(desc) { \
  _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Code is unreachable"); \
  _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
}

#define W_TEST_ASSERT_TRUE(value, desc) { \
  bool _w_assertValue = static_cast<bool>(value); \
  if (!_w_assertValue) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Value is true"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Value", #value, _w_assertValue ? "true" : "false"); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_FALSE(value, desc) { \
  bool _w_assertValue = static_cast<bool>(value); \
  if (_w_assertValue) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Value is false"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Value", #value, _w_assertValue ? "true" : "false"); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_NONNULL(value, desc) { \
  decltype((value)) _w_assertValue = (value); \
  if (_w_assertValue == nullptr) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Value is nonnull"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Value", #value, _w_assertValue); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_NULL(value, desc) { \
  decltype((value)) _w_assertValue = (value); \
  if (!(_w_assertValue == nullptr)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Value is null"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Value", #value, _w_assertValue); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_LT(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) < 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Lhs < Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_LE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) <= 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Lhs <= Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_GT(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) > 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Lhs > Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_GE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) >= 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Lhs >= Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_NE(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) != 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Lhs != Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

#define W_TEST_ASSERT_EQ(lhs, rhs, desc) { \
  decltype((lhs)) _w_assertLhs = (lhs); \
  decltype((rhs)) _w_assertRhs = (rhs); \
  if (!(_W_ASSERT_COMPARE(_w_assertLhs, _w_assertRhs) == 0)) { \
    _W_ASSERT_PRINT(::whiskey::AssertMode::Test, desc, "Lhs == Rhs"); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Lhs", #lhs, _w_assertLhs); \
    _W_ASSERT_PRINT_VALUE(::whiskey::AssertMode::Test, "Rhs", #rhs, _w_assertRhs); \
    _W_ASSERT_FAIL(::whiskey::AssertMode::Test); \
  } \
}

namespace whiskey {
enum class AssertMode {
  Internal,
  Test,

  First = Internal,
  Last = Test
};

extern const size_t assertModeCount;

std::ostream &getAssertOStream(AssertMode mode);
void setAssertOStream(AssertMode mode, std::ostream &os);

size_t getNAssertFailures(AssertMode mode);

void printAssertPrefix(AssertMode mode, const char *file, unsigned int line);
void printAssertSuffix(AssertMode mode, const char *requirement);

template<typename T>
void printAssertValue(AssertMode mode, const char *label, const char *text, const T value);

[[noreturn]] void failAssertDie();
void failAssert(AssertMode mode);

template<typename T, typename U>
int compareOnAssert(const T lhs, const U rhs);
}

#include <whiskey/Core/Assert.tpp>

#endif
