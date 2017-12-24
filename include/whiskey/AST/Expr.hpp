#ifndef __WHISKEY_AST_Expr_HPP
#define __WHISKEY_AST_Expr_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Expr : public AST {
protected:
	bool onCompare(const AST &other) const;
	void onGetChildren(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareExpr(const Expr &other) const = 0;
	virtual void onGetChildrenExpr(std::queue<ContainerRef<AST>> &children) = 0;

public:
	Expr(AST::ID id, Range range);
};
}

#endif
