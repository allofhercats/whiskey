#include <whiskey/Unicode/Char.hpp>

#include <iostream>

namespace whiskey {
int getChar32MinWidth(Char32 value) {
  if ((value & 0xff) == value) {
    return 1;
  } else if ((value & 0xffff) == value) {
    return 2;
  } else {
    return 4;
  }
}

bool isValidUTF32Char(Char32 value) {
  return value < 0xd800 || value > 0xdfff;
}

bool isValidCharWidth(int value) {
  return value == 1 || value == 2 || value == 4;
}

int getNAdditionalCharsUTF8(Char8 value) {
  if ((value & 0x80) == 0) {
    return 0;
  } else if ((value & 0xe0) == 0xc0) {
    return 1;
  } else if ((value & 0xf0) == 0xe0) {
    return 2;
  } else if ((value & 0xf8) == 0xf0) {
    return 3;
  } else {
    W_ASSERT_UNREACHABLE("Invalid UTF-8 character.");
  }
}

int getNAdditionalCharsUTF16(Char16 value) {
  if ((value & 0xfc00) != 0xd800) {
    return 0;
  } else {
    return 1;
  }
}

Char32 readCharUTF8(const Char8 *src, size_t &pos, size_t length) {
  W_ASSERT_NONNULL(src, "Cannot read character from null string.");
  W_ASSERT_GE(pos, 0, "Cannot read before start of buffer.");
  W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
  W_ASSERT_GE(length, 0, "Cannot read buffer with negative length.");

  if ((src[pos] & 0x80) == 0) {
    Char32 rtn = src[pos] & 0x7f;
    pos++;
    return rtn;
  } else if ((src[pos] & 0xe0) == 0xc0) {
    Char32 rtn = (src[pos] & 0x1f) << 6;
    pos++;

    W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
    rtn |= src[pos] & 0x3f;
    pos++;

    W_ASSERT_GE(rtn, 128, "Invalid UTF-8 character.");

    return rtn;
  } else if ((src[pos] & 0xf0) == 0xe0) {
    Char32 rtn = (src[pos] & 0x0f) << 6;
    pos++;

    W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
    rtn |= src[pos] & 0x3f;
    pos++;

    W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
    rtn <<= 6;
    rtn |= src[pos] & 0x3f;
    pos++;

    W_ASSERT_GE(rtn, 128, "Invalid UTF-8 character.");

    return rtn;
  } else if ((src[pos] & 0xf8) == 0xf0) {
    Char32 rtn = (src[pos] & 0x07) << 6;
    pos++;

    W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
    rtn |= src[pos] & 0x3f;
    pos++;

    W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
    rtn <<= 6;
    rtn |= src[pos] & 0x3f;
    pos++;

    W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
    rtn <<= 6;
    rtn |= src[pos] & 0x3f;
    pos++;

    W_ASSERT_GE(rtn, 128, "Invalid UTF-8 character.");

    return rtn;
  } else {
    W_ASSERT_UNREACHABLE("Invalid UTF-8 character.");
  }
}

Char32 readCharUTF16(const Char16 *src,
                     size_t &pos,
                     size_t length,
                     Endianness endianness) {
  W_ASSERT_NONNULL(src, "Cannot read character from null string.");
  W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
  W_ASSERT_GE(pos, 0, "Cannot read before start of buffer.");
  W_ASSERT_GE(length, 0, "Cannot read buffer with negative length.");

  Char16 buf[2];

  W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
  buf[0] = src[pos++];
  if ((buf[0] & 0xfc00) != 0xd800) {
    return buf[0];
  }

  W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
  buf[1] = src[pos++];
  W_ASSERT_TRUE((buf[1] & 0xfc00) == 0xdc00, "Invalid UTF-16 character.");

  if (endianness != Endianness::Auto && getSystemEndianness() != endianness) {
    return (((buf[1] & 0x03ff) << 10) | (buf[0] & 0x03ff)) + 0x10000;
  } else {
    return (((buf[0] & 0x03ff) << 10) | (buf[1] & 0x03ff)) + 0x10000;
  }
}

Char32 readCharUTF32(const Char32 *src,
                     size_t &pos,
                     size_t length,
                     Endianness endianness) {
  W_ASSERT_NONNULL(src, "Cannot read character from null string.");
  W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");
  W_ASSERT_GE(pos, 0, "Cannot read before start of buffer.");
  W_ASSERT_GE(length, 0, "Cannot read buffer with negative length.");

  if (endianness != Endianness::Auto && getSystemEndianness() != endianness) {
    return swapByteOrder(src[pos++]);
  } else {
    return src[pos++];
  }
}

void writeCharUTF8(Char8 *dst,
                   Char32 value,
                   size_t &pos,
                   size_t length) {
  W_ASSERT_NONNULL(dst, "Cannot write character from null string.");
  W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
  W_ASSERT_GE(pos, 0, "Cannot write before start of buffer.");
  W_ASSERT_GE(length, 0, "Cannot write buffer with negative length.");

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
    W_ASSERT_UNREACHABLE(
        "Cannot convert code point greater than 0x10ffff to UTF-8.");
  }
}

void writeCharUTF16(Char16 *dst,
                    Char32 value,
                    size_t &pos,
                    size_t length,
                    Endianness endianness) {
  W_ASSERT_NONNULL(dst, "Cannot write character from null string.");
  W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
  W_ASSERT_GE(pos, 0, "Cannot write before start of buffer.");
  W_ASSERT_GE(length, 0, "Cannot write buffer with negative length.");

  if (endianness != Endianness::Auto && getSystemEndianness() != endianness) {
    value = swapByteOrder(value);
  }

  if (value <= 0xdf77) {
    dst[pos] = value & 0xffff;
    pos++;
  } else if (value <= 0xdfff) {
    W_ASSERT_UNREACHABLE(
        "Cannot convert codepoint in 0xd800 to 0xdfff range to UTF-16.");
  } else if (value <= 0xffff) {
    dst[pos] = value & 0xffff;
    pos++;
  } else if (value <= 0x10ffff) {
    dst[pos] = 0xd800 | (((value - 0x10000) >> 10) & 0x03ff);
    pos++;

    W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
    dst[pos] = 0xdc00 | ((value - 0x10000) & 0x03ff);
    pos++;
  } else {
    W_ASSERT_UNREACHABLE(
        "Cannot convert code point greater than 0x10ffff to UTF-16.");
  }
}

void writeCharUTF32(Char32 *dst,
                    Char32 value,
                    size_t &pos,
                    size_t length,
                    Endianness endianness) {
  W_ASSERT_NONNULL(dst, "Cannot write character from null string.");
  W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
  W_ASSERT_GE(pos, 0, "Cannot write before start of buffer.");
  W_ASSERT_GE(length, 0, "Cannot write buffer with negative length.");

  if (endianness != Endianness::Auto && getSystemEndianness() != endianness) {
    value = swapByteOrder(value);
  }

  dst[pos++] = value;
}
} // namespace whiskey
