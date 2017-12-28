#ifndef __WHISKEY_AST_ExprSymbol_HPP
#define __WHISKEY_AST_ExprSymbol_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprSymbol : public Expr {
private:
  std::string value;
  std::vector<Container<AST>> templateEvalArgs;

protected:
  virtual AST *onClone() const;

  bool onCompareExpr(const Expr &other) const;
  void onGetChildrenExpr(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareExprSymbol(const ExprSymbol &other) const;
  virtual void onGetChildrenExprSymbol(std::queue<ContainerRef<AST>> &children);

public:
  ExprSymbol(std::string value,
             std::vector<Container<AST>> templateEvalArgs = {});
  ExprSymbol(Range range,
             std::string value,
             std::vector<Container<AST>> templateEvalArgs = {});

  const std::string &getValue() const;
  void setValue(std::string value);

  std::vector<Container<AST>> &getTemplateEvalArgs();
  const std::vector<Container<AST>> &getTemplateEvalArgs() const;
};
} // namespace whiskey

#endif
