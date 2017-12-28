#ifndef __WHISKEY_AST_TypeFunction_HPP
#define __WHISKEY_AST_TypeFunction_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
class TypeFunction : public Type {
private:
  Container<Type> ret;
  std::vector<Container<Type>> args;

protected:
  virtual AST *onClone() const;

  bool onCompareType(const Type &other) const;
  void onGetChildrenType(std::queue<ContainerRef<AST>> &children);

  virtual bool onCompareTypeFunction(const TypeFunction &other) const;
  virtual void
  onGetChildrenTypeFunction(std::queue<ContainerRef<AST>> &children);

public:
  TypeFunction(Container<Type> ret, std::vector<Container<Type>> args = {});
  TypeFunction(Range range,
               Container<Type> ret,
               std::vector<Container<Type>> args = {});

  Ref<Type> getRet();
  CRef<Type> getRet() const;
  void setRet(Container<Type> value);

  std::vector<Container<Type>> &getArgs();
  const std::vector<Container<Type>> &getArgs() const;
};
} // namespace whiskey

#endif
