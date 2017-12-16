#ifndef __WHISKEY_AST_StmtExpr_HPP
#define __WHISKEY_AST_StmtExpr_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtExpr : public Stmt {
private:
	Container<Expr> value;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareStmtExpr(const StmtExpr &other) const;

public:
	StmtExpr(AST::ID id, Container<Expr> value = nullptr);
	StmtExpr(AST::ID id, Range range, Container<Expr> value = nullptr);

	Ref<Expr> getValue();
	CRef<Expr> getValue() const;
	void setValue(Container<Expr> value);
};
}

#endif
