#ifndef __WHISKEY_AST_ExprBinary_HPP
#define __WHISKEY_AST_ExprBinary_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprBinary : public Expr {
private:
	Container<Expr> lhs;
	Container<Expr> rhs;

protected:
	virtual AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareExprBinary(const ExprBinary &other) const;

public:
	ExprBinary(AST::ID id, Container<Expr> lhs, Container<Expr> rhs);
	ExprBinary(AST::ID id, Range range, Container<Expr> lhs, Container<Expr> rhs);

	Ref<Expr> getLHS();
	CRef<Expr> getLHS() const;
	void setLHS(Container<Expr> value);

	Ref<Expr> getRHS();
	CRef<Expr> getRHS() const;
	void setRHS(Container<Expr> value);
};
}

#endif