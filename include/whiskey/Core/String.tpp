namespace whiskey {
template <typename T>
String::Length String::getLength(const T *value) {
  if (value == nullptr) {
    return 0;
  } else {
    Length n = 0;
    while (*value != 0) {
      n++;
      value++;
    }
    return n;
  }
}

template <typename T>
Char32 String::readCharFromString(const T *src,
                                  String::Length &pos,
                                  String::Length length) {
  W_ASSERT_LT(pos, length, "Cannot read past end of buffer.");

  if (sizeof(T) == 1) {
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
    }
  } else if (sizeof(T) == 2) {
    if (src[pos] - 0xd800 < 2048) {
      Char32 rtn = src[pos];
      pos++;
      return rtn;
    } else {
      W_ASSERT_TRUE(
          (src[pos] & 0xfffffc00) == 0xd800,
          "First 2-byte char in 4-byte codepoint must be high surrogate.");
      Char32 rtn = src[pos] << 10;
      pos++;
      W_ASSERT_LT(
          pos,
          length,
          "High surrogate 2-byte char expects low surrogate, not end of string.");
      W_ASSERT_TRUE(
          (src[pos] & 0xfffffc00) == 0xdc00,
          "First 2-byte char in 4-byte codepoint must be high surrogate.");
      rtn += src[pos] - 0x35fdc00;
      pos++;
      return rtn;
    }
  } else if (sizeof(T) == 4) {
    if (pos < length) {
      return src[pos++];
    } else {
      return 0;
    }
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << sizeof(T) << ".");
  }
}

template <typename T>
void String::writeCharToString(Char32 chr,
                               T *dst,
                               String::Length &pos,
                               String::Length length) {
  W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
  if (sizeof(T) == 1) {
    if (chr <= 0x7f) {
      dst[pos] = chr;
      pos++;
    } else if (chr <= 0x7ff) {
      dst[pos] = 0xc0 | (chr >> 6);
      pos++;

      W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
      dst[pos] = 0x80 | (chr & 0x3f);
      pos++;
    } else if (chr <= 0xffff) {
      dst[pos] = 0xe0 | (chr >> 12);
      pos++;

      W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
      dst[pos] = 0x80 | ((chr >> 6) & 0x3f);
      pos++;

      W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
      dst[pos] = 0x80 | (chr & 0x3f);
      pos++;
    } else if (chr <= 0x10ffff) {
      dst[pos] = 0xf0 | (chr >> 18);
      pos++;

      W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
      dst[pos] = 0x80 | ((chr >> 12) & 0x3f);
      pos++;

      W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
      dst[pos] = 0x80 | ((chr >> 6) & 0x3f);
      pos++;

      W_ASSERT_LT(pos, length, "Cannot write past end of buffer.");
      dst[pos] = 0x80 | (chr & 0x3f);
      pos++;
    } else {
      W_ASSERT_UNREACHABLE(
          "Cannot convert code point greater than 0x10ffff to UTF-8.");
    }
  } else if (sizeof(T) == 2) {
    int32_t casted = pos;
    // UBool error = false;
    // U16_APPEND((uint16_t *)dst, casted, length, chr, error);
    // W_ASSERT_FALSE(error, "Error while appending char.");
    pos = casted;
  } else if (sizeof(T) == 4) {
    dst[pos++] = chr;
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << sizeof(T) << ".");
  }
}
} // namespace whiskey
