#ifndef __WHISKEY_Core_Types_HPP
#define __WHISKEY_Core_Types_HPP

#include <stdint.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;
typedef uint8_t UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;
typedef float Float32;
typedef double Float64;
typedef long double Real;

template <typename T>
int getNDigits(T value, int base = 10);
} // namespace whiskey

#include <whiskey/Core/Types.tpp>

#endif
