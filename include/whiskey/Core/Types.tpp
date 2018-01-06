namespace whiskey {
template<typename T> DigitCount getNDigits(T value, DigitBase base) {
	if (value == 0) {
    return 1;
  } else {
    unsigned int n = 0;
    while (value != 0) {
      value /= base;
      n++;
    }
    return n;
  }
}
}
