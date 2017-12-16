#ifndef __WHISKEY_AST_StmtWhile_HPP
#define __WHISKEY_AST_StmtWhile_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtWhile : public Stmt {
private:
	Container<Expr> condition;
	Container<Stmt> bodyClause;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareStmtWhile(const StmtWhile &other) const;

public:
	StmtWhile(Container<Expr> condition, Container<Stmt> bodyClause = nullptr);
	StmtWhile(Range range, Container<Expr> condition, Container<Stmt> bodyClause = nullptr);

	Ref<Expr> getCondition();
	CRef<Expr> getCondition() const;
	void setCondition(Container<Expr> value);

	Ref<Stmt> getBodyClause();
	CRef<Stmt> getBodyClause() const;
	void setBodyClause(Container<Stmt> value);
};
}

#endif
