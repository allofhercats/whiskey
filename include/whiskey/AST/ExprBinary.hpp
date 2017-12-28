#ifndef __WHISKEY_AST_ExprBinary_HPP
#define __WHISKEY_AST_ExprBinary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprBinary : public Expr {
private:
  Container<Expr> lhs;
  Container<Expr> rhs;

protected:
  virtual AST *onClone() const;

  bool onCompareExpr(const Expr &other) const;
  void onGetChildrenExpr(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareExprBinary(const ExprBinary &other) const;
  virtual void onGetChildrenExprBinary(std::queue<ContainerRef<AST>> &children);

public:
  ExprBinary(AST::ID id, Container<Expr> lhs, Container<Expr> rhs);
  ExprBinary(AST::ID id, Range range, Container<Expr> lhs, Container<Expr> rhs);

  Ref<Expr> getLHS();
  CRef<Expr> getLHS() const;
  void setLHS(Container<Expr> value);

  Ref<Expr> getRHS();
  CRef<Expr> getRHS() const;
  void setRHS(Container<Expr> value);
};
} // namespace whiskey

#endif
