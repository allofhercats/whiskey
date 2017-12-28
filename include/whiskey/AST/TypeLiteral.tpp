namespace whiskey {
template <typename ValueType>
bool TypeLiteral<ValueType>::onCompareType(const Type &other) const {
  const TypeLiteral<ValueType> &casted =
      static_cast<const TypeLiteral<ValueType> &>(other);

  if (!(value == casted.value)) {
    return false;
  }

  if (!onCompareTypeLiteral(casted)) {
    return false;
  }

  return true;
}

template <typename ValueType>
void TypeLiteral<ValueType>::onGetChildrenType(
    std::queue<ContainerRef<AST>> &children) {
  onGetChildrenTypeLiteral(children);
}

template <typename ValueType>
bool TypeLiteral<ValueType>::onCompareTypeLiteral(
    const TypeLiteral &other) const {
  return true;
}

template <typename ValueType>
void TypeLiteral<ValueType>::onGetChildrenTypeLiteral(
    std::queue<ContainerRef<AST>> &children) {
}

template <typename ValueType>
TypeLiteral<ValueType>::TypeLiteral(AST::ID id, Range range, ValueType value)
    : Type(id, range), value(value) {
}

template <typename ValueType>
ValueType &TypeLiteral<ValueType>::getValue() {
  return value;
}

template <typename ValueType>
const ValueType &TypeLiteral<ValueType>::getValue() const {
  return value;
}

template <typename ValueType>
void TypeLiteral<ValueType>::setValue(ValueType value) {
  this->value = value;
}
} // namespace whiskey
