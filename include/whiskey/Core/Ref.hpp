#ifndef __WHISKEY_Core_Ref_HPP
#define __WHISKEY_Core_Ref_HPP

#include <whiskey/Core/Module.inc>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Cloneable.hpp>
#include <whiskey/Core/CRef.hpp>

namespace whiskey {
template<class ValueType>
class Ref {
private:
	ValueType *value;

public:
	Ref(ValueType *value);

	operator bool() const;
	operator CRef<ValueType>() const;

	ValueType *operator->();
	const ValueType *operator->() const;
	ValueType &operator*();
	const ValueType &operator*() const;
};
}

#include <whiskey/Core/Ref.tpp>

#endif
