#ifndef __WHISKEY_AST_ExprUnary_HPP
#define __WHISKEY_AST_ExprUnary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprUnary : public Expr {
private:
	Container<Expr> arg;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareExprUnary(const ExprUnary &other) const;

public:
	ExprUnary(AST::ID id, Container<Expr> arg);
	ExprUnary(AST::ID id, Range range, Container<Expr> arg);

	Ref<Expr> getArg();
	CRef<Expr> getArg() const;
	void setArg(Container<Expr> value);
};
}

#endif
