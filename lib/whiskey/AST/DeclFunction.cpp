#include "Module.inc"

#include <whiskey/AST/DeclVariable.hpp>

#include <whiskey/AST/DeclFunction.hpp>

namespace whiskey {
AST *DeclFunction::onClone() const {
  return new DeclFunction(getRange(), ret, getName(), args, body);
}

bool DeclFunction::onCompareDecl(const Decl &other) const {
  const DeclFunction &casted = static_cast<const DeclFunction &>(other);

  if (!AST::compare(ret, casted.ret)) {
    return false;
  }

  if (!AST::compare(args, casted.args)) {
    return false;
  }

  if (!AST::compare(body, casted.body)) {
    return false;
  }

  if (!onCompareDeclFunction(casted)) {
    return false;
  }

  return true;
}

void DeclFunction::onGetChildrenDecl(std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(ret));
  for (Container<DeclVariable> &i : args) {
    children.push(ContainerRef<AST>(i));
  }
  children.push(ContainerRef<AST>(body));
  onGetChildrenDeclFunction(children);
}

bool DeclFunction::onCompareDeclFunction(const DeclFunction &other) const {
  return true;
}

void DeclFunction::onGetChildrenDeclFunction(
    std::queue<ContainerRef<AST>> &children) {
}

DeclFunction::DeclFunction(Container<Type> ret,
                           std::string name,
                           std::vector<Container<DeclVariable>> args,
                           Container<Stmt> body)
    : Decl(AST::ID::DeclFunction, Range(), name), ret(ret), args(args),
      body(body) {
}

DeclFunction::DeclFunction(Range range,
                           Container<Type> ret,
                           std::string name,
                           std::vector<Container<DeclVariable>> args,
                           Container<Stmt> body)
    : Decl(AST::ID::DeclFunction, range, name), ret(ret), args(args),
      body(body) {
}

Ref<Type> DeclFunction::getRet() {
  return ret;
}

CRef<Type> DeclFunction::getRet() const {
  return ret;
}

void DeclFunction::setRet(Container<Type> value) {
  ret = value;
}

std::vector<Container<DeclVariable>> &DeclFunction::getArgs() {
  return args;
}

const std::vector<Container<DeclVariable>> &DeclFunction::getArgs() const {
  return args;
}

Ref<Stmt> DeclFunction::getBody() {
  return body;
}

CRef<Stmt> DeclFunction::getBody() const {
  return body;
}

void DeclFunction::setBody(Container<Stmt> value) {
  body = value;
}
} // namespace whiskey
