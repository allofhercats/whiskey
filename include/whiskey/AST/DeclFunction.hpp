#ifndef __WHISKEY_AST_DeclFunction_HPP
#define __WHISKEY_AST_DeclFunction_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Decl.hpp>
#include <whiskey/AST/DeclVariable.hpp>
#include <whiskey/AST/Stmt.hpp>
#include <whiskey/AST/Type.hpp>

namespace whiskey {
class DeclFunction : public Decl {
private:
  Container<Type> ret;
  std::vector<Container<DeclVariable>> args;
  Container<Stmt> body;

protected:
  virtual AST *onClone() const;

  bool onCompareDecl(const Decl &other) const;
  void onGetChildrenDecl(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareDeclFunction(const DeclFunction &other) const;
  virtual void
  onGetChildrenDeclFunction(std::queue<ContainerRef<AST>> &children);

public:
  DeclFunction(Container<Type> ret,
               std::string name,
               std::vector<Container<DeclVariable>> args = {},
               Container<Stmt> body = nullptr);
  DeclFunction(Range range,
               Container<Type> ret,
               std::string name,
               std::vector<Container<DeclVariable>> args = {},
               Container<Stmt> body = nullptr);

  Ref<Type> getRet();
  CRef<Type> getRet() const;
  void setRet(Container<Type> value);

  std::vector<Container<DeclVariable>> &getArgs();
  const std::vector<Container<DeclVariable>> &getArgs() const;

  Ref<Stmt> getBody();
  CRef<Stmt> getBody() const;
  void setBody(Container<Stmt> value);
};
} // namespace whiskey

#endif
