#ifndef __WHISKEY_AST_TypeUnary_HPP
#define __WHISKEY_AST_TypeUnary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
class TypeUnary : public Type {
private:
  Container<Type> arg;

protected:
  virtual AST *onClone() const;

  bool onCompareType(const Type &other) const;
  void onGetChildrenType(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareTypeUnary(const TypeUnary &other) const;
  virtual void onGetChildrenTypeUnary(std::queue<ContainerRef<AST>> &children);

public:
  TypeUnary(AST::ID id, Container<Type> arg);
  TypeUnary(AST::ID id, Range range, Container<Type> arg);

  Ref<Type> getArg();
  CRef<Type> getArg() const;
  void setArg(Container<Type> value);
};
} // namespace whiskey

#endif
