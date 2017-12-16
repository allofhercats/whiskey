#ifndef __WHISKEY_AST_ExprCall_HPP
#define __WHISKEY_AST_ExprCall_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>

namespace whiskey {
class ExprCall : public Expr {
private:
	Container<Expr> callee;
	std::vector<Container<Expr>> args;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareExprCall(const ExprCall &other) const;

public:
	ExprCall(Container<Expr> callee, std::vector<Container<Expr>> args = {});
	ExprCall(Range range, Container<Expr> callee, std::vector<Container<Expr>> args = {});

	Ref<Expr> getCallee();
	CRef<Expr> getCallee() const;
	void setCallee(Container<Expr> value);

	std::vector<Container<Expr>> &getArgs();
	const std::vector<Container<Expr>> &getArgs() const;
};
}

#endif