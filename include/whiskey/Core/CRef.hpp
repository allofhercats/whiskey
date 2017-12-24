#ifndef __WHISKEY_Core_CRef_HPP
#define __WHISKEY_Core_CRef_HPP

#include <whiskey/Core/Module.inc>

#include <whiskey/Core/Assert.hpp>
#include <whiskey/Core/Cloneable.hpp>

namespace whiskey {
template<class ValueType>
class CRef {
private:
	const ValueType *value;

public:
	CRef(const ValueType *value = nullptr);

	operator bool() const;

	const ValueType *operator->() const;
	const ValueType &operator*() const;
};
}

#include <whiskey/Core/CRef.tpp>

#endif
