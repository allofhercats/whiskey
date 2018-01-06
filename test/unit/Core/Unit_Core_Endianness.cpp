#include <gtest/gtest.h>

#include <whiskey/Core/Endianness.hpp>

using namespace whiskey;

TEST(Unit_Core_Endianness, DetectSystem) {
	getSystemEndianness();
}

TEST(Unit_Core_Endianness, GetNthByte_UInt8) {
	uint8_t value = 0xf0;
	
	ASSERT_EQ(getNthByte(value, 0), 0xf0);

	ASSERT_DEATH({
		getNthByte(value, -1);
	}, "");

	ASSERT_DEATH({
		getNthByte(value, 1);
	}, "");
}

TEST(Unit_Core_Endianness, GetNthByte_UInt16) {
	uint16_t value = 0;

	((uint8_t *)&value)[0] = 0xf0;
	((uint8_t *)&value)[1] = 0xe0;

	ASSERT_EQ(getNthByte(value, 0), 0xf0);
	ASSERT_EQ(getNthByte(value, 1), 0xe0);

	ASSERT_DEATH({
		getNthByte(value, -1);
	}, "");

	ASSERT_DEATH({
		getNthByte(value, 2);
	}, "");
}

TEST(Unit_Core_Endianness, GetNthByte_UInt32) {
	uint32_t value = 0;

	((uint8_t *)&value)[0] = 0xf0;
	((uint8_t *)&value)[1] = 0xe0;
	((uint8_t *)&value)[2] = 0xd0;
	((uint8_t *)&value)[3] = 0xc0;

	ASSERT_EQ(getNthByte(value, 0), 0xf0);
	ASSERT_EQ(getNthByte(value, 1), 0xe0);
	ASSERT_EQ(getNthByte(value, 2), 0xd0);
	ASSERT_EQ(getNthByte(value, 3), 0xc0);

	ASSERT_DEATH({
		getNthByte(value, -1);
	}, "");

	ASSERT_DEATH({
		getNthByte(value, 4);
	}, "");
}

TEST(Unit_Core_Endianness, GetNthByte_UInt64) {
	uint64_t value = 0;

	((uint8_t *)&value)[0] = 0xf0;
	((uint8_t *)&value)[1] = 0xe0;
	((uint8_t *)&value)[2] = 0xd0;
	((uint8_t *)&value)[3] = 0xc0;
	((uint8_t *)&value)[4] = 0xb0;
	((uint8_t *)&value)[5] = 0xa0;
	((uint8_t *)&value)[6] = 0x90;
	((uint8_t *)&value)[7] = 0x80;

	ASSERT_EQ(getNthByte(value, 0), 0xf0);
	ASSERT_EQ(getNthByte(value, 1), 0xe0);
	ASSERT_EQ(getNthByte(value, 2), 0xd0);
	ASSERT_EQ(getNthByte(value, 3), 0xc0);
	ASSERT_EQ(getNthByte(value, 4), 0xb0);
	ASSERT_EQ(getNthByte(value, 5), 0xa0);
	ASSERT_EQ(getNthByte(value, 6), 0x90);
	ASSERT_EQ(getNthByte(value, 7), 0x80);

	ASSERT_DEATH({
		getNthByte(value, -1);
	}, "");

	ASSERT_DEATH({
		getNthByte(value, 8);
	}, "");
}

TEST(Unit_Core_Endianness, SwapByteOrder_UInt8) {
	uint8_t value = 0xf0;
	
	ASSERT_EQ(swapByteOrder(value), 0xf0);
}

TEST(Unit_Core_Endianness, SwapByteOrder_UInt16) {
	uint16_t value = 0;

	((uint8_t *)&value)[0] = 0xf0;
	((uint8_t *)&value)[1] = 0xe0;

	uint16_t swapped = swapByteOrder(value);

	ASSERT_EQ(((const uint8_t *)&swapped)[0], 0xe0);
	ASSERT_EQ(((const uint8_t *)&swapped)[1], 0xf0);
}

TEST(Unit_Core_Endianness, SwapByteOrder_UInt32) {
	uint32_t value = 0;

	((uint8_t *)&value)[0] = 0xf0;
	((uint8_t *)&value)[1] = 0xe0;
	((uint8_t *)&value)[2] = 0xd0;
	((uint8_t *)&value)[3] = 0xc0;

	uint32_t swapped = swapByteOrder(value);

	ASSERT_EQ(((const uint8_t *)&swapped)[0], 0xc0);
	ASSERT_EQ(((const uint8_t *)&swapped)[1], 0xd0);
	ASSERT_EQ(((const uint8_t *)&swapped)[2], 0xe0);
	ASSERT_EQ(((const uint8_t *)&swapped)[3], 0xf0);
}

TEST(Unit_Core_Endianness, SwapByteOrder_UInt64) {
	uint64_t value = 0;

	((uint8_t *)&value)[0] = 0xf0;
	((uint8_t *)&value)[1] = 0xe0;
	((uint8_t *)&value)[2] = 0xd0;
	((uint8_t *)&value)[3] = 0xc0;
	((uint8_t *)&value)[4] = 0xb0;
	((uint8_t *)&value)[5] = 0xa0;
	((uint8_t *)&value)[6] = 0x90;
	((uint8_t *)&value)[7] = 0x80;

	uint64_t swapped = swapByteOrder(value);

	ASSERT_EQ(((const uint8_t *)&swapped)[0], 0x80);
	ASSERT_EQ(((const uint8_t *)&swapped)[1], 0x90);
	ASSERT_EQ(((const uint8_t *)&swapped)[2], 0xa0);
	ASSERT_EQ(((const uint8_t *)&swapped)[3], 0xb0);
	ASSERT_EQ(((const uint8_t *)&swapped)[4], 0xc0);
	ASSERT_EQ(((const uint8_t *)&swapped)[5], 0xd0);
	ASSERT_EQ(((const uint8_t *)&swapped)[6], 0xe0);
	ASSERT_EQ(((const uint8_t *)&swapped)[7], 0xf0);
}
