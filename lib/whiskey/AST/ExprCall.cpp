#include "Module.inc"

#include <whiskey/AST/ExprCall.hpp>

namespace whiskey {
AST *ExprCall::onClone() const {
  return new ExprCall(getRange(), callee, args);
}

bool ExprCall::onCompareExpr(const Expr &other) const {
  const ExprCall &casted = static_cast<const ExprCall &>(other);

  if (!AST::compare(callee, casted.callee)) {
    return false;
  }

  if (!AST::compare(args, casted.args)) {
    return false;
  }

  if (!onCompareExprCall(casted)) {
    return false;
  }

  return true;
}

void ExprCall::onGetChildrenExpr(std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(callee));
  for (Container<Expr> &i : args) {
    children.push(ContainerRef<AST>(i));
  }
  onGetChildrenExprCall(children);
}

bool ExprCall::onCompareExprCall(const ExprCall &other) const {
  return true;
}

void ExprCall::onGetChildrenExprCall(std::queue<ContainerRef<AST>> &children) {
}

ExprCall::ExprCall(Container<Expr> callee, std::vector<Container<Expr>> args)
    : Expr(AST::ID::ExprCall, Range()), callee(callee), args(args) {
}

ExprCall::ExprCall(Range range,
                   Container<Expr> callee,
                   std::vector<Container<Expr>> args)
    : Expr(AST::ID::ExprCall, range), callee(callee), args(args) {
}

Ref<Expr> ExprCall::getCallee() {
  return callee;
}

CRef<Expr> ExprCall::getCallee() const {
  return callee;
}

void ExprCall::setCallee(Container<Expr> value) {
  callee = value;
}

std::vector<Container<Expr>> &ExprCall::getArgs() {
  return args;
}

const std::vector<Container<Expr>> &ExprCall::getArgs() const {
  return args;
}
} // namespace whiskey
