#ifndef __WHISKEY_AST_Stmt_HPP
#define __WHISKEY_AST_Stmt_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/AST.hpp>

namespace whiskey {
class Stmt : public AST {
protected:
	bool onCompare(const AST &other) const;
	void onGetChildren(std::queue<ContainerRef<AST>> &children);

	virtual bool onCompareStmt(const Stmt &other) const = 0;
	virtual void onGetChildrenStmt(std::queue<ContainerRef<AST>> &children) = 0;

public:
	Stmt(AST::ID id, Range range);
};
}

#endif
