#include "Module.inc"

#include <whiskey/AST/TypeBinary.hpp>

namespace whiskey {
AST *TypeBinary::onClone() const {
  return new TypeBinary(getID(), getRange(), lhs, rhs);
}

bool TypeBinary::onCompareType(const Type &other) const {
  const TypeBinary &casted = static_cast<const TypeBinary &>(other);

  if (!AST::compare(lhs, casted.lhs)) {
    return false;
  }

  if (!AST::compare(rhs, casted.rhs)) {
    return false;
  }

  if (!onCompareTypeBinary(casted)) {
    return false;
  }

  return true;
}

void TypeBinary::onGetChildrenType(std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(lhs));
  children.push(ContainerRef<AST>(rhs));
  onGetChildrenTypeBinary(children);
}

bool TypeBinary::onCompareTypeBinary(const TypeBinary &other) const {
  return true;
}

void TypeBinary::onGetChildrenTypeBinary(
    std::queue<ContainerRef<AST>> &children) {
}

TypeBinary::TypeBinary(AST::ID id, Container<Type> lhs, Container<Type> rhs)
    : Type(id, Range()), lhs(lhs), rhs(rhs) {
}

TypeBinary::TypeBinary(AST::ID id,
                       Range range,
                       Container<Type> lhs,
                       Container<Type> rhs)
    : Type(id, range), lhs(lhs), rhs(rhs) {
}

Ref<Type> TypeBinary::getLHS() {
  return lhs;
}

CRef<Type> TypeBinary::getLHS() const {
  return lhs;
}

void TypeBinary::setLHS(Container<Type> value) {
  lhs = value;
}

Ref<Type> TypeBinary::getRHS() {
  return rhs;
}

CRef<Type> TypeBinary::getRHS() const {
  return rhs;
}

void TypeBinary::setRHS(Container<Type> value) {
  rhs = value;
}
} // namespace whiskey
