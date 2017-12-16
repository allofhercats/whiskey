#ifndef __WHISKEY_AST_StmtFor_HPP
#define __WHISKEY_AST_StmtFor_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Stmt.hpp>
#include <whiskey/AST/Decl.hpp>

namespace whiskey {
class StmtFor : public Stmt {
private:
	std::vector<Container<Decl>> decls;
	Container<Expr> condition;
	std::vector<Container<Expr>> steps;
	Container<Stmt> bodyClause;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareStmtFor(const StmtFor &other) const;

public:
	StmtFor(Range range = Range());
	StmtFor(std::vector<Container<Decl>> decls, Container<Expr> condition, std::vector<Container<Expr>> steps, Container<Stmt> bodyClause = nullptr);
	StmtFor(Range range, std::vector<Container<Decl>> decls, Container<Expr> condition, std::vector<Container<Expr>> steps, Container<Stmt> bodyClause = nullptr);

	std::vector<Container<Decl>> &getDecls();
	const std::vector<Container<Decl>> &getDecls() const;

	Ref<Expr> getCondition();
	CRef<Expr> getCondition() const;
	void setCondition(Container<Expr> value);

	std::vector<Container<Expr>> &getSteps();
	const std::vector<Container<Expr>> &getSteps() const;

	Ref<Stmt> getBodyClause();
	CRef<Stmt> getBodyClause() const;
	void setBodyClause(Container<Stmt> value);
};
}

#endif
