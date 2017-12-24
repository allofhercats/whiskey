#ifndef __WHISKEY_AST_TypeAtomic_HPP
#define __WHISKEY_AST_TypeAtomic_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
class TypeAtomic : public Type {
protected:
	virtual AST *onClone() const;

	bool onCompareType(const Type &other) const;
	void onGetChildrenType(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareTypeAtomic(const TypeAtomic &other) const;
	virtual void onGetChildrenTypeAtomic(std::queue<ContainerRef<AST>> &children);

public:
	TypeAtomic(AST::ID id, Range range = Range());
};
}

#endif
