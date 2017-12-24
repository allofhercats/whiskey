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
	virtual AST *onClone() const;

	bool onCompareStmt(const Stmt &other) const;
	void onGetChildrenStmt(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareStmtForEach(const StmtForEach &other) const;
	virtual void onGetChildrenStmtForEach(std::queue<ContainerRef<AST>> &children);

public:
	StmtForEach(Container<Decl> value, Container<Expr> sequence, Container<Stmt> bodyClause = nullptr);
	StmtForEach(Range range, Container<Decl> value, Container<Expr> sequence, Container<Stmt> bodyClause = nullptr);

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
