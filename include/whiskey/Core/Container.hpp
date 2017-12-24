#ifndef __WHISKEY_Core_Container_HPP
#define __WHISKEY_Core_Container_HPP

#include <whiskey/Core/Module.inc>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Cloneable.hpp>
#include <whiskey/Core/Ref.hpp>
#include <whiskey/Core/CRef.hpp>

namespace whiskey {
template<class ContainerRefType>
class ContainerRef;

template<class ValueType>
class Container {
	template<class ContainerRefType>
	friend class ContainerRef;

private:
	ValueType *value;

public:
	Container(ValueType *value = nullptr);
	Container(const Container &other);
	Container(Container &&other);
	Container &operator=(const Container &other);
	Container &operator=(Container &&other);
	~Container();

	operator bool() const;
	operator Ref<ValueType>();
	operator CRef<ValueType>() const;

	ValueType *operator->();
	const ValueType *operator->() const;
	ValueType &operator*();
	const ValueType &operator*() const;
};
}

#include <whiskey/Core/Container.tpp>

#endif
