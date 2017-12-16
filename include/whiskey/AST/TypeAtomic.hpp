#ifndef __WHISKEY_AST_TypeAtomic_HPP
#define __WHISKEY_AST_TypeAtomic_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>

namespace whiskey {
class TypeAtomic : public Type {
protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareTypeAtomic(const TypeAtomic &other) const;

public:
	TypeAtomic(AST::ID id, Range range = Range());
};
}

#endif
