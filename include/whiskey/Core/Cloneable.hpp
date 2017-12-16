#ifndef __WHISKEY_Core_Cloneable_HPP
#define __WHISKEY_Core_Cloneable_HPP

#include <whiskey/Core/Module.inc>

#include <whiskey/Core/Assert.hpp>

namespace whiskey {
template<class SelfType>
class Cloneable {
protected:
	virtual SelfType *onClone() const = 0;

public:
	Cloneable();
	Cloneable(const Cloneable &) = delete;
	Cloneable(Cloneable &&) = delete;
	Cloneable &operator=(const Cloneable &) = delete;
	Cloneable &operator=(Cloneable &&) = delete;
	virtual ~Cloneable();

	SelfType *clone() const;
	
	template<class ResType>
	ResType *cloneAs() const;
};
}

#include <whiskey/Core/Cloneable.tpp>

#endif
