#ifndef __WHISKEY_Passes_PassContext_HPP
#define __WHISKEY_Passes_PassContext_HPP

#include <whiskey/Passes/Module.inc>

namespace whiskey {
template <class T>
class PassContext {
private:
  CRef<AST> parent;
  Ref<T> original;
  Container<AST> replacement;

public:
  PassContext();
  PassContext(CRef<AST> parent, Ref<T> original);

  template <class U>
  PassContext<U> branch();

  template <class U>
  void merge(PassContext<U> &other);

  Ref<T> getOriginal();
  CRef<AST> getParent();
  Container<AST> &getReplacement();
  void setReplacement(Container<AST> value);
};
} // namespace whiskey

#include <whiskey/Passes/PassContext.tpp>

#endif
