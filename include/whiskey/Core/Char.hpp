#ifndef __WHISKEY_Core_Char_HPP
#define __WHISKEY_Core_Char_HPP

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
typedef char Char8;
typedef char16_t Char16;
typedef char32_t Char32;

typedef int32_t CharOffset;

bool isValidUTF32Char(Char32 value);
Char32 readCharUTF8(const Char8 *src, CharOffset &pos, CharOffset length);
Char32 readCharUTF16(const Char16 *src, CharOffset &pos, CharOffset length);
Char32 readCharUTF32(const Char32 *src, CharOffset &pos, CharOffset length);
template<typename T>
Char32 readCharUTF(const T *src, CharOffset &pos, CharOffset length);
void writeCharUTF8(Char8 *dst, Char32 value, CharOffset &pos, CharOffset length);
void writeCharUTF16(Char16 *dst, Char32 value, CharOffset &pos, CharOffset length);
void writeCharUTF32(Char32 *dst, Char32 value, CharOffset &pos, CharOffset length);
template<typename T>
void writeCharUTF(T *dst, Char32 value, CharOffset &pos, CharOffset length);
} // namespace whiskey

#include <whiskey/Core/Char.tpp>

#endif
