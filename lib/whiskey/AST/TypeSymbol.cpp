#include "Module.inc"

#include <whiskey/AST/TypeSymbol.hpp>

namespace whiskey {
AST *TypeSymbol::onClone() const {
  TypeSymbol *rtn = new TypeSymbol(getRange(), getValue());
  rtn->templateEvalArgs = templateEvalArgs;
  return rtn;
}

bool TypeSymbol::onCompareTypeLiteral(
    const TypeLiteral<std::string> &other) const {
  const TypeSymbol &casted = static_cast<const TypeSymbol &>(other);

  if (!AST::compare(templateEvalArgs, casted.templateEvalArgs)) {
    return false;
  }

  if (!onCompareTypeSymbol(casted)) {
    return false;
  }

  return true;
}

void TypeSymbol::onGetChildrenTypeLiteral(
    std::queue<ContainerRef<AST>> &children) {
  for (Container<AST> &i : templateEvalArgs) {
    children.push(ContainerRef<AST>(i));
  }
  onGetChildrenTypeSymbol(children);
}

bool TypeSymbol::onCompareTypeSymbol(const TypeSymbol &other) const {
  return true;
}

void TypeSymbol::onGetChildrenTypeSymbol(
    std::queue<ContainerRef<AST>> &children) {
}

TypeSymbol::TypeSymbol(std::string value,
                       std::vector<Container<AST>> templateEvalArgs)
    : TypeLiteral<std::string>(AST::ID::TypeSymbol, Range(), value),
      templateEvalArgs(templateEvalArgs) {
}

TypeSymbol::TypeSymbol(Range range,
                       std::string value,
                       std::vector<Container<AST>> templateEvalArgs)
    : TypeLiteral<std::string>(AST::ID::TypeSymbol, range, value),
      templateEvalArgs(templateEvalArgs) {
}

std::vector<Container<AST>> &TypeSymbol::getTemplateEvalArgs() {
  return templateEvalArgs;
}

const std::vector<Container<AST>> &TypeSymbol::getTemplateEvalArgs() const {
  return templateEvalArgs;
}
} // namespace whiskey
