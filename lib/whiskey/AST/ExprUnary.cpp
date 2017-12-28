#include "Module.inc"

#include <whiskey/AST/ExprUnary.hpp>

namespace whiskey {
AST *ExprUnary::onClone() const {
  return new ExprUnary(getID(), getRange(), arg);
}

bool ExprUnary::onCompareExpr(const Expr &other) const {
  const ExprUnary &casted = static_cast<const ExprUnary &>(other);

  if (!AST::compare(arg, casted.arg)) {
    return false;
  }

  if (!onCompareExprUnary(casted)) {
    return false;
  }

  return true;
}

void ExprUnary::onGetChildrenExpr(std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(arg));
  onGetChildrenExprUnary(children);
}

bool ExprUnary::onCompareExprUnary(const ExprUnary &other) const {
  return true;
}

void ExprUnary::onGetChildrenExprUnary(
    std::queue<ContainerRef<AST>> &children) {
}

ExprUnary::ExprUnary(AST::ID id, Container<Expr> arg)
    : Expr(id, Range()), arg(arg) {
}

ExprUnary::ExprUnary(AST::ID id, Range range, Container<Expr> arg)
    : Expr(id, range), arg(arg) {
}

Ref<Expr> ExprUnary::getArg() {
  return arg;
}

CRef<Expr> ExprUnary::getArg() const {
  return arg;
}

void ExprUnary::setArg(Container<Expr> value) {
  arg = value;
}
} // namespace whiskey
