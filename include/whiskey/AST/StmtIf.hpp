#ifndef __WHISKEY_AST_StmtIf_HPP
#define __WHISKEY_AST_StmtIf_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtIf : public Stmt {
private:
	Container<Expr> condition;
	Container<Stmt> thenClause;
	Container<Stmt> elseClause;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareStmtIf(const StmtIf &other) const;

public:
	StmtIf(Container<Expr> condition, Container<Stmt> thenClause, Container<Stmt> elseClause = nullptr);
	StmtIf(Range range, Container<Expr> condition, Container<Stmt> thenClause, Container<Stmt> elseClause = nullptr);

	Ref<Expr> getCondition();
	CRef<Expr> getCondition() const;
	void setCondition(Container<Expr> value);

	Ref<Stmt> getThenClause();
	CRef<Stmt> getThenClause() const;
	void setThenClause(Container<Stmt> value);

	Ref<Stmt> getElseClause();
	CRef<Stmt> getElseClause() const;
	void setElseClause(Container<Stmt> value);
};
}

#endif
