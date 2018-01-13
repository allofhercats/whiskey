namespace whiskey {
template <typename T>
size_t getStringLength(const T *value) {
  if (value == nullptr) {
    return 0;
  } else {
    size_t n = 0;
    while (*value != 0) {
      n++;
      value++;
    }
    return n;
  }
}

template <typename T>
Char32 readCharUTF(const T *src,
                   size_t &pos,
                   size_t length,
                   Endianness endianness) {
  if (sizeof(T) == 1) {
    return readCharUTF8((const Char8 *)src, pos, length);
  } else if (sizeof(T) == 2) {
    return readCharUTF16((const Char16 *)src, pos, length, endianness);
  } else if (sizeof(T) == 4) {
    return readCharUTF32((const Char32 *)src, pos, length, endianness);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << sizeof(T) << ".");
  }
}

template <typename T>
void writeCharUTF(T *dst,
                  Char32 value,
                  size_t &pos,
                  size_t length,
                  Endianness endianness) {
  if (sizeof(T) == 1) {
    return writeCharUTF8((Char8 *)dst, value, pos, length);
  } else if (sizeof(T) == 2) {
    return writeCharUTF16((Char16 *)dst, value, pos, length, endianness);
  } else if (sizeof(T) == 4) {
    return writeCharUTF32((Char32 *)dst, value, pos, length, endianness);
  } else {
    W_ASSERT_UNREACHABLE("Unsupported char width " << sizeof(T) << ".");
  }
}
} // namespace whiskey
