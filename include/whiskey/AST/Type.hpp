#ifndef __WHISKEY_AST_Type_HPP
#define __WHISKEY_AST_Type_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Type : public AST {
protected:
	bool onCompare(const AST &other) const;
	void onGetChildren(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareType(const Type &other) const = 0;
	virtual void onGetChildrenType(std::queue<ContainerRef<AST>> &children) = 0;

public:
	Type(AST::ID id, Range range);
};
}

#endif
