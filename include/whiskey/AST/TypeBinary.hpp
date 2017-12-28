#ifndef __WHISKEY_AST_TypeBinary_HPP
#define __WHISKEY_AST_TypeBinary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
class TypeBinary : public Type {
private:
  Container<Type> lhs;
  Container<Type> rhs;

protected:
  virtual AST *onClone() const;

  bool onCompareType(const Type &other) const;
  void onGetChildrenType(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareTypeBinary(const TypeBinary &other) const;
  virtual void onGetChildrenTypeBinary(std::queue<ContainerRef<AST>> &children);

public:
  TypeBinary(AST::ID id, Container<Type> lhs, Container<Type> rhs);
  TypeBinary(AST::ID id, Range range, Container<Type> lhs, Container<Type> rhs);

  Ref<Type> getLHS();
  CRef<Type> getLHS() const;
  void setLHS(Container<Type> value);

  Ref<Type> getRHS();
  CRef<Type> getRHS() const;
  void setRHS(Container<Type> value);
};
} // namespace whiskey

#endif
