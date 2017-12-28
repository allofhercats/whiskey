#include "Module.inc"

// This is put before Decl.hpp due to the forward declaration of DeclVariable
// in Decl.hpp.
#include <whiskey/AST/DeclVariable.hpp>

#include <whiskey/AST/Decl.hpp>

namespace whiskey {
bool Decl::onCompare(const AST &other) const {
  const Decl &casted = static_cast<const Decl &>(other);

  if (name != casted.name) {
    return false;
  }

  if (!AST::compare(templateDeclArgs, casted.templateDeclArgs)) {
    return false;
  }

  if (!onCompareDecl(casted)) {
    return false;
  }

  return true;
}

void Decl::onGetChildren(std::queue<ContainerRef<AST>> &children) {
  for (Container<DeclVariable> &i : templateDeclArgs) {
    children.push(ContainerRef<AST>(i));
  }
  onGetChildrenDecl(children);
}

Decl::Decl(AST::ID id, Range range, std::string name)
    : AST(id, range), name(name) {
}

const std::string &Decl::getName() const {
  return name;
}

void Decl::setName(std::string value) {
  name = value;
}

std::vector<Container<DeclVariable>> &Decl::getTemplateDeclArgs() {
  return templateDeclArgs;
}

const std::vector<Container<DeclVariable>> &Decl::getTemplateDeclArgs() const {
  return templateDeclArgs;
}
} // namespace whiskey
