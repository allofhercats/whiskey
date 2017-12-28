#include "Module.inc"

#include <whiskey/AST/DeclVariable.hpp>

namespace whiskey {
AST *DeclVariable::onClone() const {
  return new DeclVariable(getRange(), type, getName(), init);
}

bool DeclVariable::onCompareDecl(const Decl &other) const {
  const DeclVariable &casted = static_cast<const DeclVariable &>(other);

  if (!AST::compare(type, casted.type)) {
    return false;
  }

  if (!AST::compare(init, casted.init)) {
    return false;
  }

  if (!onCompareDeclVariable(casted)) {
    return false;
  }

  return true;
}

void DeclVariable::onGetChildrenDecl(std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(type));
  children.push(ContainerRef<AST>(init));
  onGetChildrenDeclVariable(children);
}

bool DeclVariable::onCompareDeclVariable(const DeclVariable &other) const {
  return true;
}

void DeclVariable::onGetChildrenDeclVariable(
    std::queue<ContainerRef<AST>> &children) {
}

DeclVariable::DeclVariable(Container<Type> type,
                           std::string name,
                           Container<Expr> init)
    : Decl(AST::ID::DeclVariable, Range(), name), type(type), init(init) {
}

DeclVariable::DeclVariable(Range range,
                           Container<Type> type,
                           std::string name,
                           Container<Expr> init)
    : Decl(AST::ID::DeclVariable, range, name), type(type), init(init) {
}

Ref<Type> DeclVariable::getType() {
  return type;
}

CRef<Type> DeclVariable::getType() const {
  return type;
}

void DeclVariable::setType(Container<Type> value) {
  type = value;
}

Ref<Expr> DeclVariable::getInit() {
  return init;
}

CRef<Expr> DeclVariable::getInit() const {
  return init;
}

void DeclVariable::setInit(Container<Expr> value) {
  init = value;
}
} // namespace whiskey
