namespace whiskey {
template <typename T>
unsigned int getNDigits(T value, T base) {
  W_ASSERT_GT(
      base, static_cast<decltype(base)>(0), "Cannot get n digits in non-positive base " << base << ".");

  if (value == 0) {
    return 1;
  } else if (value < 0) {
    W_ASSERT_UNREACHABLE("Cannot get n digits in negative integer " << value
                                                                    << ".");
  } else {
    unsigned int n = 0;
    while (value != 0) {
      value /= static_cast<T>(base);
      n++;
    }
    return n;
  }
}
} // namespace whiskey
