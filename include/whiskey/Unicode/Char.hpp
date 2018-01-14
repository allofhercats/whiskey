#ifndef __WHISKEY_Core_Char_HPP
#define __WHISKEY_Core_Char_HPP

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Unicode/Endianness.hpp>

namespace whiskey {
typedef char Char8;
typedef char16_t Char16;
typedef char32_t Char32;

int getChar32MinWidth(Char32 value);
bool isValidUTF32Char(Char32 value);
bool isValidCharWidth(int value);
template<typename T>
size_t getStringLength(const T *src);
int getNAdditionalCharsUTF8(Char8 value);
int getNAdditionalCharsUTF16(Char16 value);
Char32 readCharUTF8(const Char8 *src, size_t &pos, size_t length);
Char32 readCharUTF16(const Char16 *src,
                     size_t &pos,
                     size_t length,
                     Endianness endianness = Endianness::Auto);
Char32 readCharUTF32(const Char32 *src,
                     size_t &pos,
                     size_t length,
                     Endianness endianness = Endianness::Auto);
template <typename T>
Char32 readCharUTF(const T *src,
                   size_t &pos,
                   size_t length,
                   Endianness endianness = Endianness::Auto);
void writeCharUTF8(Char8 *dst,
                   Char32 value,
                   size_t &pos,
                   size_t length);
void writeCharUTF16(Char16 *dst,
                    Char32 value,
                    size_t &pos,
                    size_t length,
                    Endianness endianness = Endianness::Auto);
void writeCharUTF32(Char32 *dst,
                    Char32 value,
                    size_t &pos,
                    size_t length,
                    Endianness endianness = Endianness::Auto);
template <typename T>
void writeCharUTF(T *dst,
                  Char32 value,
                  size_t &pos,
                  size_t length,
                  Endianness endianness = Endianness::Auto);
} // namespace whiskey

#include <whiskey/Unicode/Char.tpp>

#endif
