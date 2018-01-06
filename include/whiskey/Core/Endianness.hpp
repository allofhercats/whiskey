#ifndef __WHISKEY_Core_Endianness_HPP
#define __WHISKEY_Core_Endianness_HPP

#include <stdint.h>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
enum class Endianness { Auto, Big, Little };

Endianness getSystemEndianness();
template <typename T>
uint8_t getNthByte(T value, int n);
uint16_t swapByteOrder16(uint16_t value);
uint32_t swapByteOrder32(uint32_t value);
uint64_t swapByteOrder64(uint64_t value);
template <typename T>
T swapByteOrder(T value);
} // namespace whiskey

#include <whiskey/Core/Endianness.tpp>

#endif
