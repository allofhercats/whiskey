#ifndef __WHISKEY_AST_StmtEmpty_HPP
#define __WHISKEY_AST_StmtEmpty_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtEmpty : public Stmt {
protected:
	virtual AST *onClone() const;

	bool onCompareStmt(const Stmt &other) const;
	void onGetChildrenStmt(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareStmtEmpty(const StmtEmpty &other) const;
	virtual void onGetChildrenStmtEmpty(std::queue<ContainerRef<AST>> &children);

public:
	StmtEmpty(Range range = Range());
};
}

#endif
