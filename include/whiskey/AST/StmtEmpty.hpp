#ifndef __WHISKEY_AST_StmtEmpty_HPP
#define __WHISKEY_AST_StmtEmpty_HPP

#include <whiskey/AST/Module.inc>

#include <whiskey/AST/Stmt.hpp>

namespace whiskey {
class StmtEmpty : public Stmt {
protected:
	AST *onClone() const;
	bool onCompare(const AST &other) const;

public:
	StmtEmpty(Range range = Range());
};
}

#endif
