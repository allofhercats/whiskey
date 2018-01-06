namespace whiskey {
template <typename T>
void LiteralPrinterInt<T>::onPrint(std::ostream &os) const {
}

template <typename T>
bool LiteralPrinterInt<T>::isValidBase(unsigned int base) {
  return base == 2 || base == 8 || base == 10 || base == 16;
}

template <typename T>
void LiteralPrinterInt<T>::printBasePrefix(unsigned int base,
                                           std::ostream &os) {
}
} // namespace whiskey
