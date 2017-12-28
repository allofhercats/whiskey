#ifndef __WHISKEY_AST_ExprUnary_HPP
#define __WHISKEY_AST_ExprUnary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprUnary : public Expr {
private:
  Container<Expr> arg;

protected:
  virtual AST *onClone() const;

  bool onCompareExpr(const Expr &other) const;
  void onGetChildrenExpr(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareExprUnary(const ExprUnary &other) const;
  virtual void onGetChildrenExprUnary(std::queue<ContainerRef<AST>> &children);

public:
  ExprUnary(AST::ID id, Container<Expr> arg);
  ExprUnary(AST::ID id, Range range, Container<Expr> arg);

  Ref<Expr> getArg();
  CRef<Expr> getArg() const;
  void setArg(Container<Expr> value);
};
} // namespace whiskey

#endif
