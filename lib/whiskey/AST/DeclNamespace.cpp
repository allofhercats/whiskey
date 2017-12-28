#include "Module.inc"

#include <whiskey/AST/DeclVariable.hpp>

#include <whiskey/AST/DeclNamespace.hpp>

namespace whiskey {
AST *DeclNamespace::onClone() const {
  return new DeclNamespace(getRange(), getName(), members);
}

bool DeclNamespace::onCompareDecl(const Decl &other) const {
  const DeclNamespace &casted = static_cast<const DeclNamespace &>(other);

  if (!AST::compare(members, casted.members)) {
    return false;
  }

  if (!onCompareDeclNamespace(casted)) {
    return false;
  }

  return true;
}

void DeclNamespace::onGetChildrenDecl(std::queue<ContainerRef<AST>> &children) {
  for (Container<Decl> &i : members) {
    children.push(ContainerRef<AST>(i));
  }
  onGetChildrenDeclNamespace(children);
}

bool DeclNamespace::onCompareDeclNamespace(const DeclNamespace &other) const {
  return true;
}

void DeclNamespace::onGetChildrenDeclNamespace(
    std::queue<ContainerRef<AST>> &children) {
}

DeclNamespace::DeclNamespace(std::string name,
                             std::vector<Container<Decl>> members)
    : Decl(AST::ID::DeclNamespace, Range(), name), members(members) {
}

DeclNamespace::DeclNamespace(Range range,
                             std::string name,
                             std::vector<Container<Decl>> members)
    : Decl(AST::ID::DeclNamespace, range, name), members(members) {
}

std::vector<Container<Decl>> &DeclNamespace::getMembers() {
  return members;
}

const std::vector<Container<Decl>> &DeclNamespace::getMembers() const {
  return members;
}
} // namespace whiskey
