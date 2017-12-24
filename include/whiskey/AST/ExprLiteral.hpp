#ifndef __WHISKEY_AST_ExprLiteral_HPP
#define __WHISKEY_AST_ExprLiteral_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Type.hpp>
#include <whiskey/AST/Expr.hpp>

namespace whiskey {
template<typename ValueExpr>
class ExprLiteral : public Expr {
private:
	Container<Type> type;
	ValueExpr value;

protected:
	bool onCompareExpr(const Expr &other) const;
	void onGetChildrenExpr(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareExprLiteral(const ExprLiteral &other) const;
	virtual void onGetChildrenExprLiteral(std::queue<ContainerRef<AST>> &children);

public:
	ExprLiteral(AST::ID id, Range range, Container<Type> type, ValueExpr value);

	Ref<Type> getType();
	CRef<Type> getType() const;
	void setType(Container<Type> value);

	ValueExpr &getValue();
	const ValueExpr &getValue() const;
	void setValue(ValueExpr value);
};
}

#include <whiskey/AST/ExprLiteral.tpp>

#endif
