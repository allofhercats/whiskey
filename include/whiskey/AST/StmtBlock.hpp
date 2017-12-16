#ifndef __WHISKEY_AST_StmtBlock_HPP
#define __WHISKEY_AST_StmtBlock_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtBlock : public Stmt {
private:
	std::vector<Container<Stmt>> body;

protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

	virtual bool onCompareStmtBlock(const StmtBlock &other) const;

public:
	StmtBlock(std::vector<Container<Stmt>> body = {});
	StmtBlock(Range range, std::vector<Container<Stmt>> body = {});

	std::vector<Container<Stmt>> &getBody();
	const std::vector<Container<Stmt>> &getBody() const;
};
}

#endif
