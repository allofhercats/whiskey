#ifndef __WHISKEY_AST_StmtExpr_HPP
#define __WHISKEY_AST_StmtExpr_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtExpr : public Stmt {
private:
  Container<Expr> value;

protected:
  virtual AST *onClone() const;

  bool onCompareStmt(const Stmt &other) const;
  void onGetChildrenStmt(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareStmtExpr(const StmtExpr &other) const;
  virtual void onGetChildrenStmtExpr(std::queue<ContainerRef<AST>> &children);

public:
  StmtExpr(AST::ID id, Container<Expr> value = nullptr);
  StmtExpr(AST::ID id, Range range, Container<Expr> value = nullptr);

  Ref<Expr> getValue();
  CRef<Expr> getValue() const;
  void setValue(Container<Expr> value);
};
} // namespace whiskey

#endif
