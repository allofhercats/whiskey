namespace whiskey {
template <typename T>
uint8_t getNthByte(T value, int n) {
  W_ASSERT_GE(n, 0, "Cannot access byte at negative index.");
  W_ASSERT_LT(n, sizeof(T), "Cannot access byte past end of value.");
  return (value >> (n * 8)) & 0xff;
}

template <typename T>
T swapByteOrder(T value) {
  if (sizeof(T) == 1) {
    return value;
  } else if (sizeof(T) == 2) {
    return (T)swapByteOrder16((uint16_t)value);
  } else if (sizeof(T) == 4) {
    return (T)swapByteOrder32((uint32_t)value);
  } else if (sizeof(T) == 8) {
    return (T)swapByteOrder64((uint64_t)value);
  } else {
    W_ASSERT_UNREACHABLE(
        "Cannot swap byte order of value that is not 1, 2, or 4 byte integer.");
  }
}
} // namespace whiskey
