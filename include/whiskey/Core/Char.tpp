namespace whiskey {
template <typename T>
Char32 readCharUTF(const T *src,
                   CharOffset &pos,
                   CharOffset length,
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
                  CharOffset &pos,
                  CharOffset length,
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
