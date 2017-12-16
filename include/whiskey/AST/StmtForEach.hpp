#ifndef __WHISKEY_AST_StmtForEach_HPP
#define __WHISKEY_AST_StmtForEach_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Expr.hpp>
#include <whiskey/AST/Stmt.hpp>
#include <whiskey/AST/Decl.hpp>

namespace whiskey {
class StmtForEach : public Stmt {
private:
	Container<Decl> value;
	Container<Expr> sequence;
	Container<Stmt> bodyClause;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareStmtForEach(const StmtForEach &other) const;

public:
	StmtForEach(Container<Decl> value, Container<Expr> sequence, Container<Stmt> bodyClause);
	StmtForEach(Range range, Container<Decl> value, Container<Expr> sequence, Container<Stmt> bodyClause);

	Ref<Decl> getValue();
	CRef<Decl> getValue() const;
	void setValue(Container<Decl> value);

	Ref<Expr> getSequence();
	CRef<Expr> getSequence() const;
	void setSequence(Container<Expr> value);

	Ref<Stmt> getBodyClause();
	CRef<Stmt> getBodyClause() const;
	void setBodyClause(Container<Stmt> value);
};
}

#endif
