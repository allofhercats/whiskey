// #include "Module.inc"

#include <whiskey/Core/Char.hpp>

namespace whiskey {
bool isValidUTF32Char(Char32 value) {
	return value < 0xd800 || value > 0xdfff;
}

Char32 readNextUTF8(const Char8 *src, CharOffset &pos, CharOffset length) {
	W_ASSERT_NONNULL(src, "Cannot read character from null string.");
	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
	
	if ((src[pos] & 0x80) == 0) {
		Char32 rtn = src[pos];
		pos++;
		return rtn;
	} else if ((src[pos] & 0xe0) == 0xc0) {
		Char32 rtn = (src[pos] & 0x1f) << 6;
		pos++;

		W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
		rtn |= src[pos];
		pos++;

		W_ASSERT_LT(rtn, 128, "Invalid UTF-8 character.");

		return rtn;
	} else if ((src[pos] & 0xf0) == 0xe0) {
		Char32 rtn = (src[pos] & 0x1f) << 6;
		pos++;

		W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
		rtn |= src[pos];
		pos++;

		W_ASSERT_LT(rtn, 128, "Invalid UTF-8 character.");

		return rtn;
	} else {
		W_ASSERT_UNREACHABLE("Invalid UTF-8 character.");
	}
}

Char32 readNextUTF16(const Char16 *src, CharOffset &pos, CharOffset length) {
	W_ASSERT_NONNULL(src, "Cannot read character from null string.");
	
	Char16 buf[2];

	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
	buf[0] = src[pos++];
	if ((buf[0] & 0xfc00) != 0xd800) {
		return buf[0];
	}

	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
	buf[1] = src[pos++];
	W_ASSERT_TRUE((buf[1] & 0xfc00) == 0xdc00, "Invalid UTF-16 character.");

	return ((buf[0] & 0x03ff) << 10) | (buf[1] & 0x03ff);
}

Char32 readCharUTF32(const Char32 *src, CharOffset &pos, CharOffset length) {
	W_ASSERT_NONNULL(src, "Cannot read character from null string.");
	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
	return src[pos++];
}

void writeCharUTF8(Char8 *dst, Char32 value, CharOffset &pos, CharOffset length) {
	W_ASSERT_NONNULL(dst, "Cannot read character from null string.");
	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");

	if (value <= 0x7f) {
		dst[pos] = value;
		pos++;
	} else if (value <= 0x7ff) {
		dst[pos] = 0xc0 | (value >> 6);
		pos++;
		
		W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
		dst[pos] = 0x80 | (value & 0x3f);
		pos++;
	} else if (value <= 0xffff) {
		dst[pos] = 0xe0 | (value >> 12);
		pos++;

		W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
		dst[pos] = 0x80 | ((value >> 6) & 0x3f);
		pos++;

		W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
		dst[pos] = 0x80 | (value & 0x3f);
		pos++;
	} else if (value <= 0x10ffff) {
		dst[pos] = 0xf0 | (value >> 18);
		pos++;

		W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
		dst[pos] = 0x80 | ((value >> 12) & 0x3f);
		pos++;

		W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
		dst[pos] = 0x80 | ((value >> 6) & 0x3f);
		pos++;

		W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
		dst[pos] = 0x80 | (value & 0x3f);
		pos++;
	} else {
		W_ASSERT_UNREACHABLE("Cannot convert code point greater than 0x10ffff to UTF-8.");
	}
}

void writeCharUTF16(Char16 *dst, Char32 value, CharOffset &pos, CharOffset length) {
	W_ASSERT_NONNULL(dst, "Cannot read character from null string.");
	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
}

void writeCharUTF32(Char32 *dst, Char32 value, CharOffset &pos, CharOffset length) {
	W_ASSERT_NONNULL(dst, "Cannot read character from null string.");
	W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
	
	dst[pos++] = value;
}
}
