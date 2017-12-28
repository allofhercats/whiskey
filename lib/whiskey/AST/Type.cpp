#include "Module.inc"

#include <whiskey/AST/Type.hpp>

namespace whiskey {
bool Type::onCompare(const AST &other) const {
  const Type &casted = static_cast<const Type &>(other);

  if (!onCompareType(casted)) {
    return false;
  }

  return true;
}

void Type::onGetChildren(std::queue<ContainerRef<AST>> &children) {
  onGetChildrenType(children);
}

Type::Type(AST::ID id, Range range) : AST(id, range) {
}
} // namespace whiskey
