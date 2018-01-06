#ifndef __WHISKEY_Core_Assert_HPP
#define __WHISKEY_Core_Assert_HPP

#include <stdint.h>

#include <ostream>

#define _W_ASSERT_PRINT_REASON(reason) { \
  ::whiskey::printAssertReasonPre(); \
  ::whiskey::getAssertStream() << reason; \
  ::whiskey::printAssertReasonPost(); \
}

#define W_ASSERT_UNREACHABLE(reason)                        \
  {                                                         \
    ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected code to be unreachable"); \
    _W_ASSERT_PRINT_REASON(reason);                         \
    ::whiskey::dieOnAssertFail();                                        \
  }

#define W_ASSERT_TRUE(arg0, reason)                                        \
  {                                                                        \
    ::whiskey::AssertBool _w_arg0Value = (::whiskey::AssertBool)(arg0);                  \
    if (!_w_arg0Value) {                                                   \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected value to be true");                    \
      ::whiskey::printAssertValueBool("actual", _w_arg0Value, #arg0); \
      _W_ASSERT_PRINT_REASON(reason);                                      \
      ::whiskey::dieOnAssertFail();                                                     \
    }                                                                      \
  }

#define W_ASSERT_FALSE(arg0, reason)                                       \
  {                                                                        \
    ::whiskey::AssertBool _w_arg0Value = (::whiskey::AssertBool)(arg0);                  \
    if (_w_arg0Value) {                                                    \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected value to be false");                   \
      ::whiskey::printAssertValueBool("actual", _w_arg0Value, #arg0); \
      _W_ASSERT_PRINT_REASON(reason);                                      \
      ::whiskey::dieOnAssertFail();                                                     \
    }                                                                      \
  }

#define W_ASSERT_NULL(arg0, reason)                                        \
  {                                                                        \
    ::whiskey::AssertPointer _w_arg0Value = (::whiskey::AssertPointer)(arg0);            \
    if (_w_arg0Value != nullptr) {                                         \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected value to be null");                    \
      ::whiskey::printAssertValuePointer("actual", _w_arg0Value, #arg0); \
      _W_ASSERT_PRINT_REASON(reason);                                      \
      ::whiskey::dieOnAssertFail();                                                     \
    }                                                                      \
  }

#define W_ASSERT_NONNULL(arg0, reason)                                     \
  {                                                                        \
    ::whiskey::AssertPointer _w_arg0Value = (::whiskey::AssertPointer)(arg0);            \
    if (_w_arg0Value == nullptr) {                                         \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected value to not be null");                \
      ::whiskey::printAssertValuePointer("actual", _w_arg0Value, #arg0); \
      _W_ASSERT_PRINT_REASON(reason);                                      \
      ::whiskey::dieOnAssertFail();                                                     \
    }                                                                      \
  }

#define W_ASSERT_LT(arg0, arg1, reason)                                 \
  {                                                                     \
    ::whiskey::AssertInt _w_arg0Value = (::whiskey::AssertInt)(arg0);                 \
    ::whiskey::AssertInt _w_arg1Value = (::whiskey::AssertInt)(arg1);                 \
    if (!(_w_arg0Value < _w_arg1Value)) {                               \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be less than rhs");          \
      ::whiskey::printAssertValueInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                   \
      ::whiskey::dieOnAssertFail();                                                  \
    }                                                                   \
  }

#define W_ASSERT_LE(arg0, arg1, reason)                                    \
  {                                                                        \
    ::whiskey::AssertInt _w_arg0Value = (::whiskey::AssertInt)(arg0);                    \
    ::whiskey::AssertInt _w_arg1Value = (::whiskey::AssertInt)(arg1);                    \
    if (!(_w_arg0Value <= _w_arg1Value)) {                                 \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be less than or equal to rhs"); \
      ::whiskey::printAssertValueInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                      \
      ::whiskey::dieOnAssertFail();                                                     \
    }                                                                      \
  }

#define W_ASSERT_GT(arg0, arg1, reason)                                 \
  {                                                                     \
    ::whiskey::AssertInt _w_arg0Value = (::whiskey::AssertInt)(arg0);                 \
    ::whiskey::AssertInt _w_arg1Value = (::whiskey::AssertInt)(arg1);                 \
    if (!(_w_arg0Value > _w_arg1Value)) {                               \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be greater than rhs");       \
      ::whiskey::printAssertValueInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                   \
      ::whiskey::dieOnAssertFail();                                                  \
    }                                                                   \
  }

#define W_ASSERT_GE(arg0, arg1, reason)                                       \
  {                                                                           \
    ::whiskey::AssertInt _w_arg0Value = (::whiskey::AssertInt)(arg0);                       \
    ::whiskey::AssertInt _w_arg1Value = (::whiskey::AssertInt)(arg1);                       \
    if (!(_w_arg0Value >= _w_arg1Value)) {                                    \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be greater than or equal to rhs"); \
      ::whiskey::printAssertValueInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                         \
      ::whiskey::dieOnAssertFail();                                                        \
    }                                                                         \
  }

#define W_ASSERT_ULT(arg0, arg1, reason)                                \
  {                                                                     \
    ::whiskey::AssertUInt _w_arg0Value = (::whiskey::AssertUInt)(arg0);               \
    ::whiskey::AssertUInt _w_arg1Value = (::whiskey::AssertUInt)(arg1);               \
    if (!(_w_arg0Value < _w_arg1Value)) {                               \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be less than rhs");          \
      ::whiskey::printAssertValueUInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueUInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                   \
      ::whiskey::dieOnAssertFail();                                                  \
    }                                                                   \
  }

#define W_ASSERT_ULE(arg0, arg1, reason)                                   \
  {                                                                        \
    ::whiskey::AssertUInt _w_arg0Value = (::whiskey::AssertUInt)(arg0);                  \
    ::whiskey::AssertUInt _w_arg1Value = (::whiskey::AssertUInt)(arg1);                  \
    if (!(_w_arg0Value <= _w_arg1Value)) {                                 \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be less than or equal to rhs"); \
      ::whiskey::printAssertValueUInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueUInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                      \
      ::whiskey::dieOnAssertFail();                                                     \
    }                                                                      \
  }

#define W_ASSERT_UGT(arg0, arg1, reason)                                \
  {                                                                     \
    ::whiskey::AssertUInt _w_arg0Value = (::whiskey::AssertUInt)(arg0);               \
    ::whiskey::AssertUInt _w_arg1Value = (::whiskey::AssertUInt)(arg1);               \
    if (!(_w_arg0Value > _w_arg1Value)) {                               \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be greater than rhs");       \
      ::whiskey::printAssertValueUInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueUInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                   \
      ::whiskey::dieOnAssertFail();                                                  \
    }                                                                   \
  }

#define W_ASSERT_UGE(arg0, arg1, reason)                                      \
  {                                                                           \
    ::whiskey::AssertUInt _w_arg0Value = (::whiskey::AssertUInt)(arg0);                     \
    ::whiskey::AssertUInt _w_arg1Value = (::whiskey::AssertUInt)(arg1);                     \
    if (!(_w_arg0Value >= _w_arg1Value)) {                                    \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected lhs to be greater than or equal to rhs"); \
      ::whiskey::printAssertValueUInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueUInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                         \
      ::whiskey::dieOnAssertFail();                                                        \
    }                                                                         \
  }

#define W_ASSERT_NE(arg0, arg1, reason)                                 \
  {                                                                     \
    ::whiskey::AssertInt _w_arg0Value = (::whiskey::AssertInt)(arg0);                 \
    ::whiskey::AssertInt _w_arg1Value = (::whiskey::AssertInt)(arg1);                 \
    if (!(_w_arg0Value != _w_arg1Value)) {                              \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected values to not be equal");           \
      ::whiskey::printAssertValueUInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueUInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                   \
      ::whiskey::dieOnAssertFail();                                                  \
    }                                                                   \
  }

#define W_ASSERT_EQ(arg0, arg1, reason)                                 \
  {                                                                     \
    ::whiskey::AssertInt _w_arg0Value = (::whiskey::AssertInt)(arg0);                 \
    ::whiskey::AssertInt _w_arg1Value = (::whiskey::AssertInt)(arg1);                 \
    if (!(_w_arg0Value == _w_arg1Value)) {                              \
      ::whiskey::printAssertMessage(__FILE__, __LINE__, "expected values to be equal");               \
      ::whiskey::printAssertValueUInt("lhs", _w_arg0Value, #arg0); \
      ::whiskey::printAssertValueUInt("rhs", _w_arg1Value, #arg1); \
      _W_ASSERT_PRINT_REASON(reason);                                   \
      ::whiskey::dieOnAssertFail();                                                  \
    }                                                                   \
  }

namespace whiskey {
typedef bool AssertBool;
typedef void *AssertPointer;
typedef int64_t AssertInt;
typedef uint64_t AssertUInt;

std::ostream &getAssertStream();
void setAssertStream(std::ostream &os);

void printAssertMessage(const char *file, int line, const char *desc);
void printAssertReasonPre();
void printAssertReasonPost();
[[noreturn]] void dieOnAssertFail();
void printAssertValueBool(const char *label, AssertBool value, const char *text);
void printAssertValuePointer(const char *label, AssertPointer value, const char *text);
void printAssertValueInt(const char *label, AssertInt value, const char *text);
void printAssertValueUInt(const char *label, AssertUInt value, const char *text);
} // namespace whiskey

#endif
