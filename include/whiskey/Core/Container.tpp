namespace whiskey {
template <class ValueType>
Container<ValueType>::Container(ValueType *value) : value(value) {
}

template <class ValueType>
Container<ValueType>::Container(const Container &other) {
  value = other.value == nullptr ? nullptr
                                 : other.value->template cloneAs<ValueType>();
}

template <class ValueType>
Container<ValueType>::Container(Container &&other) {
  value = other.value;
  other.value = nullptr;
}

template <class ValueType>
Container<ValueType> &Container<ValueType>::operator=(const Container &other) {
  delete value;
  value = other.value == nullptr ? nullptr
                                 : other.value->template cloneAs<ValueType>();
  return *this;
}

template <class ValueType>
Container<ValueType> &Container<ValueType>::operator=(Container &&other) {
  delete value;
  value = other.value;
  other.value = nullptr;
  return *this;
}

template <class ValueType>
Container<ValueType>::~Container() {
  delete value;
}

template <class ValueType>
Container<ValueType>::operator bool() const {
  return value != nullptr;
}

template <class ValueType>
Container<ValueType>::operator Ref<ValueType>() {
  return Ref<ValueType>(value);
}

template <class ValueType>
Container<ValueType>::operator CRef<ValueType>() const {
  return CRef<ValueType>(value);
}

template <class ValueType>
ValueType *Container<ValueType>::operator->() {
  W_ASSERT_NONNULL(value, "Cannot access null value.");
  return value;
}

template <class ValueType>
const ValueType *Container<ValueType>::operator->() const {
  W_ASSERT_NONNULL(value, "Cannot access null value.");
  return value;
}

template <class ValueType>
ValueType &Container<ValueType>::operator*() {
  W_ASSERT_NONNULL(value, "Cannot access null value.");
  return *value;
}

template <class ValueType>
const ValueType &Container<ValueType>::operator*() const {
  W_ASSERT_NONNULL(value, "Cannot access null value.");
  return *value;
}
} // namespace whiskey
