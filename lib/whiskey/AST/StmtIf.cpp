#include "Module.inc"

#include <whiskey/AST/StmtIf.hpp>

namespace whiskey {
AST *StmtIf::onClone() const {
  return new StmtIf(getRange(), condition, thenClause, elseClause);
}

bool StmtIf::onCompareStmt(const Stmt &other) const {
  const StmtIf &casted = static_cast<const StmtIf &>(other);

  if (!AST::compare(condition, casted.condition)) {
    return false;
  }

  if (!AST::compare(thenClause, casted.thenClause)) {
    return false;
  }

  if (!AST::compare(elseClause, casted.elseClause)) {
    return false;
  }

  if (!onCompareStmtIf(casted)) {
    return false;
  }

  return true;
}

void StmtIf::onGetChildrenStmt(std::queue<ContainerRef<AST>> &children) {
  children.push(ContainerRef<AST>(condition));
  children.push(ContainerRef<AST>(thenClause));
  children.push(ContainerRef<AST>(elseClause));
  onGetChildrenStmtIf(children);
}

bool StmtIf::onCompareStmtIf(const StmtIf &other) const {
  return true;
}

void StmtIf::onGetChildrenStmtIf(std::queue<ContainerRef<AST>> &children) {
}

StmtIf::StmtIf(Container<Expr> condition,
               Container<Stmt> thenClause,
               Container<Stmt> elseClause)
    : Stmt(AST::ID::StmtIf, Range()), condition(condition),
      thenClause(thenClause), elseClause(elseClause) {
}

StmtIf::StmtIf(Range range,
               Container<Expr> condition,
               Container<Stmt> thenClause,
               Container<Stmt> elseClause)
    : Stmt(AST::ID::StmtIf, range), condition(condition),
      thenClause(thenClause), elseClause(elseClause) {
}

Ref<Expr> StmtIf::getCondition() {
  return condition;
}

CRef<Expr> StmtIf::getCondition() const {
  return condition;
}

void StmtIf::setCondition(Container<Expr> value) {
  condition = value;
}

Ref<Stmt> StmtIf::getThenClause() {
  return thenClause;
}

CRef<Stmt> StmtIf::getThenClause() const {
  return thenClause;
}

void StmtIf::setThenClause(Container<Stmt> value) {
  thenClause = value;
}

Ref<Stmt> StmtIf::getElseClause() {
  return elseClause;
}

CRef<Stmt> StmtIf::getElseClause() const {
  return elseClause;
}

void StmtIf::setElseClause(Container<Stmt> value) {
  elseClause = value;
}
} // namespace whiskey
