#ifndef __WHISKEY_Core_Types_HPP
#define __WHISKEY_Core_Types_HPP

#include <stdint.h>

namespace whiskey {
typedef int64_t Int;
typedef uint64_t UInt;
typedef long double Real;

typedef int32_t DigitCount;
typedef int32_t DigitBase;

template <typename T>
DigitCount getNDigits(T value, DigitBase base = 10);
} // namespace whiskey

#include <whiskey/Core/Types.tpp>

#endif
