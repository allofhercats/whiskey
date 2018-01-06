#include <whiskey/Core/Endianness.hpp>

namespace whiskey {
Endianness getSystemEndianness() {
	const uint32_t n = 1;
	const uint8_t *p = (const uint8_t *)&n;
	if ((p[0] == 0 && p[1] == 0) && (p[2] == 0 && p[3] == 1)) {
		return Endianness::Little;
	} else if ((p[0] == 1 && p[1] == 0) && (p[2] == 0 && p[3] == 0)) {
		return Endianness::Big;
	} else {
		W_ASSERT_UNREACHABLE("Cannot detect system endianness.");
	}
}

uint16_t swapByteOrder16(uint16_t value) {
	return (uint16_t)getNthByte(value, 1)
			| (uint16_t)getNthByte(value, 0) << 8;
}

uint32_t swapByteOrder32(uint32_t value) {
	return (uint32_t)getNthByte(value, 3)
			| (uint32_t)getNthByte(value, 2) << 8
			| (uint32_t)getNthByte(value, 1) << 16
			| (uint32_t)getNthByte(value, 0) << 24;
}

uint64_t swapByteOrder64(uint64_t value) {
	return (uint64_t)getNthByte(value, 7)
			| (uint64_t)getNthByte(value, 6) << 8
			| (uint64_t)getNthByte(value, 5) << 16
			| (uint64_t)getNthByte(value, 4) << 24
			| (uint64_t)getNthByte(value, 3) << 32
			| (uint64_t)getNthByte(value, 2) << 40
			| (uint64_t)getNthByte(value, 1) << 48
			| (uint64_t)getNthByte(value, 0) << 56;
}
}
