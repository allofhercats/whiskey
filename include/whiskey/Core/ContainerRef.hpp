#ifndef __WHISKEY_Core_ContainerRef_HPP
#define __WHISKEY_Core_ContainerRef_HPP

#include <whiskey/Core/Module.inc>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Container.hpp>

namespace whiskey {
template <class ValueType>
class ContainerRef {
private:
  ValueType **value;

public:
  ContainerRef();

  template <class ContainerType>
  ContainerRef(Container<ContainerType> &value);

  operator bool() const;
  operator Container<ValueType>();
  operator Ref<ValueType>();
  operator CRef<ValueType>() const;

  ValueType *operator->();
  const ValueType *operator->() const;
  ValueType &operator*();
  const ValueType &operator*() const;

  void replace(ValueType *value);
};
} // namespace whiskey

#include <whiskey/Core/ContainerRef.tpp>

#endif
