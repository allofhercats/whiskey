namespace whiskey {
template <typename ValueType>
bool ExprLiteral<ValueType>::onCompareExpr(const Expr &other) const {
  const ExprLiteral<ValueType> &casted =
      static_cast<const ExprLiteral<ValueType> &>(other);

  if (!(value == casted.value)) {
    return false;
  }

  if (!AST::compare(type, casted.type)) {
    return false;
  }

  if (!onCompareExprLiteral(casted)) {
    return false;
  }

  return true;
}

template <typename ValueType>
void ExprLiteral<ValueType>::onGetChildrenExpr(
    std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(type));
  onGetChildrenExprLiteral(children);
}

template <typename ValueType>
bool ExprLiteral<ValueType>::onCompareExprLiteral(
    const ExprLiteral &other) const {
  return true;
}

template <typename ValueType>
void ExprLiteral<ValueType>::onGetChildrenExprLiteral(
    std::queue<ContainerRef<AST>> &children) {
}

template <typename ValueType>
ExprLiteral<ValueType>::ExprLiteral(AST::ID id,
                                    Range range,
                                    Container<Type> type,
                                    ValueType value)
    : Expr(id, range), type(type), value(value) {
}

template <typename ValueType>
Ref<Type> ExprLiteral<ValueType>::getType() {
  return type;
}

template <typename ValueType>
CRef<Type> ExprLiteral<ValueType>::getType() const {
  return type;
}

template <typename ValueType>
void ExprLiteral<ValueType>::setType(Container<Type> value) {
  type = value;
}

template <typename ValueType>
ValueType &ExprLiteral<ValueType>::getValue() {
  return value;
}

template <typename ValueType>
const ValueType &ExprLiteral<ValueType>::getValue() const {
  return value;
}

template <typename ValueType>
void ExprLiteral<ValueType>::setValue(ValueType value) {
  this->value = value;
}
} // namespace whiskey
